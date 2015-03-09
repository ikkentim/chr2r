#include "EditorScene.h"
#include <fstream>

#include <direct.h>

#define MOVEMENT_ACCEL      (0.0004)
#define MOVEMENT_DECEL      (0.008)
EditorScene *instance;

bool fileExists(const char * file)
{
    std::string fp = std::string(_getcwd(NULL, 0)).append("/").append(file);

    OutputDebugString(fp.c_str());
    std::ifstream ifile(fp.c_str());
    return !!ifile;
}

bool isBmpPath(std::string const &fullString) {
    return fullString.length() >= 4 && 
        (0 == fullString.compare(fullString.length() - 4, 4, ".bmp"));
}


bool SetBackgroundTextureCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isBmpPath(cmd)) {
        console->LogError("Given path is not a .bmp file.");
        console->LogNotice("Usage: setbackgroundtexture [path]");
        return true;
    }

    if (!fileExists(cmd)) {
        console->LogError("File does not exist.");
        console->LogNotice("Usage: setbackgroundtexture [path]");
        return true;
    }

    console->LogNotice("Background set to %s", cmd);
    instance->SetBackground(SpriteSheet::Get(command));

    return true;
}

bool SetBackgroundWidthCommand(Console * const console, const char *cmd) {
    int width = atoi(cmd);

    if (width < 100) {
        console->LogError("Minimum width is 100. %d was given.", width);
        console->LogNotice("Usage: setbackgroundwidth [width]");
        return true;
    }
    console->LogNotice("Background width set to %d", width);
    instance->SetBackgroundWidth(width);

    return true;
}

bool GoToCommand(Console * const console, const char *cmd) {
    std::string command = cmd;


    int sp = command.find(' ');
    if (sp == -1) sp = command.length();
    std::string xvalue = command.substr(0, sp);

    command.erase(0, sp);
    while (command.find(' ', 0) == 0) command.erase(0, 1);

    sp = command.find(' ');
    if (sp == -1) sp = command.length();
    std::string yvalue = command.substr(0, sp);

    if (xvalue.length() == 0 || yvalue.length() == 0) {
        console->LogNotice("Invalid parameters.");
        console->LogNotice("Usage: goto [x] [y]");
        return true;
    }

    instance->GoTo(atoi(xvalue.c_str()), atoi(yvalue.c_str()));

    return true;
}

EditorScene::EditorScene(GameWindow *window)
    :window_(window), viewport_(Viewport(0, 0, 640, 480)) {

    instance = this;

    window->console()->RegisterCommand("setbackgroundtexture", 
        SetBackgroundTextureCommand);
    window->console()->RegisterCommand("setbackgroundwidth", 
        SetBackgroundWidthCommand);
    window->console()->RegisterCommand("goto", GoToCommand);
}

EditorScene::~EditorScene() {
}

void EditorScene::Start() {
    // temporary defaults
    SetBackground(SpriteSheet::Get("spr/background01.bmp"));
    SetBackgroundWidth(727);
}

void EditorScene::Update(double delta, Keys keys) {

    if (keys & KEY_LEFT)
        cursorVelocity_.x -= MOVEMENT_ACCEL * delta;
    else if (cursorVelocity_.x < 0)
        cursorVelocity_.x += min(abs(cursorVelocity_.x), MOVEMENT_DECEL * delta);

    if (keys & KEY_RIGHT)
        cursorVelocity_.x += MOVEMENT_ACCEL * delta;
    else if (cursorVelocity_.x > 0)
        cursorVelocity_.x -= min(abs(cursorVelocity_.x), MOVEMENT_DECEL * delta);

    if (keys & KEY_UP)
        cursorVelocity_.y -= MOVEMENT_ACCEL * delta;
    else if (cursorVelocity_.y < 0)
        cursorVelocity_.y += min(abs(cursorVelocity_.y), MOVEMENT_DECEL * delta);

    if (keys & KEY_DOWN)
        cursorVelocity_.y += MOVEMENT_ACCEL * delta;
    else if (cursorVelocity_.y > 0)
        cursorVelocity_.y -= min(abs(cursorVelocity_.y), MOVEMENT_DECEL * delta);

    cursorPos_ += cursorVelocity_;



    /* Update viewport */
    UpdateViewport();
}

void EditorScene::UpdateViewport()
{
    /* Minimum distance between window edge and the player*/
    const int borderOffset = 215;

    int minx = viewport_.x + borderOffset;
    int maxx = viewport_.x - borderOffset + viewport_.width;

    int miny = viewport_.y + borderOffset;
    int maxy = viewport_.y - borderOffset + viewport_.height;

    auto pos = cursorPos_;
    int posx = (int)floor(pos.x);
    int posy = (int)floor(pos.y);

    if (posx < minx) viewport_.x += posx - minx;
    else if (posx > maxx) viewport_.x += posx - maxx;

    if (posy < miny) viewport_.y += posy - miny;
    else if (posy > maxy) viewport_.y += posy - maxy;
}

void EditorScene::Render(HDC graphics) {
    /* Draw background */
    if (background_ && backgroundWidth_ > 0) {
        Texture tex = { 0, 0, backgroundWidth_, viewport_.height };
        for (int skyx = -(viewport_.x / 2) % backgroundWidth_ - backgroundWidth_;
            skyx <= viewport_.width; skyx += backgroundWidth_) {
            background_->Draw(tex, skyx, 0);
        }
    }

    /*
    /* Render all layers * /
    LevelLayer *layer;

    layer = level_->BackgroundLayer();
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;
        object->Render(viewport_);
    }
    layer = level_->PlayableLayer();
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;
        object->Render(viewport_);
    }
    layer = level_->ForegroundLayer();
    for (LevelLayer::iterator it = layer->begin(); it != layer->end(); ++it) {
        GameObject *object = *it;
        object->Render(viewport_);
    }*/


    /* Draw cursor */
    HPEN hLinePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hPenOld = (HPEN)SelectObject(graphics, hLinePen);
 
    int x = (int)cursorPos_.x - viewport_.x;
    int y = (int)cursorPos_.y - viewport_.y;
    MoveToEx(graphics, x, 0, NULL);
    LineTo(graphics, x, viewport_.height);
    MoveToEx(graphics, 0, y, NULL);
    LineTo(graphics,  viewport_.width, y);

    SelectObject(graphics, hPenOld);
    DeleteObject(hLinePen);

    /* Draw cursor pos*/
    char buf[32];
    sprintf_s(buf, "%f, %f", cursorPos_.x, cursorPos_.y);
    TextOut(graphics, 5, 50, buf, strlen(buf));
}

#include "EditorScene.h"
#include "LevelHeader.h"
#include <fstream>
#include <algorithm>

#include <direct.h>

#define MOVEMENT_ACCEL      (0.0004)

EditorScene *instance; /* todo: find a better way than just keeping a ref */

bool fileExists(const char * file) {
    std::string fp = std::string(_getcwd(NULL, 0)).append("/").append(file);

    OutputDebugString(fp.c_str());
    std::ifstream ifile(fp.c_str());
    return !!ifile;
}

bool isExtPath(std::string const &fullString, const char *ext) {
    return fullString.length() >= 4 && 
        (0 == fullString.compare(fullString.length() - strlen(ext), strlen(ext), ext));
}

bool SetLevelNameCommand(Console * const console, const char *cmd) {
    if (strlen(cmd) == 0) {
        console->LogNotice("Usage: setlevelname [name]");
        return true;
    }

    console->LogNotice("Level name set to %s.", cmd);
    instance->SetLevelName(cmd);
    return true;
}
bool SetNextLevelCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".dat")) {
        console->LogError("Given path is not a .dat file.");
        console->LogNotice("Usage: setnextlevel [path]");
        return true;
    }

    if (!fileExists(cmd)) {
        console->LogError("File does not exist.");
        console->LogNotice("Usage: setnextlevel [path]");
        return true;
    }

    console->LogNotice("Next level set to %s.", cmd);
    instance->SetNextLevel(cmd);

    return true;
}

bool SetBackgroundTextureCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".bmp")) {
        console->LogError("Given path is not a .bmp file.");
        console->LogNotice("Usage: setbackgroundtexture [path]");
        return true;
    }

    if (!fileExists(cmd)) {
        console->LogError("File does not exist.");
        console->LogNotice("Usage: setbackgroundtexture [path]");
        return true;
    }

    console->LogNotice("Background set to %s.", cmd);
    instance->SetBackground(cmd);

    return true;
}

bool SetTerrainTextureCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".bmp")) {
        console->LogError("Given path is not a .bmp file.");
        console->LogNotice("Usage: setterraintexture [path]");
        return true;
    }

    if (!fileExists(cmd)) {
        console->LogError("File does not exist.");
        console->LogNotice("Usage: setterraintexture [path]");
        return true;
    }

    console->LogNotice("Terrain set to %s.", cmd);
    instance->SetTerrain(cmd);

    return true;
}

bool SetBackgroundWidthCommand(Console * const console, const char *cmd) {
    int width = atoi(cmd);

    if (width < 100) {
        console->LogError("Minimum width is 100. %d was given.", width);
        console->LogNotice("Usage: setbackgroundwidth [width]");
        return true;
    }

    console->LogNotice("Background width set to %d.", width);
    instance->SetBackgroundWidth(width);

    return true;
}

bool SetGridSizeCommand(Console * const console, const char *cmd) {
    int size = atoi(cmd);

    if (size < 1) {
        console->LogError("Minimum grid size is 1. %d was given.", size);
        console->LogNotice("Usage: setgridsize [size]");
        return true;
    }

    console->LogNotice("Grid size set to %d.", size);
    instance->SetGridSize(size);

    return true;
}

bool SetBottomYCommand(Console * const console, const char *cmd) {
    int y = atoi(cmd);

    console->LogNotice("Bottom Y set to %d", y);
    instance->SetBottomY(y);

    return true;
}

bool SaveLevelCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".dat")) {
        console->LogError("Given path is not a .dat file.");
        console->LogNotice("Usage: savelevel [path]");
        return true;
    }

    console->LogNotice("Saving to %s...", cmd);
    instance->Save(cmd);
    console->LogNotice("Level saved!", cmd);
}

bool SetPlayerSpawnCommand(Console * const console, const char *cmd) {
    int x, y;
    instance->GetCurrentPos(x, y);
    instance->SetPlayerSpawn(x, y);

    console->LogNotice("Player spawn set to (%d, %d).", x, y);
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

bool ToggleLayerCommand(Console * const console, const char *cmd) {
    switch (cmd[0])
    {
    case 'P':
    case 'p':
        if (instance->ToggleLayerVisible(LevelManager::PLAYABLE))
            console->LogNotice("The playable layer is now visible.");
        else
            console->LogNotice("The playable layer is now invisible.");
        break;
    case 'B':
    case 'b':
        if (instance->ToggleLayerVisible(LevelManager::BACKGROUND))
            console->LogNotice("The background layer is now visible.");
        else
            console->LogNotice("The background layer is now invisible.");
        break;
    case 'F':
    case 'f':
        if (instance->ToggleLayerVisible(LevelManager::FOREGROUND))
            console->LogNotice("The foreground layer is now visible.");
        else
            console->LogNotice("The foreground layer is now invisible.");
        break;
    default:
        console->LogNotice("Invalid parameters.");
        console->LogNotice("Usage: togglelayer [layer]");
        break;
    }

    return true;
}

bool SelectTextureCommand(Console * const console, const char *cmd) {
    std::string command = cmd;


    int sp = command.find(' ');
    if (sp == -1) sp = command.length();
    std::string xvalue = command.substr(0, sp);

    command.erase(0, sp);
    while (command.find(' ', 0) == 0) command.erase(0, 1);

    sp = command.find(' ');
    if (sp == -1) sp = command.length();
    std::string yvalue = command.substr(0, sp);

    command.erase(0, sp);
    while (command.find(' ', 0) == 0) command.erase(0, 1);

    sp = command.find(' ');
    if (sp == -1) sp = command.length();
    std::string wvalue = command.substr(0, sp);

    command.erase(0, sp);
    while (command.find(' ', 0) == 0) command.erase(0, 1);

    sp = command.find(' ');
    if (sp == -1) sp = command.length();
    std::string hvalue = command.substr(0, sp);

    if (xvalue.length() == 0 || yvalue.length() == 0 || 
        wvalue.length() == 0 || hvalue.length() == 0) {
        console->LogNotice("Invalid parameters.");
        console->LogNotice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    int x = atoi(xvalue.c_str());
    int y = atoi(yvalue.c_str());
    int width = atoi(wvalue.c_str());
    int height = atoi(hvalue.c_str());

    if (x < 0) {
        console->LogNotice("Minimum left value is 0. %d was given", x);
        console->LogNotice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    if (y < 0) {
        console->LogNotice("Minimum top value is 0. %d was given", y);
        console->LogNotice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    if (width < 1) {
        console->LogNotice("Minimum width value is 1. %d was given", width);
        console->LogNotice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    if (height < 1) {
        console->LogNotice("Minimum height value is 1. %d was given", height);
        console->LogNotice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    instance->SelectTexture(x, y, width, height);

    return true;
}

EditorScene::EditorScene(GameWindow *window)
    :window_(window), viewport_(Viewport(0, 0, 640, 480)) {
    instance = this;

    defaultTerrain_ = SpriteSheet::Get("spr/terrain.bmp");

    ZeroMemory(levelName_, MAX_LEVEL_NAME);
    ZeroMemory(backgroundPath_, MAX_TEXTURE_PATH);
    ZeroMemory(terrainPath_, MAX_TEXTURE_PATH);
    ZeroMemory(nextLevel_, MAX_LEVEL_PATH);

    window->console()->RegisterCommand("setterraintexture",
        SetTerrainTextureCommand);
    window->console()->RegisterCommand("setbackgroundtexture", 
        SetBackgroundTextureCommand);
    window->console()->RegisterCommand("setbackgroundwidth", 
        SetBackgroundWidthCommand);
    window->console()->RegisterCommand("goto", GoToCommand);
    window->console()->RegisterCommand("setbottomy", SetBottomYCommand);
    window->console()->RegisterCommand("savelevel", SaveLevelCommand);
    window->console()->RegisterCommand("setplayerspawn", SetPlayerSpawnCommand);
    window->console()->RegisterCommand("setlevelname", SetLevelNameCommand);
    window->console()->RegisterCommand("setnextlevel", SetNextLevelCommand);
    window->console()->RegisterCommand("togglelayer", ToggleLayerCommand);
    window->console()->RegisterCommand("setgridsize", SetGridSizeCommand);
    window->console()->RegisterCommand("selecttexture", SelectTextureCommand);
}

EditorScene::~EditorScene() {
}

void EditorScene::Save(const char *path) {
    LevelHeader lvl;
    lvl.bottom = bottomY_;
    lvl.player_x = playerX_;
    lvl.player_y = playerY_;
    lvl.player_abilities_ph = 0;
    sprintf_s(lvl.name, levelName_);
    sprintf_s(lvl.background_texture, backgroundPath_);
    lvl.background_width = backgroundWidth_;
    sprintf_s(lvl.terrain_texture, terrainPath_);
    sprintf_s(lvl.next_level, nextLevel_);
    lvl.actor_count = 0;
    lvl.object_count = playableLayer_.size() + foregroundLayer_.size() +
        backgroundLayer_.size();

    std::ofstream lvlout;
    lvlout.open(path, std::ios::out | std::ios::binary);

    lvlout.write((char *)&lvl, sizeof(lvl));

    /* todo: add objects and actors */

    for (ObjectData d : playableLayer_) {
        lvlout.write((char *)&d, sizeof(d));
    }
    for (ObjectData d : foregroundLayer_) {
        lvlout.write((char *)&d, sizeof(d));
    }
    for (ObjectData d : backgroundLayer_) {
        lvlout.write((char *)&d, sizeof(d));
    }

    lvlout.close();

}

void EditorScene::Start() {
    /* temporary defaults */
    SetBackground("spr/background01.bmp");
    SetTerrain("spr/terrain.bmp");
    SetBackgroundWidth(727);
}

void EditorScene::Update(double delta, Keys keys) {

    auto accel = MOVEMENT_ACCEL * max(1, gridSize_ / 4) * delta;
    /* Movement keys */
    if (keys & KEY_LEFT)
        cursorVelocity_.x -= accel;
    else if (cursorVelocity_.x < 0)
        cursorVelocity_.x  = 0;

    if (keys & KEY_RIGHT)
        cursorVelocity_.x += accel;
    else if (cursorVelocity_.x > 0)
        cursorVelocity_.x = 0;

    if (keys & KEY_UP)
        cursorVelocity_.y -= accel;
    else if (cursorVelocity_.y < 0)
        cursorVelocity_.y = 0;

    if (keys & KEY_DOWN)
        cursorVelocity_.y += accel;
    else if (cursorVelocity_.y > 0)
        cursorVelocity_.y = 0;

    cursorPos_ += cursorVelocity_;

    if (!isKeyDown_) {
        if (keys & KEY_L) {
            switch (currentLayer_) {
                case LevelManager::PLAYABLE:
                    currentLayer_ = LevelManager::FOREGROUND;
                break;
                case LevelManager::FOREGROUND:
                    currentLayer_ = LevelManager::BACKGROUND;
                break;
                case LevelManager::BACKGROUND:
                    currentLayer_ = LevelManager::PLAYABLE;
                break;
            }
            isKeyDown_ = true;
        }
        else if (keys & KEY_O) {/* TODO: put object types in an array for a 
                           little more dynimicness.*/
            switch (currentObjectType_) {
            case BLOCK:
                currentObjectType_ = COIN;
                break;
            case COIN:
                currentObjectType_ = BLOCK;
                break;
            }
            isKeyDown_ = true;
        }
        else if (keys & KEY_JUMP) {
            if (selectedTexture_.width > 0 && selectedTexture_.height > 0) {
                ObjectData data;
                GetCurrentPos(data.x, data.y);
                data.layer = currentLayer_;
                data.texture = selectedTexture_;
                data.type = currentObjectType_;
                data.width = selectedTexture_.width;
                data.height = selectedTexture_.height;

                AddObject(GetCurrentLayer(), data);
            }
            isKeyDown_ = true;
        }
        else if (keys & KEY_DELETE) {

            int x, y;
            GetCurrentPos(x, y);
            RemoveObject(GetCurrentLayer(), Vector2(x, y));
            isKeyDown_ = true;
        }
    }
    else {
        isKeyDown_ = (keys & KEY_L) || (keys & KEY_O) || (keys & KEY_JUMP) || (keys & KEY_DELETE);
    }

    /* Update viewport */
    UpdateViewport();
}

void EditorScene::AddObject(std::vector<ObjectData> *layer, ObjectData data) {
    for (std::vector<ObjectData>::iterator it = layer->begin(); it != layer->end();)
    {
        ObjectData check = *it;

        if (!(data.x - data.width / 2 >= check.x + check.width / 2 ||
            data.x + data.width / 2 <= check.x - check.width / 2 ||
            data.y - data.height / 2 >= check.y + check.height / 2 ||
            data.y + data.height / 2 <= check.y - check.height / 2)) {
            it = layer->erase(it);
        }
        else {
            ++it;
        }
    }

    layer->push_back(data);
}

void EditorScene::RemoveObject(std::vector<ObjectData> *layer, Vector2 pos) {
    for (std::vector<ObjectData>::iterator it = layer->begin(); it != layer->end();)
    {
        ObjectData check = *it;
        if (!(pos.x >= check.x + check.width / 2 ||
            pos.x <= check.x - check.width / 2 ||
            pos.y >= check.y + check.height / 2 ||
            pos.y <= check.y - check.height / 2)) {
            it = layer->erase(it);
        }
        else {
            ++it;
        }
    }
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

void EditorScene::DrawObject(ObjectData data) {
    switch (data.type) {
    case BLOCK:
        terrain_->Draw(data.texture, Vector2(data.x, data.y), viewport_);
        break;
    case COIN:
        defaultTerrain_->Draw(Texture(219, 28, 12, 16), Vector2(data.x, data.y), viewport_);
        break;
    }
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

    /* Draw terrain */
    if (terrain_) {
        if (showBackgroundLayer_) {
            for (std::vector<ObjectData>::iterator it = backgroundLayer_.begin(); it != backgroundLayer_.end(); ++it) {
                DrawObject(*it);
            }
        }
        if (showPlayableLayer_) {
            for (std::vector<ObjectData>::iterator it = playableLayer_.begin(); it != playableLayer_.end(); ++it) {
                DrawObject(*it);
            }
        }
        if (showForegroundLayer_) {
            for (std::vector<ObjectData>::iterator it = foregroundLayer_.begin(); it != foregroundLayer_.end(); ++it) {
                DrawObject(*it);
            }
        }
    }

    /* Guidelines */
    HPEN hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HPEN hPenOld = (HPEN)SelectObject(graphics, hBlackPen);
 

    /* Draw cursor */
    int cx, cy;
    GetCurrentPos(cx, cy);
    int x = cx - viewport_.x;
    int y = cy - viewport_.y;

    MoveToEx(graphics, x, 0, NULL);
    LineTo(graphics, x, viewport_.height);
    MoveToEx(graphics, 0, y, NULL);
    LineTo(graphics,  viewport_.width, y);

    SelectObject(graphics, hRedPen);

    MoveToEx(graphics, 0, bottomY_ - viewport_.y, NULL);
    LineTo(graphics, viewport_.width, bottomY_ - viewport_.y);

    /* Draw spawn */
    Ellipse(graphics, playerX_ - 10 - viewport_.x, playerY_ - 10 - viewport_.y,
        playerX_ + 10 - viewport_.x, playerY_ + 10 - viewport_.y);

    TextOut(graphics, playerX_ - viewport_.x - 10, playerY_ - viewport_.y - 10, "SP", 2);

    /* END guidelines */
    SelectObject(graphics, hPenOld);
    DeleteObject(hRedPen);
    DeleteObject(hBlackPen);

    /* Draw cursor pos string */
    char buf[32];
    sprintf_s(buf, "%f, %f", cursorPos_.x, cursorPos_.y);
    TextOut(graphics, 5, 50, buf, strlen(buf));
    
    /* draw selected data */
    switch (currentLayer_) {
    case LevelManager::PLAYABLE:
        TextOut(graphics, 5, 70, "PLAYABLE", 8);
        sprintf_s(buf, "%d", playableLayer_.size());
        break;
    case LevelManager::FOREGROUND:
        TextOut(graphics, 5, 70, "FOREGROUND", 10);
        sprintf_s(buf, "%d", foregroundLayer_.size());
        break;
    case LevelManager::BACKGROUND:
        TextOut(graphics, 5, 70, "BACKGROUND", 10);
        sprintf_s(buf, "%d", backgroundLayer_.size());
        break;
    }

    TextOut(graphics, 200, 70, buf, strlen(buf));


    switch (currentObjectType_) {
    case BLOCK:
        TextOut(graphics, 5, 90, "BLOCK", 5);
        break;
    case COIN:
        TextOut(graphics, 5, 90, "COIN", 4);
        break;
    }
}

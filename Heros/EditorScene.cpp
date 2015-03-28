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
        console->log_notice("Usage: setlevelname [name]");
        return true;
    }

    console->log_notice("Level name set to %s.", cmd);
    instance->level_name(cmd);
    return true;
}
bool SetNextLevelCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".dat")) {
        console->log_error("Given path is not a .dat file.");
        console->log_notice("Usage: setnextlevel [path]");
        return true;
    }

    if (!fileExists(cmd)) {
        console->log_error("File does not exist.");
        console->log_notice("Usage: setnextlevel [path]");
        return true;
    }

    console->log_notice("Next level set to %s.", cmd);
    instance->next_level(cmd);

    return true;
}

bool SetBackgroundTextureCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".bmp")) {
        console->log_error("Given path is not a .bmp file.");
        console->log_notice("Usage: setbackgroundtexture [path]");
        return true;
    }

    if (!fileExists(cmd)) {
        console->log_error("File does not exist.");
        console->log_notice("Usage: setbackgroundtexture [path]");
        return true;
    }

    console->log_notice("Background set to %s.", cmd);
    instance->background(cmd);

    return true;
}

bool SetBackgroundOverlayTextureCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".bmp")) {
        console->log_error("Given path is not a .bmp file.");
        console->log_notice("Usage: setbackgroundoverlaytexture [path]");
        return true;
    }

    if (!fileExists(cmd)) {
        console->log_error("File does not exist.");
        console->log_notice("Usage: setbackgroundoverlaytexture [path]");
        return true;
    }

    console->log_notice("Background overlay set to %s.", cmd);
    instance->background_overlay(cmd);

    return true;
}

bool SetTerrainTextureCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".bmp")) {
        console->log_error("Given path is not a .bmp file.");
        console->log_notice("Usage: setterraintexture [path]");
        return true;
    }

    if (!fileExists(cmd)) {
        console->log_error("File does not exist.");
        console->log_notice("Usage: setterraintexture [path]");
        return true;
    }

    console->log_notice("Terrain set to %s.", cmd);
    instance->terrain(cmd);

    return true;
}

bool SetBackgroundWidthCommand(Console * const console, const char *cmd) {
    int width = atoi(cmd);

    if (width < 100) {
        console->log_error("Minimum width is 100. %d was given.", width);
        console->log_notice("Usage: setbackgroundwidth [width]");
        return true;
    }

    console->log_notice("Background width set to %d.", width);
    instance->background_width(width);

    return true;
}

bool SetBackgroundOverlayWidthCommand(Console * const console, const char *cmd) {
    int width = atoi(cmd);

    if (width < 100) {
        console->log_error("Minimum width is 100. %d was given.", width);
        console->log_notice("Usage: setbackgroundoverlaywidth [width]");
        return true;
    }

    console->log_notice("Background overlay width set to %d.", width);
    instance->background_overlay_width(width);

    return true;
}

bool SetGridSizeCommand(Console * const console, const char *cmd) {
    int size = atoi(cmd);

    if (size < 1) {
        console->log_error("Minimum grid size is 1. %d was given.", size);
        console->log_notice("Usage: setgridsize [size]");
        return true;
    }

    console->log_notice("Grid size set to %d.", size);
    instance->grid_size(size);

    return true;
}

bool SetBottomYCommand(Console * const console, const char *cmd) {
    int y = atoi(cmd);

    console->log_notice("Bottom Y set to %d", y);
    instance->bottom_y(y);

    return true;
}

bool SetEndGameXCommand(Console * const console, const char *cmd) {
    int x = atoi(cmd);

    console->log_notice("End game X set to %d", x);
    instance->end_game_x(x);

    return true;
}

bool SaveLevelCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".dat")) {
        console->log_error("Given path is not a .dat file.");
        console->log_notice("Usage: savelevel [path]");
        return true;
    }

    console->log_notice("Saving to %s...", cmd);
    instance->save(cmd);
    console->log_notice("Level saved!", cmd);

    return true;
}

bool LoadLevelCommand(Console * const console, const char *cmd) {
    std::string command = cmd;

    if (!isExtPath(cmd, ".dat")) {
        console->log_error("Given path is not a .dat file.");
        console->log_notice("Usage: loadlevel [path]");
        return true;
    }

    console->log_notice("Loading from %s...", cmd);
    instance->load(cmd);
    console->log_notice("Level loaded!", cmd);
}

bool SetPlayerSpawnCommand(Console * const console, const char *cmd) {
    int x, y;
    instance->current_pos(x, y);
    instance->player_spawn(x, y);

    console->log_notice("Player spawn set to (%d, %d).", x, y);
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
        console->log_notice("Invalid parameters.");
        console->log_notice("Usage: goto [x] [y]");
        return true;
    }

    instance->go_to(atoi(xvalue.c_str()), atoi(yvalue.c_str()));

    return true;
}

bool ToggleLayerCommand(Console * const console, const char *cmd) {
    switch (cmd[0])
    {
    case 'P':
    case 'p':
        if (instance->toggle_layer_visible(LevelManager::PLAYABLE))
            console->log_notice("The playable layer is now visible.");
        else
            console->log_notice("The playable layer is now invisible.");
        break;
    case 'B':
    case 'b':
        if (instance->toggle_layer_visible(LevelManager::BACKGROUND))
            console->log_notice("The background layer is now visible.");
        else
            console->log_notice("The background layer is now invisible.");
        break;
    case 'F':
    case 'f':
        if (instance->toggle_layer_visible(LevelManager::FOREGROUND))
            console->log_notice("The foreground layer is now visible.");
        else
            console->log_notice("The foreground layer is now invisible.");
        break;
    default:
        console->log_notice("Invalid parameters.");
        console->log_notice("Usage: togglelayer [layer]");
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
        console->log_notice("Invalid parameters.");
        console->log_notice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    int x = atoi(xvalue.c_str());
    int y = atoi(yvalue.c_str());
    int width = atoi(wvalue.c_str());
    int height = atoi(hvalue.c_str());

    if (x < 0) {
        console->log_notice("Minimum left value is 0. %d was given", x);
        console->log_notice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    if (y < 0) {
        console->log_notice("Minimum top value is 0. %d was given", y);
        console->log_notice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    if (width < 1) {
        console->log_notice("Minimum width value is 1. %d was given", width);
        console->log_notice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    if (height < 1) {
        console->log_notice("Minimum height value is 1. %d was given", height);
        console->log_notice("Usage: selecttexture [left] [top] [width] [height]");
        return true;
    }

    instance->select_texture(x, y, width, height);

    return true;
}

EditorScene::EditorScene(GameWindow *window)
    :window_(window), viewport_(Viewport(0, 0, 640, 480)) {
    instance = this;

    ZeroMemory(levelName_, MAX_LEVEL_NAME);
    ZeroMemory(backgroundPath_, MAX_TEXTURE_PATH);
    ZeroMemory(terrainPath_, MAX_TEXTURE_PATH);
    ZeroMemory(nextLevel_, MAX_LEVEL_PATH);

    window->console()->register_command("setterraintexture",
        SetTerrainTextureCommand);
    window->console()->register_command("setbackgroundtexture",
        SetBackgroundTextureCommand);
    window->console()->register_command("setbackgroundwidth",
        SetBackgroundWidthCommand);
    window->console()->register_command("setbackgroundoverlaytexture",
        SetBackgroundOverlayTextureCommand);
    window->console()->register_command("setbackgroundoverlaywidth",
        SetBackgroundOverlayWidthCommand);
    window->console()->register_command("goto", GoToCommand);
    window->console()->register_command("setbottomy", SetBottomYCommand);
    window->console()->register_command("setendgamex", SetEndGameXCommand);
    window->console()->register_command("savelevel", SaveLevelCommand);
    window->console()->register_command("loadlevel", LoadLevelCommand);
    window->console()->register_command("setplayerspawn", SetPlayerSpawnCommand);
    window->console()->register_command("setlevelname", SetLevelNameCommand);
    window->console()->register_command("setnextlevel", SetNextLevelCommand);
    window->console()->register_command("togglelayer", ToggleLayerCommand);
    window->console()->register_command("setgridsize", SetGridSizeCommand);
    window->console()->register_command("selecttexture", SelectTextureCommand);
}

EditorScene::~EditorScene() {
}

void EditorScene::load(const char *path) {
    playableLayer_.clear();
    foregroundLayer_.clear();
    backgroundLayer_.clear();
    actors_.clear();

    std::ifstream lvl;
    lvl.open(path, std::ios::in | std::ios::binary);

    LevelHeader header;
    lvl.read((char *)&header, sizeof(header));

    bottomY_ = header.bottom;
    playerX_ = header.player_x;
    playerY_ = header.player_y;

    level_name(header.name);
    background(header.background_texture);
    background_overlay(header.background_overlay_texture);
    background_width(header.background_width);
    background_overlay_width(header.background_overlay_width);
    next_level(header.next_level);
    terrain(header.terrain_texture);
    end_game_x(header.end_game_x);

    ObjectData object_buffer;
    for (int i = 0; i < header.object_count; i++) {
        lvl.read((char *)&object_buffer, sizeof(object_buffer));
        switch (object_buffer.type){
        case LevelManager::BACKGROUND:
            backgroundLayer_.push_back(object_buffer);
            break;
        case LevelManager::FOREGROUND:
            foregroundLayer_.push_back(object_buffer);
            break;
        default:
            playableLayer_.push_back(object_buffer);
            break;
        }
    }

    ActorData actor_buffer;
    for (int i = 0; i < header.actor_count; i++) {
        lvl.read((char *)&actor_buffer, sizeof(actor_buffer));
        actors_.push_back(actor_buffer);
    }
}

void EditorScene::save(const char *path) {
    LevelHeader lvl;
    lvl.bottom = bottomY_;
    lvl.player_x = playerX_;
    lvl.player_y = playerY_;
    lvl.player_abilities_ph = 0;
    sprintf_s(lvl.name, levelName_);
    sprintf_s(lvl.background_texture, backgroundPath_);
    sprintf_s(lvl.background_overlay_texture, backgroundOverlayPath_);
    sprintf_s(lvl.next_level, nextLevel_);
    lvl.background_width = backgroundWidth_;
    lvl.background_overlay_width = backgroundOverlayWidth_;
    sprintf_s(lvl.terrain_texture, terrainPath_);
    lvl.actor_count = actors_.size();
    lvl.object_count = playableLayer_.size() + foregroundLayer_.size() +
        backgroundLayer_.size();
    lvl.end_game_x = endGameX_;
    lvl.is_end_game_right = endGameX_ > playerX_;

    std::ofstream lvlout;
    lvlout.open(path, std::ios::out | std::ios::binary);

    lvlout.write((char *)&lvl, sizeof(lvl));

    for (ObjectData d : playableLayer_) {
        lvlout.write((char *)&d, sizeof(d));
    }
    for (ObjectData d : foregroundLayer_) {
        lvlout.write((char *)&d, sizeof(d));
    }
    for (ObjectData d : backgroundLayer_) {
        lvlout.write((char *)&d, sizeof(d));
    }

    for (ActorData d : actors_) {
        lvlout.write((char *)&d, sizeof(d));
    }
    lvlout.close();

}

void EditorScene::start() {
    /* useful defaults */
    background("spr/background01.bmp");
    terrain("spr/terrain.bmp");
    background_width(727);
}

void EditorScene::update(double delta, Keys keys) {

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
                currentLayer_ = LevelManager::MOVABLE;
                break;
            case LevelManager::MOVABLE:
                currentLayer_ = LevelManager::PLAYABLE;
                break;
            }
            isKeyDown_ = true;
        }
        else if (keys & KEY_O) {/* TODO: put object types in an array for a
                           little more dynimicness.*/

            if (currentLayer_ == LevelManager::MOVABLE) {
                switch (currentActorType_) {
                case DOG:
                    currentActorType_ = FLYING_ENEMIE;
                    break;
                case FLYING_ENEMIE:
                    currentActorType_ = JUMPING_ENEMIE;
                    break;
                case JUMPING_ENEMIE:
                    currentActorType_ = CHARACTER;
                    break;
                case CHARACTER:
                    currentActorType_ = DOG;
                    break;
                }
            }
            else {
                switch (currentObjectType_) {
                case BLOCK:
                    currentObjectType_ = COIN;
                    break;
                case COIN:
                    currentObjectType_ = JUMPER;
                    break;
                case JUMPER:
                    currentObjectType_ = BLOCK;
                    break;
                }
            }
            isKeyDown_ = true;
        }
    }
    else {

        isKeyDown_ = (keys & KEY_L) || (keys & KEY_O);
    }

         if (keys & KEY_JUMP) {
            if (currentLayer_ == LevelManager::MOVABLE) {
                /* Actors */
                ActorData data;
                data.type = currentActorType_;
                current_pos(data.x, data.y);

                add_actor(data);
            }
            else {
                /* Objects */
                if (currentObjectType_ != BLOCK || 
                    (selectedTexture_.width > 0 && selectedTexture_.height > 0)) {
                    ObjectData data;
                    current_pos(data.x, data.y);
                    data.layer = currentLayer_;
                    data.texture = selectedTexture_;
                    data.type = currentObjectType_;

                    if (currentObjectType_ == COIN) {
                        data.width = 12;
                        data.height = 16;
                    }
                    else if (currentObjectType_ == JUMPER) {
                        data.width = 19;
                        data.height = 20;
                    }
                    else {
                        data.width = selectedTexture_.width;
                        data.height = selectedTexture_.height;
                    }

                    add_object(current_layer(), data);
                }
            }
            isKeyDown_ = true;
        }
        if (keys & KEY_DELETE) {
            int x, y;
            current_pos(x, y);
            if (currentLayer_ == LevelManager::MOVABLE) {
                remove_actor(Vector2(x, y));
            }
            else {
                remove_object(current_layer(), Vector2(x, y));
            }
            isKeyDown_ = true;
        }
    

    /* Update viewport */
    update_viewport();
}

void EditorScene::add_object(std::vector<ObjectData> *layer, ObjectData data) {
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

void EditorScene::remove_object(std::vector<ObjectData> *layer, Vector2 pos) {
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
Vector2 EditorScene::actor_size_for_actor(ActorType type) {
    /* TODO: improve this block */
    return Vector2(16, 16);
}

void EditorScene::add_actor(ActorData data) {
    auto size = actor_size_for_actor(data.type);
    for (std::vector<ActorData>::iterator it = actors_.begin(); it != actors_.end();)
    {
        ActorData check = *it;
        auto checksize = actor_size_for_actor(check.type);
        if (!(data.x - size.x / 2 >= check.x + checksize.x / 2 ||
            data.x + size.x / 2 <= check.x - checksize.x / 2 ||
            data.y - size.y / 2 >= check.y + checksize.y / 2 ||
            data.y + size.y / 2 <= check.y - checksize.y / 2)) {
            it = actors_.erase(it);
        }
        else {
            ++it;
        }
    }

    actors_.push_back(data);
}

void EditorScene::remove_actor(Vector2 pos) {
    for (std::vector<ActorData>::iterator it = actors_.begin(); it != actors_.end();)
    {
        ActorData check = *it;
        auto checksize = actor_size_for_actor(check.type);
        if (!(pos.x >= check.x + checksize.x / 2 ||
            pos.x <= check.x - checksize.x / 2 ||
            pos.y >= check.y + checksize.y / 2 ||
            pos.y <= check.y - checksize.y / 2)) {
            it = actors_.erase(it);
        }
        else {
            ++it;
        }
    }
}

void EditorScene::update_viewport() {
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

void EditorScene::draw_object(ObjectData data) {
    switch (data.type) {
    case BLOCK:
        terrain_->draw(data.texture, Vector2(data.x, data.y), viewport_);
        break;
    case COIN:
        defaultSpriteSheet_->draw(Texture(219, 28, 12, 16), Vector2(data.x, data.y), viewport_);
        break;
    case JUMPER:
        bumperSpriteSheet_->draw(Texture(3, 11, 19, 20), Vector2(data.x, data.y), viewport_);
        break;
    }
}
void EditorScene::render(HDC graphics) {
    /* Draw background */
    const int image_width = backgroundWidth_;
    const int image2_width = backgroundOverlayWidth_;
    Texture tex = { 0, 0, image_width, viewport_.height };
    Texture tex2 = { 0, 0, image2_width, viewport_.height };
    for (int skyx = -(viewport_.x / 2) % image_width - image_width;
        skyx <= viewport_.width; skyx += image_width) {
        background_->draw(tex, skyx, 0);
    }
    if (backgroundOverlay_)
        for (int skyx = -(viewport_.x / 3) % image2_width - image2_width;
            skyx <= viewport_.width; skyx += image2_width) {
        backgroundOverlay_->draw(tex2, skyx, 0);
    }

    /* Draw terrain */
    if (terrain_) {
        if (showBackgroundLayer_) {
            for (ObjectData object : backgroundLayer_) {
                draw_object(object);
            }
        }
        if (showPlayableLayer_) {
            for (ObjectData object : playableLayer_) {
                draw_object(object);
            }
        }
        if (showForegroundLayer_) {
            for (ObjectData object : foregroundLayer_) {
                draw_object(object);
            }
        }
    }

    for (ActorData actor : actors_) {
        switch (actor.type) {
        case DOG:
            metalGearSpriteSheet_->draw(Texture(75, 280, 33, 18 ), Vector2(actor.x, actor.y), viewport_);
            break;
        case FLYING_ENEMIE:
            zeldaEnemiesSpriteSheet_->draw(Texture(56, 241, 18, 18), Vector2(actor.x, actor.y), viewport_);
            break;
        case JUMPING_ENEMIE:
            zeldaEnemiesSpriteSheet_->draw(Texture(164, 288, 12, 17), Vector2(actor.x, actor.y), viewport_);
            break;
        case CHARACTER:
            marioSpriteSheet_->draw(Texture(91, 0, 16, 28), Vector2(actor.x, actor.y), viewport_);

            break;
        }
    }

    /* Guidelines */
    HPEN hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    HPEN hPenOld = (HPEN)SelectObject(graphics, hBlackPen);
 

    /* Draw cursor */
    int cx, cy;
    current_pos(cx, cy);
    int x = cx - viewport_.x;
    int y = cy - viewport_.y;

    MoveToEx(graphics, x, 0, NULL);
    LineTo(graphics, x, viewport_.height);
    MoveToEx(graphics, 0, y, NULL);
    LineTo(graphics,  viewport_.width, y);

    SelectObject(graphics, hRedPen);

    MoveToEx(graphics, 0, bottomY_ - viewport_.y, NULL);
    LineTo(graphics, viewport_.width, bottomY_ - viewport_.y);

    SelectObject(graphics, hBluePen);
    MoveToEx(graphics, endGameX_ - viewport_.x, 0, NULL);
    LineTo(graphics, endGameX_ - viewport_.x, viewport_.height);

    /* Draw spawn */
    Ellipse(graphics, playerX_ - 10 - viewport_.x, playerY_ - 10 - viewport_.y,
        playerX_ + 10 - viewport_.x, playerY_ + 10 - viewport_.y);

    TextOut(graphics, playerX_ - viewport_.x - 10, playerY_ - viewport_.y - 10, "SP", 2);

    /* END guidelines */
    SelectObject(graphics, hPenOld);
    DeleteObject(hRedPen);
    DeleteObject(hBluePen);
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
    case LevelManager::MOVABLE:
        TextOut(graphics, 5, 70, "ACTORS", 6);
        sprintf_s(buf, "%d", actors_.size());
        break;
    }

    TextOut(graphics, 200, 70, buf, strlen(buf));


    if (currentLayer_ == LevelManager::MOVABLE) {
        switch (currentActorType_) {
        case DOG:
            TextOut(graphics, 5, 90, "DOG", 3);
            break;
        case FLYING_ENEMIE:
            TextOut(graphics, 5, 90, "FLYING_ENEMIE", 13);
            break;
        case JUMPING_ENEMIE:
            TextOut(graphics, 5, 90, "JUMPING_ENEMIE", 14);
            break;
        case CHARACTER:
            TextOut(graphics, 5, 90, "CHARACTER", 9);
            break;
        }
    }
    else {
        switch (currentObjectType_) {
        case BLOCK:
            TextOut(graphics, 5, 90, "BLOCK", 5);
            break;
        case COIN:
            TextOut(graphics, 5, 90, "COIN", 4);
            break;
        case JUMPER:
            TextOut(graphics, 5, 90, "JUMPER", 6);
            break;
        }
    }
}

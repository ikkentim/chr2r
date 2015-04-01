/**
 * EditorScene.cpp
 * Defines the EditorScene class.
 */

#include "EditorScene.h"
#include "LevelHeader.h"
#include <fstream>
#include <algorithm>
#include "Abilities.h"
#include "fileutil.h"

#define MOVEMENT_ACCEL      (0.0004)

EditorScene::EditorScene(GameWindow *window)
    :window_(window), viewport_(Viewport(0, 0, 640, 480)) {
  
    /* Clear char arrays */
	ZeroMemory(sound_, MAX_SOUND_NAME);
	ZeroMemory(backgroundPath_, MAX_TEXTURE_PATH);
	ZeroMemory(backgroundOverlayPath_, MAX_TEXTURE_PATH);
    ZeroMemory(terrainPath_, MAX_TEXTURE_PATH);
    ZeroMemory(nextLevel_, MAX_LEVEL_PATH);

    /* Fill map of game object types */
    objectTypes_[BLOCK] = GameObjectTypeData("BLOCK", 0, 0, 
        NULL, Texture(0,0,0,0));
    objectTypes_[JUMPER] = GameObjectTypeData("JUMPER", 15, 16, 
        SpriteSheet::get("spr/Bumper.bmp"), Texture(47, 14, 15, 16));
    objectTypes_[COIN] = GameObjectTypeData("COIN", 12, 16,
        SpriteSheet::get("spr/terrain.bmp"), Texture(219, 28, 12, 16));

    /* Set default game object */
    currentObjectType_ = BLOCK;

    /* Fill map of actor types */
    actorTypes_[DOG] = GameObjectTypeData("DOG", 33, 18,
        SpriteSheet::get("spr/metalgearsheet.bmp"), Texture(75, 280, 33, 18));
    actorTypes_[FLYING_ENEMIE] = GameObjectTypeData("FLYING_ENEMIE", 18, 18,
        SpriteSheet::get("spr/Zelda_Enemies_Sprite.bmp"), 
        Texture(56, 241, 18, 18));
    actorTypes_[JUMPING_ENEMIE] = GameObjectTypeData("JUMPING_ENEMIE", 12, 17,
        SpriteSheet::get("spr/Zelda_Enemies_Sprite.bmp"), 
        Texture(164, 288, 12, 17));
    actorTypes_[CHARACTER_MARIO] = GameObjectTypeData("CHARACTER_MARIO", 16, 28,
        SpriteSheet::get("spr/mario.bmp"), Texture(91, 0, 16, 28));
    actorTypes_[CHARACTER_SANIC] = GameObjectTypeData("CHARACTER_SANIC", 16, 28,
        SpriteSheet::get("spr/sonic_sheet.bmp"), Texture(391, 56, 34, 40));
    actorTypes_[CHARACTER_MAGIKARP] = GameObjectTypeData("CHARACTER_MAGIKARP", 
        16, 28, SpriteSheet::get("spr/magikarp_Sprite.bmp"), 
        Texture(10, 158, 30, 36));
	actorTypes_[CHARACTER_SNAKE] = GameObjectTypeData("CHARACTER_SNAKE",
		16, 28, SpriteSheet::get("spr/Box_Sprite.bmp"),
		Texture(76, 12, 18, 18));

    /* Set default actor type */
    currentActorType_ = DOG;
}


EditorScene::~EditorScene() {
}

void EditorScene::load(const char *path) {
    /* When loading a map, drop all known level data */
    playableLayer_.clear();
    foregroundLayer_.clear();
    backgroundLayer_.clear();
    actors_.clear();

    /* Open the file at the specified path for reading */
    std::ifstream lvl;
    lvl.open(path, std::ios::in | std::ios::binary);

    /* Read the file header */
    LevelHeader header;
    lvl.read((char *)&header, sizeof(header));

    bottomY_ = header.bottom;
    playerX_ = header.player_x;
    playerY_ = header.player_y;

    abilities_ = header.player_abilities;
    sound(header.sound);
    background(header.background_texture);
    background_overlay(header.background_overlay_texture);
    background_width(header.background_width);
    background_overlay_width(header.background_overlay_width);
    next_level(header.next_level);
    terrain(header.terrain_texture);
    end_game_x(header.end_game_x);

    /* Read the objects */
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

    /* Read athe actors */
    ActorData actor_buffer;
    for (int i = 0; i < header.actor_count; i++) {
        lvl.read((char *)&actor_buffer, sizeof(actor_buffer));
        actors_.push_back(actor_buffer);
    }
}

void EditorScene::save(const char *path) {
    /* Create the file header. */
    LevelHeader header;
    header.bottom = bottomY_;
    header.player_x = playerX_;
    header.player_y = playerY_;
    header.player_abilities = abilities_;
    header.background_width = backgroundWidth_;
    header.background_overlay_width = backgroundOverlayWidth_;
    header.end_game_x = endGameX_;
    header.is_end_game_right = endGameX_ > playerX_;

    header.actor_count = actors_.size();
    header.object_count = playableLayer_.size() 
        + foregroundLayer_.size()
        + backgroundLayer_.size();

    sprintf_s(header.sound, sound_);
    sprintf_s(header.background_texture, backgroundPath_);
    sprintf_s(header.background_overlay_texture, backgroundOverlayPath_);
    sprintf_s(header.next_level, nextLevel_);
    sprintf_s(header.terrain_texture, terrainPath_);

    /* Open the file at the specified path for writing. */
    std::ofstream lvlout;
    lvlout.open(path, std::ios::out | std::ios::binary);

    /* Write the header to the file. */
    lvlout.write((char *)&header, sizeof(header));

    /* Write the objects to the file. */
    for (ObjectData d : playableLayer_) {
        lvlout.write((char *)&d, sizeof(d));
    }
    for (ObjectData d : foregroundLayer_) {
        lvlout.write((char *)&d, sizeof(d));
    }
    for (ObjectData d : backgroundLayer_) {
        lvlout.write((char *)&d, sizeof(d));
    }

    /* Write the actors to the file. */
    for (ActorData d : actors_) {
        lvlout.write((char *)&d, sizeof(d));
    }

    /* Close the file. */
    lvlout.close();

}

void EditorScene::start() {
    /* Set useful defaults */
    background("spr/background01.bmp");
    terrain("spr/terrain.bmp");
    background_width(727);

    /* Register all level editor commands to the console. When the scene is
     * changed the commands will automatically be unregistered from the console
     * by the game window. */

    /* Create a reference to 'this' scene for use in the lamba code later on. */
    EditorScene * const editorScene = this;

    /* Command: setterraintexture [path] 
     * Sets the path to the terrain texture used for every BLOCK game object for
     * the current level. */
    window_->console()->register_command("setterraintexture",
        [editorScene](Console * const console, const char * args) -> bool {
        if (!has_extension(args, ".bmp")) {
            console->log_error("Given path is not a .bmp file.");
            console->log_notice("Usage: setterraintexture [path]");
            return true;
        }

        if (!file_exists(args)) {
            console->log_error("File does not exist.");
            console->log_notice("Usage: setterraintexture [path]");
            return true;
        }

        console->log_notice("Terrain set to %s.", args);
        editorScene->terrain(args);
        return true;
    });

    /* Command: setbackgroundtexture [path]
     * Sets the background texture for the current level. */
    window_->console()->register_command("setbackgroundtexture",
        [editorScene](Console * const console, const char * args) -> bool {
        if (!has_extension(args, ".bmp")) {
            console->log_error("Given path is not a .bmp file.");
            console->log_notice("Usage: setbackgroundtexture [path]");
            return true;
        }

        if (!file_exists(args)) {
            console->log_error("File does not exist.");
            console->log_notice("Usage: setbackgroundtexture [path]");
            return true;
        }

        console->log_notice("Background set to %s.", args);
        editorScene->background(args);
        return true;
    });

    /* Command: setbackgroundwidth [width]
     * Sets the size of the background texture for the current level. */
    window_->console()->register_command("setbackgroundwidth",
        [editorScene](Console * const console, const char * args) -> bool {
        int width = atoi(args);

        if (width < 100) {
            console->log_error("Minimum width is 100. %d was given.", width);
            console->log_notice("Usage: setbackgroundwidth [width]");
            return true;
        }

        console->log_notice("Background width set to %d.", width);
        editorScene->background_width(width);
        return true;
    });

    /* Command: setbackgroundoverlaytexture [path]
     * Sets the background overlay texture for the current level. The background
     * overlay is drawn over the background in a parallelish way. */
    window_->console()->register_command("setbackgroundoverlaytexture",
        [editorScene](Console * const console, const char * args) -> bool {
        if (!has_extension(args, ".bmp")) {
            console->log_error("Given path is not a .bmp file.");
            console->log_notice("Usage: setbackgroundoverlaytexture [path]");
            return true;
        }

        if (!file_exists(args)) {
            console->log_error("File does not exist.");
            console->log_notice("Usage: setbackgroundoverlaytexture [path]");
            return true;
        }

        console->log_notice("Background overlay set to %s.", args);
        editorScene->background_overlay(args);
        return true;
    });
    /* Command: clearbackgroundoverlaytexture 
     * Removes background overlay textures set using 
     * setbackgroundoverlaytexture. */
    window_->console()->register_command("clearbackgroundoverlaytexture",
        [editorScene](Console * const console, const char * args) -> bool {
        console->log_notice("Background overlay removed.");
        editorScene->background_overlay("");
        return true;
    });

    /* Command: setbackgroundoverlaywidth [width]
     * Sets the size of the background overlay texture for the current level. */
    window_->console()->register_command("setbackgroundoverlaywidth",
        [editorScene](Console * const console, const char * args) -> bool {
        int width = atoi(args);

        if (width < 100) {
            console->log_error("Minimum width is 100. %d was given.", width);
            console->log_notice("Usage: setbackgroundoverlaywidth [width]");
            return true;
        }

        console->log_notice("Background overlay width set to %d.", width);
        editorScene->background_overlay_width(width);
        return true;
    });
    /* Command: goto [x] [y]
     * Moves the cursor to the specified x and y coordinates */
    window_->console()->register_command("goto",
        [editorScene](Console * const console, const char * args) -> bool {
        std::string command = args;

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

        editorScene->go_to(atoi(xvalue.c_str()), atoi(yvalue.c_str()));
        return true;
    });
    /* Command: setbottomy [y]
     * Sets the y-coordinate under which the player dies. */
    window_->console()->register_command("setbottomy",
        [editorScene](Console * const console, const char * args) -> bool {
        int y = atoi(args);

        console->log_notice("Bottom Y set to %d", y);
        editorScene->bottom_y(y);
        return true;
    });
    /* Command: setendgamex [x]
     * Sets the x-coordinate the player needs to pass to proceed to the next 
     * level. */
    window_->console()->register_command("setendgamex",
        [editorScene](Console * const console, const char * args) -> bool {
        int x = atoi(args);

        console->log_notice("End game X set to %d", x);
        editorScene->end_game_x(x);
        return true;
    });
    /* Command: savelevel [path]
     * Saves the current level to the specified path. */
    window_->console()->register_command("savelevel",
        [editorScene](Console * const console, const char * args) -> bool {
        if (!has_extension(args, ".dat")) {
            console->log_error("Given path is not a .dat file.");
            console->log_notice("Usage: savelevel [path]");
            return true;
        }

        console->log_notice("Saving to %s...", args);
        editorScene->save(args);
        console->log_notice("Level saved!", args);
        return true;
    });
    /* Command: loadlevel [path]
     * Loads a level from the specified path. */
    window_->console()->register_command("loadlevel",
        [editorScene](Console * const console, const char * args) -> bool {
        std::string command = args;

        if (!strlen(args)) {
            console->log_notice("Usage: loadlevel [path]");
            return true;
        }

        if (!has_extension(args, ".dat")) {
            console->log_error("Given path is not a .dat file.");
            console->log_notice("Usage: loadlevel [path]");
            return true;
        }

        if (!file_exists(args)) {
            console->log_error("File does not exist");
            console->log_notice("Usage: loadlevel [path]");
            return true;
        }

        console->log_notice("Loading from %s...", args);
        editorScene->load(args);
        console->log_notice("Level loaded!", args);
        return true;
    });
    /* Command: setplayerspawn
     * Sets the CURRENT x- and y-coordinates of the cursor to as the player 
     * spawn. */
    window_->console()->register_command("setplayerspawn",
        [editorScene](Console * const console, const char * args) -> bool {
        int x, y;
        editorScene->current_pos(x, y);
        editorScene->player_spawn(x, y);

        console->log_notice("Player spawn set to (%d, %d).", x, y);
        return true;
    });
    /* Command: setsound [path]
     * Sets the file at the specified path as the sound played while playing
     * the current level. */
    window_->console()->register_command("setsound",
        [editorScene](Console * const console, const char * args) -> bool {
        if (strlen(args) == 0) {
            console->log_notice("Usage: setsound [path]");
            return true;
        }

        if (!file_exists(args)) {
            console->log_error("File does not exist.");
            console->log_notice("Usage: setsound [path]");
            return true;
        }

        console->log_notice("Sound set to %s.", args);
        editorScene->sound(args);
        return true;
    });
    /* Command: setnextlevel [path]
     * Sets the path to the next level. If none is specified, we assume there
     * is no next map. */
    window_->console()->register_command("setnextlevel",
        [editorScene](Console * const console, const char * args) -> bool {
        if (!has_extension(args, ".dat")) {
            console->log_error("Given path is not a .dat file.");
            console->log_notice("Usage: setnextlevel [path]");
            return true;
        }

        if (!file_exists(args)) {
            console->log_error("File does not exist.");
            console->log_notice("Usage: setnextlevel [path]");
            return true;
        }

        console->log_notice("Next level set to %s.", args);
        editorScene->next_level(args);
        return true;
    });
    /* Command: clearnextlevel
     * Remove the previously set next level (using setnextlevel). */
    window_->console()->register_command("clearnextlevel",
        [editorScene](Console * const console, const char * args) -> bool {
        editorScene->next_level("");
        console->log_notice("Removed next level.");
        return true;
    });
    /* Command togglelayer [layer]
     * Toggles the visibility of the specified layer. */
    window_->console()->register_command("togglelayer",
        [editorScene](Console * const console, const char * args) -> bool {
        switch (args[0])
        {
        case 'P':
        case 'p':
            if (editorScene->toggle_layer_visible(LevelManager::PLAYABLE))
                console->log_notice("The playable layer is now visible.");
            else
                console->log_notice("The playable layer is now invisible.");
            break;
        case 'B':
        case 'b':
            if (editorScene->toggle_layer_visible(LevelManager::BACKGROUND))
                console->log_notice("The background layer is now visible.");
            else
                console->log_notice("The background layer is now invisible.");
            break;
        case 'F':
        case 'f':
            if (editorScene->toggle_layer_visible(LevelManager::FOREGROUND))
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
    });
    /* Command: toggleability [ability]
     * Toggles the availability of the specified ability at the start of the 
     * map. */
    window_->console()->register_command("toggleability",
        [editorScene](Console * const console, const char * args) -> bool {

        if (!strcmp(args, "sneak")) {
            if (editorScene->toggle_ability_type(ABILITY_SNEAK))
                console->log_notice("Sneaking is now available");
            else
                console->log_notice("Sneaking is now unavailable");
        }
        else if (!strcmp(args, "jump")) {
            if (editorScene->toggle_ability_type(ABILITY_JUMP))
                console->log_notice("Jumping is now available");
            else
                console->log_notice("Jumping is now unavailable");

        }
        else if (!strcmp(args, "sprint")) {
            if (editorScene->toggle_ability_type(ABILITY_SPRINT))
                console->log_notice("Sprinting is now available");
            else
                console->log_notice("Sprinting is now unavailable");

        }
        else if (!strcmp(args, "splash")) {
            if (editorScene->toggle_ability_type(ABILITY_SPLASH))
                console->log_notice("Splashing is now available");
            else
                console->log_notice("Splashing is now unavailable");

        }
        else if (!strcmp(args, "duck")) {
            if (editorScene->toggle_ability_type(ABILITY_DUCK))
                console->log_notice("Ducking is now available");
            else
                console->log_notice("Ducking is now unavailable");

        }
        else {
            console->log_notice("Invalid parameters.");
            console->log_notice(
                "Usage: toggleability [ability:sneak|jump|sprint|splash|duck]");
        }

        return true;
    });
    /* Command: setgridsize [size]
     * Sets the pixels the cursors jumps at when moving.
     */
    window_->console()->register_command("setgridsize",
        [editorScene](Console * const console, const char * args) -> bool {
        int size = atoi(args);

        if (size < 1) {
            console->log_error("Minimum grid size is 1. %d was given.", size);
            console->log_notice("Usage: setgridsize [size]");
            return true;
        }

        console->log_notice("Grid size set to %d.", size);
        editorScene->grid_size(size);
        return true;
    });

    /* Command: selecttexture [left] [top] [width] [height]
     * Selects the texture used for the next BLOCK placed. */
    window_->console()->register_command("selecttexture",
        [editorScene](Console * const console, const char * args) -> bool {
        std::string command = args;


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
            console->log_notice(
                "Usage: selecttexture [left] [top] [width] [height]");
            return true;
        }

        int x = atoi(xvalue.c_str());
        int y = atoi(yvalue.c_str());
        int width = atoi(wvalue.c_str());
        int height = atoi(hvalue.c_str());

        if (x < 0) {
            console->log_notice("Minimum left value is 0. %d was given", x);
            console->log_notice(
                "Usage: selecttexture [left] [top] [width] [height]");
            return true;
        }

        if (y < 0) {
            console->log_notice("Minimum top value is 0. %d was given", y);
            console->log_notice(
                "Usage: selecttexture [left] [top] [width] [height]");
            return true;
        }

        if (width < 1) {
            console->log_notice("Minimum width value is 1. %d was given",
                width);
            console->log_notice(
                "Usage: selecttexture [left] [top] [width] [height]");
            return true;
        }

        if (height < 1) {
            console->log_notice("Minimum height value is 1. %d was given",
                height);
            console->log_notice(
                "Usage: selecttexture [left] [top] [width] [height]");
            return true;
        }

        editorScene->select_texture(x, y, width, height);
        return true;
    });
}

void EditorScene::update(double delta, Keys keys) {
    auto accel = MOVEMENT_ACCEL * max(1, gridSize_ / 4) * delta;

    /* Process movement keys. */
    if (keys & KEY_LEFT)
        cursorVelocity_.x -= accel;
    else if (cursorVelocity_.x < 0)
        cursorVelocity_.x = 0;

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

    /* Process layer/object switch keys. */
    if (!isKeyDown_) {
        /* L key: Select the next layer. */
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
        /* O key: Select the next available object*/
        else if (keys & KEY_O) {
            /* Find the next available object/actor type in the map. 
            * If none are available use the first type in the map.*/

            if (currentLayer_ == LevelManager::MOVABLE) {
                auto it = actorTypes_.find(currentActorType_);
                currentActorType_ = ++it == actorTypes_.end()
                    ? (*actorTypes_.begin()).first
                    : (*it).first;
            }
            else {
                auto it = objectTypes_.find(currentObjectType_);
                currentObjectType_ = ++it == objectTypes_.end()
                    ? (*objectTypes_.begin()).first
                    : (*it).first;
            }
            isKeyDown_ = true;
        }
    }
    else { /* (!isKeyDown_) */
        isKeyDown_ = (keys & KEY_L) || (keys & KEY_O);
    }

    /* Process placement key. */
    if (keys & KEY_JUMP) {
        if (currentLayer_ == LevelManager::MOVABLE) {
            /* Place an actor. */
            ActorData data;
            data.type = currentActorType_;
            current_pos(data.x, data.y);

            add_actor(data);
        }
        else {
            /* Place an object. */

            /* If the current object type is BLOCK, and no texture is selected,
             * do not place the object.
             */
            if (currentObjectType_ != BLOCK ||
                (selectedTexture_.width > 0 && selectedTexture_.height > 0)) {
                ObjectData data;
                current_pos(data.x, data.y);
                data.layer = currentLayer_;
                data.texture = selectedTexture_;
                data.type = currentObjectType_;

                if (currentObjectType_ == BLOCK) {
                    data.width = selectedTexture_.width;
                    data.height = selectedTexture_.height;
                }
                else {
                    data.width = objectTypes_[currentObjectType_].width;
                    data.height = objectTypes_[currentObjectType_].height;
                }

                add_object(current_layer(), data);
            }
        }
        isKeyDown_ = true;
    }

    /* Process deletion key. */
    if (keys & KEY_DELETE) {
        int x, y;
        current_pos(x, y);

        if (currentLayer_ == LevelManager::MOVABLE) 
            remove_actor(Vector2(x, y));
        else 
            remove_object(current_layer(), Vector2(x, y));
        
        isKeyDown_ = true;
    }


    /* Update viewport */
    update_viewport();
}

void EditorScene::add_object(std::vector<ObjectData> *layer, ObjectData data) {
    /* Find objects at the position we're trying to place an object and delete
     * these. */
    for (auto it = layer->begin(); it != layer->end();)
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
    /* Find objects at the specified position and delete these. */
    for (auto it = layer->begin(); it != layer->end();)
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

void EditorScene::add_actor(ActorData data) {
    /* Find actors at the position we're trying to place an actor and delete
    * these. */
    auto size = Vector2(actorTypes_[data.type].width, 
        actorTypes_[data.type].height);
    for (auto it = actors_.begin(); it != actors_.end();)
    {
        ActorData check = *it;
        auto checksize = Vector2(actorTypes_[check.type].width, 
            actorTypes_[check.type].height);
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
    /* Find actors at the specified position and delete these. */
    for (auto it = actors_.begin(); it != actors_.end();)
    {
        ActorData check = *it;
        auto checksize = Vector2(actorTypes_[check.type].width,
            actorTypes_[check.type].height);
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
    /* Minimum distance between window edge and the player. */
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

void EditorScene::render(HDC graphics) {
    /* Draw background. */
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

    /* Draw terrain. */
    if (terrain_) {
        if (showBackgroundLayer_) {
            for (ObjectData object : backgroundLayer_) {
                auto data = objectTypes_[object.type];
                if (data.spriteSheet) {
                    data.spriteSheet->draw(data.texture,
                        Vector2(object.x, object.y), viewport_);
                }
                else {
                    terrain_->draw(object.texture,
                        Vector2(object.x, object.y), viewport_);
                }
            }
        }
        if (showPlayableLayer_) {
            for (ObjectData object : playableLayer_) {
                auto data = objectTypes_[object.type];
                if (data.spriteSheet) {
                    data.spriteSheet->draw(data.texture,
                        Vector2(object.x, object.y), viewport_);
                }
                else {
                    terrain_->draw(object.texture,
                        Vector2(object.x, object.y), viewport_);
                }
            }
        }
        if (showForegroundLayer_) {
            for (ObjectData object : foregroundLayer_) {
                auto data = objectTypes_[object.type];
                if (data.spriteSheet) {
                    data.spriteSheet->draw(data.texture,
                        Vector2(object.x, object.y), viewport_);
                }
                else {
                    terrain_->draw(object.texture,
                        Vector2(object.x, object.y), viewport_);
                }
            }
        }
    }

    for (ActorData actor : actors_) {
        auto data = actorTypes_[actor.type];
        data.spriteSheet->draw(data.texture,
            Vector2(actor.x, actor.y), viewport_);
    }

    /* Pens used... */
    HPEN hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    HPEN hPenOld = (HPEN)SelectObject(graphics, hBlackPen);


    /* Draw cursor. */
    int cx, cy;
    current_pos(cx, cy);
    int x = cx - viewport_.x;
    int y = cy - viewport_.y;

    MoveToEx(graphics, x, 0, NULL);
    LineTo(graphics, x, viewport_.height);
    MoveToEx(graphics, 0, y, NULL);
    LineTo(graphics, viewport_.width, y);

    /* Draw bottom y. */
    SelectObject(graphics, hRedPen);

    MoveToEx(graphics, 0, bottomY_ - viewport_.y, NULL);
    LineTo(graphics, viewport_.width, bottomY_ - viewport_.y);

    /* Draw end game x. */
    SelectObject(graphics, hBluePen);
    MoveToEx(graphics, endGameX_ - viewport_.x, 0, NULL);
    LineTo(graphics, endGameX_ - viewport_.x, viewport_.height);

    /* Draw spawn. */
    Ellipse(graphics, playerX_ - 10 - viewport_.x, playerY_ - 10 - viewport_.y,
        playerX_ + 10 - viewport_.x, playerY_ + 10 - viewport_.y);

    TextOut(graphics, playerX_ - viewport_.x - 10, playerY_ - viewport_.y - 10, 
        "SP", 2);

    /* Delete pens used for guidelines */
    SelectObject(graphics, hPenOld);
    DeleteObject(hRedPen);
    DeleteObject(hBluePen);
    DeleteObject(hBlackPen);

    /* Draw cursor pos string. */
    char buf[32];
    sprintf_s(buf, "%f, %f", cursorPos_.x, cursorPos_.y);
    TextOut(graphics, 5, 50, buf, strlen(buf));

    /* Draw selection information. */
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
        char * name = actorTypes_[currentActorType_].name;
        TextOut(graphics, 5, 90, name, strlen(name));
    }
    else {
        char * name = objectTypes_[currentObjectType_].name;
        TextOut(graphics, 5, 90, name, strlen(name));
    }
}


void EditorScene::background(const char *background) {
    strcpy_s(backgroundPath_, background);
    background_ = SpriteSheet::get(background);
}

void EditorScene::background_overlay(const char *background) {
    strcpy_s(backgroundOverlayPath_, background);
    backgroundOverlay_ = SpriteSheet::get(background);
}

void EditorScene::terrain(const char *terrain) {
    strcpy_s(terrainPath_, terrain);
    terrain_ = SpriteSheet::get(terrain);
}

void EditorScene::sound(const char *path) {
    strcpy_s(sound_, path);
}

void EditorScene::next_level(const char *path) {
    strcpy_s(nextLevel_, path);
}

void EditorScene::background_width(int backgroundWidth) {
    backgroundWidth_ = backgroundWidth;
}

void EditorScene::background_overlay_width(int backgroundWidth) {
    backgroundOverlayWidth_ = backgroundWidth;
}

void EditorScene::bottom_y(int y) {
    bottomY_ = y;
}

void EditorScene::go_to(int x, int y) {
    cursorPos_.x = x;
    cursorPos_.y = y;
}

void EditorScene::end_game_x(int x) {
    endGameX_ = x;
}

void EditorScene::player_spawn(int x, int y) {
    playerX_ = x;
    playerY_ = y;
}

void EditorScene::current_pos(int &x, int &y) {
    x = ((int)cursorPos_.x / gridSize_) * gridSize_;
    y = ((int)cursorPos_.y / gridSize_) * gridSize_;
}

void EditorScene::grid_size(int size) {
    gridSize_ = size;
}

void EditorScene::select_texture(int left, int top, int width, int height) {
    selectedTexture_.left = left;
    selectedTexture_.top = top;
    selectedTexture_.width = width;
    selectedTexture_.height = height;
}

bool EditorScene::toggle_layer_visible(LevelManager::Layer layer) {
    switch (layer) {
    case LevelManager::PLAYABLE:
        return showPlayableLayer_ = !showPlayableLayer_;
    case LevelManager::FOREGROUND:
        return showForegroundLayer_ = !showForegroundLayer_;
    case LevelManager::BACKGROUND:
        return showBackgroundLayer_ = !showBackgroundLayer_;
    }

    return false;
}

bool EditorScene::toggle_ability_type(Abilities type) {
    abilities_ = abilities_ ^ type;
    return !!(abilities_ & type);
}

std::vector<ObjectData> *EditorScene::current_layer() {
    switch (currentLayer_) {
    case LevelManager::FOREGROUND:
        return &foregroundLayer_;
    case LevelManager::BACKGROUND:
        return &backgroundLayer_;
    default:
        return &playableLayer_;
    }
}
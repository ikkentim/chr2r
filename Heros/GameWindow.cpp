#include "GameWindow.h"
#include <typeinfo>
#include <hidsdi.h>

#include "SpriteSheet.h"
#include "SplashScene.h"
#include "GameScene.h"
#include "LevelManager.h"
#include <string>

#define MAX_HID_BUTTONS     (64)
GameWindow::GameWindow() {
}

GameWindow::~GameWindow() {
    if (scene_)
        delete scene_;
}

void GameWindow::UpdateScene(Scene *scene) {
	if (scene_){
		delete scene_;
	}

	soundEngine_->stopAllSounds();

	scene_ = scene;
	scene_->Start();
}

irrklang::ISoundEngine *GameWindow::SoundEngine() {
	return soundEngine_;
}

void GameWindow::GameInit() {
    SpriteSheet::SetWindow(hWnd_, graphics_);

    /* Create handle of sound engine. */
    soundEngine_ = irrklang::createIrrKlangDevice(); 
    assert(soundEngine_ && "Sound engine failed to load (missing resources?)");
    soundEngine_->setSoundVolume(0.3f);/* Master Volume. */

    scene_ = new SplashScene(this);
	scene_->Start();

    /* Get display refresh rate */
    DEVMODE mode;
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);

    int refresh_rate = mode.dmDisplayFrequency;
    if (refresh_rate < 30)
        refresh_rate = 30;
    frameInterval_ = 1.0f / refresh_rate;

    /* Register window for HID updates. */
    RAWINPUTDEVICE rid;

    rid.usUsagePage = 1;
    rid.usUsage = 4; /* joystick */
    rid.dwFlags = 0;
    rid.hwndTarget = hWnd_;

    hasJoystick_ = !!RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE));

}

void GameWindow::GameEnd() {
    SpriteSheet::Unload();
    soundEngine_->drop();
}

bool GameWindow::GameLoop(double delta) {
	/* Check whether it is time to render another frame. */
    timeSinceRender_ += delta;

    if (timeSinceRender_ >= frameInterval_) {
        timeSinceRender_ -= frameInterval_;

        scene_->Render(delta, graphics_);
        fps.Update();

#ifdef SHOW_FPS
        TCHAR buf[16];
        sprintf_s(buf, "FPS: %d", fps.GetFps());
        TextOut(graphics_, 5, 5, buf, strlen(buf));

        sprintf_s(buf, "UPS: %d", ups.GetFps());
        TextOut(graphics_, 5, 25, buf, strlen(buf));
#endif
        /* Tell the window to repaint. */
        return true;
    }
	else {
		/* Handle key presses. */
#define MAP_KEY(vk,map); if(GetAsyncKeyState(vk)) { \
	keys_ |= map; } else if (keys_ & map) { \
	keys_ ^= map; }

		MAP_KEY(VK_LEFT, KEY_LEFT);
		MAP_KEY(VK_RIGHT, KEY_RIGHT);
		MAP_KEY(VK_UP, KEY_UP);
		MAP_KEY(VK_DOWN, KEY_DOWN);
		MAP_KEY(VK_SPACE, KEY_JUMP);

#undef MAP_KEY

		/* Simple statement for using ESCAPE to exit. If LSHIFT or LCONTROL is
		* pressed, ESCAPE won't close the window.
		*/

		if (::GetAsyncKeyState(VK_ESCAPE)
			&& !GetAsyncKeyState(VK_LSHIFT)
			&& !GetAsyncKeyState(VK_LCONTROL))
			::exit(0);

		/* This restart button leaks pretty badly but it's useful. */
		if (::GetAsyncKeyState(VK_F5)) {
            soundEngine_->stopAllSounds();

			/* FIXME: Fix leak in LevelManager. (initializer/destructor) */
			while (::GetAsyncKeyState(VK_F5));
			UpdateScene(new GameScene(this));
		}

        scene_->Update(delta, keys_ | joystickKeys_);
		ups.Update();

        return false;
    }
}

/* Handles WM_INPUT for HID input. */
LRESULT GameWindow::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, 
    LPARAM lParam) {
    switch (uMsg) {
    case WM_INPUT:
    {
        UINT bufferSize;

        /* Code is long'n messy. Should look for a way to clean this up a bit.
         * 
         * In the code below we assume all memory allocations are successful.
         */

        /* No joystick? No joy. */
        if (!hasJoystick_) return 0;

        /* Fill a buffer with the raw input data. */
        GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL,
            &bufferSize, sizeof(RAWINPUTHEADER));

        PRAWINPUT rawInput = (PRAWINPUT)new char[bufferSize];
        GetRawInputData((HRAWINPUT)lParam, RID_INPUT,
            rawInput, &bufferSize, sizeof(RAWINPUTHEADER));

        /* Fill a buffer with the raw input device info. */
        if (GetRawInputDeviceInfo(rawInput->header.hDevice, RIDI_PREPARSEDDATA,
            NULL, &bufferSize) != 0) {
            delete[] rawInput;
            return 0;
        }

        PHIDP_PREPARSED_DATA preparsedData = 
            (PHIDP_PREPARSED_DATA)new char[bufferSize];

        if ((int)GetRawInputDeviceInfo(rawInput->header.hDevice,
            RIDI_PREPARSEDDATA, preparsedData, &bufferSize) < 0) {
            delete[] rawInput;
            delete[] preparsedData;
            return 0;
        }

        /* Get the capabilities of the device. */
        HIDP_CAPS capabilities;
        if (HidP_GetCaps(preparsedData, &capabilities) != HIDP_STATUS_SUCCESS) {
            delete[] rawInput;
            delete[] preparsedData;
            return 0;
        }

        /* Get the capabilities of the buttons. */
        PHIDP_BUTTON_CAPS buttonCapabilities = (PHIDP_BUTTON_CAPS)new char[
            sizeof(HIDP_BUTTON_CAPS) * capabilities.NumberInputButtonCaps];

        if (HidP_GetButtonCaps(HidP_Input, buttonCapabilities,
            &capabilities.NumberInputButtonCaps, preparsedData) != 
            HIDP_STATUS_SUCCESS) {
            delete[] rawInput;
            delete[] preparsedData;
            delete[] buttonCapabilities;
            return 0;
        }

        /* Get the used buttons. */
        ULONG usageLength = buttonCapabilities->Range.UsageMax -
            buttonCapabilities->Range.UsageMin + 1;
        USAGE usedButtons[MAX_HID_BUTTONS];
        if (HidP_GetUsages(HidP_Input, buttonCapabilities->UsagePage, 0, usedButtons,
            &usageLength, preparsedData, (PCHAR)rawInput->data.hid.bRawData,
            rawInput->data.hid.dwSizeHid) != HIDP_STATUS_SUCCESS) {
            delete[] rawInput;
            delete[] preparsedData;
            delete[] buttonCapabilities;
            return 0;
        }

        /* Get the capabilities of the values (axes). */
        PHIDP_VALUE_CAPS valueCapabilities = (PHIDP_VALUE_CAPS)new char[
            sizeof(HIDP_VALUE_CAPS) * capabilities.NumberInputValueCaps];
        if (HidP_GetValueCaps(HidP_Input, valueCapabilities,
            &capabilities.NumberInputValueCaps, preparsedData) != 
            HIDP_STATUS_SUCCESS) {
            delete[] rawInput;
            delete[] preparsedData;
            delete[] buttonCapabilities;
            delete[] valueCapabilities;
            return 0;
        }

        /* Set button states. */
        bool buttonStates[MAX_HID_BUTTONS] = { false };
        for (ULONG i = 0; i < usageLength; i++)
            buttonStates[usedButtons[i] - buttonCapabilities->Range.UsageMin] = true;

        /* Get x/y axis values. */
        LONG lAxisX = 0;
        LONG lAxisY = 0;
        ULONG value;
        for (ULONG i = 0; i < capabilities.NumberInputValueCaps; i++) {
            if (HidP_GetUsageValue(HidP_Input, valueCapabilities[i].UsagePage, 0,
                valueCapabilities[i].Range.UsageMin, &value, preparsedData,
                (PCHAR)rawInput->data.hid.bRawData,
                rawInput->data.hid.dwSizeHid) == HIDP_STATUS_SUCCESS) {
                switch (valueCapabilities[i].Range.UsageMin)
                {
                case 0x30:
                    lAxisX = (LONG)value - 127;
                    break;

                case 0x31:
                    lAxisY = (LONG)value - 127;
                    break;
                }
            }
        }
        
        /* Process data to keys. */
        if (lAxisX < 0)
            joystickKeys_ |= KEY_LEFT;
        else if (joystickKeys_ & KEY_LEFT)
            joystickKeys_ ^= KEY_LEFT;

        if (lAxisX > 0)
            joystickKeys_ |= KEY_RIGHT;
        else if (joystickKeys_ & KEY_RIGHT)
            joystickKeys_ ^= KEY_RIGHT;

        if (lAxisY < 0)
            joystickKeys_ |= KEY_UP;
        else if (joystickKeys_ & KEY_UP)
            joystickKeys_ ^= KEY_UP;

        if (lAxisY > 0)
            joystickKeys_ |= KEY_DOWN;
        else if (joystickKeys_ & KEY_DOWN)
            joystickKeys_ ^= KEY_DOWN;

        /* KEYMAP:        /
         *      4        /       5
         *   /----------------------\
         *  /  ^                0    \
         * | <   >            3   1   |
         *  \  v      8   9     2    /
         *   \----------------------/ 
         */

        /* 'A'-key (jump) */
        if (buttonStates[1])
            joystickKeys_ |= KEY_JUMP;
        else if (joystickKeys_ & KEY_JUMP)
            joystickKeys_ ^= KEY_JUMP;

        /* Free memory from heap. */
        delete[] preparsedData;
        delete[] buttonCapabilities;
        delete[] valueCapabilities;
        delete[] rawInput;
    }
    return 0;
    default:
        return Window::MsgProc(hWnd, uMsg, wParam, lParam);
    }
}
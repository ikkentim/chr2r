#include "Console.h"
#include <stdio.h>
#include <assert.h>

#define LINE_HEIGHT         (15)
#define CONSOLE_WIDTH       (640)
#define CONSOLE_HEIGHT      (480)
#define CONSOLE_TYPE_WIDTH  (64)

Console *instance;

bool commandscmd(const char *cmd) {
    instance->LogAvailableCommands();

    return true;
}
bool exitcmd(const char *cmd) {
    exit(0);
    return true;
}

Console::Console(HDC hdc) {
    instance = this;

    dc_ = CreateCompatibleDC(hdc);
    bitmap_ = CreateCompatibleBitmap(hdc, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    oldHandle_ = SelectObject(dc_, bitmap_);

    for (int i = 0; i < CONSOLE_LOG_COUNT; i++) {
        ZeroMemory(consoleTypeBuffer_[i], CONSOLE_TYPE_BUFFER_SIZE);
        ZeroMemory(consoleBuffer_[i], CONSOLE_BUFFER_SIZE);
    }

    ClearInputBuffer();

    RegisterCommand("exit", exitcmd);
    RegisterCommand("commands", commandscmd);
}

void Console::LogAvailableCommands() {
    LogNotice("Available commands:");
    for (std::map<std::string, ConsoleCommandHandler>::iterator iterator = commands_.begin(); iterator != commands_.end(); iterator++) {
        auto name = iterator->first;

        char buffer[CONSOLE_BUFFER_SIZE];
        sprintf(buffer, "  %s", name.c_str());

        LogNotice(buffer);
    }
}

void Console::ClearInputBuffer() {
    ZeroMemory(inputBuffer_, CONSOLE_BUFFER_SIZE);
    inputPos_ = 0;
}

void Console::ProcessCommand(char *command) {
    std::string cmd = command;

    LogUserInput(command);

    if (cmd.length() == 0) {
        LogNotice("invalid command.");
        return;
    }

    while (cmd.find(' ') == 0) cmd.erase(0);

    int sp = cmd.find(' ');
    if (sp == -1) sp = cmd.length();
    
    std::string cmdword = cmd.substr(0, sp);

    if (commands_.find(cmdword) == commands_.end()) {
        LogNotice("invalid command.");
        return;
    }

    auto rest = cmd.substr(sp, cmd.length() - sp);
    auto func = commands_[cmdword];

    if (!func(rest.c_str())) {
        LogNotice("invalid command.");
        return;
    }
}

void Console::SendInputCommand() {
    if (inputPos_ == 0) return;

    ProcessCommand(inputBuffer_);
    ClearInputBuffer();
}

void Console::LogNotice(char *message) {
    Log(message, "notice", RGB(100, 255, 100));
}

void Console::LogWarn(char *message) {
    Log(message, "warn", RGB(255, 127, 42));
}

void Console::LogError(char *message) {
    Log(message, "error", RGB(255, 0, 0));
}

void Console::LogUserInput(char *message) {
    Log(message, "input", RGB(255, 255, 255));
}

bool Console::RegisterCommand(std::string name, ConsoleCommandHandler handler) {
    assert(handler);
    assert(name.length() < 32);

    if (commands_.find(name) != commands_.end()) {
        return false;
    }

    commands_[name] = handler;
}

void Console::Log(char *message, char *type, COLORREF color) {

    strcpy(consoleTypeBuffer_[consolePos_], type);
    strcpy(consoleBuffer_[consolePos_], message);
    consoleTypeColor_[consolePos_++] = color;

    consolePos_ %= CONSOLE_LOG_COUNT;
}
void Console::Update(WPARAM wParam) {
    char input = MapVirtualKey(wParam, MAPVK_VK_TO_CHAR);

    if (input == 0) return; /* invalid keys */
    if (input >= 'A' && input <= 'Z' && !GetAsyncKeyState(VK_SHIFT))
        input -= 'A' - 'a';

    if (!isOpen_) {
        isOpen_ = input == '`';

        return;
    }

    if (input == '`') {
        isOpen_ = false;
        ClearInputBuffer();
    }

    switch (wParam) {
    case VK_BACK:
        if (inputPos_ > 0)
            inputBuffer_[--inputPos_] = '\0';
        break;
    case VK_RETURN:
        SendInputCommand();
        break;
    default:
        if (inputPos_ < CONSOLE_BUFFER_SIZE)
            inputBuffer_[inputPos_++] = input;
    }

}

void Console::Render(HDC hdc) {
    if (!isOpen_) return;

    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = CONSOLE_WIDTH;
    r.bottom = CONSOLE_HEIGHT;
    COLORREF color = RGB(15, 15, 15);

    SetBkMode(dc_, TRANSPARENT);
    HBRUSH hbr = CreateSolidBrush(color);
    FillRect(dc_, &r, hbr);

    /* Log lines */
    for (int i = 0; i < CONSOLE_LOG_COUNT; i++) {
        int y = CONSOLE_HEIGHT - LINE_HEIGHT * 2 - i * LINE_HEIGHT;

        int rpos = ((CONSOLE_LOG_COUNT - i) + consolePos_ - 1) % CONSOLE_LOG_COUNT;

        char buffer[CONSOLE_TYPE_BUFFER_SIZE + 2];
        sprintf(buffer, "[%s]", consoleTypeBuffer_[rpos]);

        SetTextColor(dc_, consoleTypeColor_[rpos]);
        TextOut(dc_, 0, y, buffer, strlen(buffer));

        SetTextColor(dc_, RGB(255, 255, 255));
        TextOut(dc_, CONSOLE_TYPE_WIDTH, y, consoleBuffer_[rpos], strlen(consoleBuffer_[rpos]));
    }

    TextOut(dc_, 0, CONSOLE_HEIGHT - LINE_HEIGHT, inputBuffer_, strlen(inputBuffer_));

    AlphaBlend(hdc, 0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT, dc_, 0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT, { AC_SRC_OVER, 0, 200, 0 });
    DeleteObject(hbr);
}
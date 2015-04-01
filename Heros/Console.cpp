/**
 * Console.cpp
 * Defines the Console class.
 */

#include "Console.h"
#include <assert.h>

#define LINE_HEIGHT         (15)
#define CONSOLE_WIDTH       (640)
#define CONSOLE_HEIGHT      (480)
#define CONSOLE_TYPE_WIDTH  (64)

Console::Console(HDC hdc) {
    dc_ = CreateCompatibleDC(hdc);
    bitmap_ = CreateCompatibleBitmap(hdc, CONSOLE_WIDTH, CONSOLE_HEIGHT);
    oldHandle_ = SelectObject(dc_, bitmap_);

    for (int i = 0; i < CONSOLE_LOG_COUNT; i++) {
        ZeroMemory(consoleTypeBuffer_[i], CONSOLE_TYPE_BUFFER_SIZE);
        ZeroMemory(consoleBuffer_[i], CONSOLE_BUFFER_SIZE);
    }

    clear_input_buffer();
    log_notice("Type 'commands' to view all commands.");
}

void Console::reset_commands() {
    commands_.clear();
    register_command("commands", 
        [](Console * const console, const char * args) -> bool {
        console->log_available_commands();
        return true;
    });
}
void Console::log_available_commands() {
    log_notice("Available commands:");
    for (auto & kv : commands_) {
        auto name = kv.first;

        char buffer[CONSOLE_BUFFER_SIZE];
        sprintf_s(buffer, "  %s", name.c_str());

        log_notice(buffer);
    }
}

void Console::clear_input_buffer() {
    ZeroMemory(inputBuffer_, CONSOLE_BUFFER_SIZE);
    inputPos_ = 0;
}

void Console::process_command(char *command) {
    std::string cmd = command;

    log_user_input(command);

    if (cmd.length() == 0) {
        log_notice("invalid command.");
        return;
    }

    while (cmd.find(' ') == 0) cmd.erase(0, 1);

    int sp = cmd.find(' ');
    if (sp == -1) sp = cmd.length();
    
    std::string cmdword = cmd.substr(0, sp);

    if (commands_.find(cmdword) == commands_.end()) {
        log_notice("invalid command.");
        return;
    }
    auto func = commands_[cmdword];

    cmd.erase(0, sp);

    while (cmd.find(' ', 0) == 0) cmd.erase(0, 1);

    if (!func(this, cmd.c_str())) {
        log_notice("invalid command.");
        return;
    }
}

void Console::send_input_command() {
    if (inputPos_ == 0) return;

    process_command(inputBuffer_);
    clear_input_buffer();
}

void Console::log_notice(const char *format, ...) {
    va_list args;
    va_start(args, format);
    log(format, args, "notice", RGB(100, 255, 100));
    va_end(args);
}

void Console::log_warn(const char *format, ...) {
    va_list args;
    va_start(args, format);
    log(format, args, "warn", RGB(255, 127, 42));
    va_end(args);
}

void Console::log_error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    log(format, args, "error", RGB(255, 0, 0));
    va_end(args);
}

void Console::log_user_input(const char *message) {
    log(message, "input", RGB(255, 255, 255));
}

void Console::log(const char *format, va_list args, char *type, 
    COLORREF color) {
    char buffer[CONSOLE_BUFFER_SIZE];

    vsnprintf_s(buffer, CONSOLE_BUFFER_SIZE, format, args);
    log(buffer, type, color);
}

void Console::log(const char *message, char *type, COLORREF color) {

    strcpy_s(consoleTypeBuffer_[consolePos_], type);
    strcpy_s(consoleBuffer_[consolePos_], message);
    consoleTypeColor_[consolePos_++] = color;

    consolePos_ %= CONSOLE_LOG_COUNT;
}

bool Console::register_command(std::string name, 
    ConsoleCommandHandler handler) {
    assert(handler);
    assert(name.length() < 32);

    if (commands_.find(name) != commands_.end()) {
        log_warn("Registration of %s command failed; Command exists already", 
            name.c_str());
        return false;
    }

    commands_[name] = handler;

    return true;
}

void Console::remove_command(std::string name) {
    if (commands_.find(name) != commands_.end())
        commands_.erase(name);
}

void Console::update(WPARAM wParam) {
    char input = MapVirtualKey(wParam, MAPVK_VK_TO_CHAR);

    if (!isOpen_) {
        isOpen_ = wParam == VK_TAB || wParam == VK_OEM_3;
        return;
    }

    if (wParam == VK_TAB || wParam == VK_OEM_3) {
        isOpen_ = false;
        clear_input_buffer();
        return;
    }


    if (input == '\0'|| input == '`') return; /* invalid keys */
    if (input >= 'A' && input <= 'Z' && !GetAsyncKeyState(VK_SHIFT))
        input -= 'A' - 'a';

    switch (wParam) {
    case VK_BACK:
        if (inputPos_ > 0)
            inputBuffer_[--inputPos_] = '\0';
        break;
    case VK_RETURN:
        send_input_command();
        break;
    default:
        if (inputPos_ < CONSOLE_BUFFER_SIZE)
            inputBuffer_[inputPos_++] = input;
    }

}

void Console::render(HDC hdc) {
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

        int rpos = ((CONSOLE_LOG_COUNT - i) + consolePos_ - 1) 
            % CONSOLE_LOG_COUNT;

        if (!strlen(consoleBuffer_[rpos]))
            continue;

        char buffer[CONSOLE_TYPE_BUFFER_SIZE + 2];
        sprintf_s(buffer, "[%s]", consoleTypeBuffer_[rpos]);

        SetTextColor(dc_, consoleTypeColor_[rpos]);
        TextOut(dc_, 0, y, buffer, strlen(buffer));

        SetTextColor(dc_, RGB(255, 255, 255));
        TextOut(dc_, CONSOLE_TYPE_WIDTH, y, consoleBuffer_[rpos], 
            strlen(consoleBuffer_[rpos]));
    }

    TextOut(dc_, 0, CONSOLE_HEIGHT - LINE_HEIGHT, inputBuffer_, 
        strlen(inputBuffer_));

    AlphaBlend(hdc, 0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT, dc_, 0, 0, 
        CONSOLE_WIDTH, CONSOLE_HEIGHT, { AC_SRC_OVER, 0, 200, 0 });
    DeleteObject(hbr);
}
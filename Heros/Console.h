    #pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <functional>

#define CONSOLE_LOG_COUNT           (64)
#define CONSOLE_BUFFER_SIZE         (256)
#define CONSOLE_TYPE_BUFFER_SIZE    (32)

typedef std::function<bool(class Console * const console, const char * args)>
    ConsoleCommandHandler;

class Console
{
public:
    Console(HDC);
    void update(WPARAM);
    void render(HDC);
    bool register_command(std::string, ConsoleCommandHandler);
    void remove_command(std::string);
    void reset_commands();
    void log_notice(const char *, ...);
    void log_warn(const char *, ...);
    void log_error(const char *, ...);
    void log_available_commands();

    bool is_open() {
        return isOpen_;
    }

private:
    void log_user_input(const char *);
    void log(const char *format, va_list args, char *type, COLORREF color);
    void log(const char *message, char *type, COLORREF color);
    void process_command(char *);
    void send_input_command();
    void clear_input_buffer();

    HDC dc_ = NULL;
    HBITMAP bitmap_;
    HANDLE oldHandle_;
    COLORREF consoleTypeColor_[CONSOLE_LOG_COUNT];
    char consoleTypeBuffer_[CONSOLE_LOG_COUNT][CONSOLE_TYPE_BUFFER_SIZE];
    char consoleBuffer_[CONSOLE_LOG_COUNT][CONSOLE_BUFFER_SIZE];
    char inputBuffer_[CONSOLE_BUFFER_SIZE];
    int consolePos_ = 0;
    int inputPos_ = 0;
    bool isOpen_ = false;
    std::map<std::string, ConsoleCommandHandler> commands_;
};
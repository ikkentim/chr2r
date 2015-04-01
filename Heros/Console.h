/**
 * Console.h
 * Declares the Console class.
 */
#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <functional>

#define CONSOLE_LOG_COUNT           (64)
#define CONSOLE_BUFFER_SIZE         (256)
#define CONSOLE_TYPE_BUFFER_SIZE    (32)

// Represents a console
class Console
{
public:
    // A function to handle console commands
    typedef std::function<bool(class Console * const console, const char * args)>
        ConsoleCommandHandler;

    // A constructor for the specified graphics handle
    Console(HDC hDc);

    // Updates based on the specified wparam
    void update(WPARAM wParam);

    // Renders the graphics to the specified handle
    void render(HDC hDc);

    // Registers a command
    bool register_command(std::string, ConsoleCommandHandler);

    // Removes a registered command
    void remove_command(std::string);

    // Removes all commands
    void reset_commands();

    // Logs a notice
    void log_notice(const char *, ...);

    // Logs a warning
    void log_warn(const char *, ...);

    // Logs an error
    void log_error(const char *, ...);

    // Logs all available commands
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
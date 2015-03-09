#pragma once
#include <Windows.h>
#include <map>
#include <string>

#define CONSOLE_LOG_COUNT           (64)
#define CONSOLE_BUFFER_SIZE         (256)
#define CONSOLE_TYPE_BUFFER_SIZE    (32)

typedef bool(*ConsoleCommandHandler)(class Console * const, const char *);

class Console
{
public:
    Console(HDC);

    void Update(WPARAM);
    void Render(HDC);
    bool IsOpen() {
        return isOpen_;
    }
    void LogNotice(const char *, ...);
    void LogWarn(const char *, ...);
    void LogError(const char *, ...);
    void LogAvailableCommands();
    bool RegisterCommand(std::string, ConsoleCommandHandler);
    void RemoveCommand(std::string);
private:
    void LogUserInput(const char *);
    void Log(const char *format, va_list args, char *type, COLORREF color);
    void Log(const char *message, char *type, COLORREF color);
    HDC dc_ = NULL;
    HBITMAP bitmap_;
    HANDLE oldHandle_;
    void ProcessCommand(char *);
    void SendInputCommand();
    void ClearInputBuffer();

    COLORREF consoleTypeColor_[CONSOLE_LOG_COUNT];
    char consoleTypeBuffer_[CONSOLE_LOG_COUNT][CONSOLE_TYPE_BUFFER_SIZE];
    char consoleBuffer_[CONSOLE_LOG_COUNT][CONSOLE_BUFFER_SIZE];
    char inputBuffer_[CONSOLE_BUFFER_SIZE];
    int consolePos_ = 0;
    int inputPos_ = 0;
    bool isOpen_ = false;
    std::map<std::string, ConsoleCommandHandler> commands_;
};
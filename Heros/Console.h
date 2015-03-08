#pragma once
#include <Windows.h>
#include <map>
#include <string>

#define CONSOLE_LOG_COUNT           (64)
#define CONSOLE_BUFFER_SIZE         (256)
#define CONSOLE_TYPE_BUFFER_SIZE    (32)

typedef bool(*ConsoleCommandHandler)(const char *);
class Console
{
public:
    Console(HDC);

    void Update(WPARAM);
    void Render(HDC);
    bool IsOpen() {
        return isOpen_;
    }
    void LogNotice(char *);
    void LogWarn(char *);
    void LogError(char *);
    void LogAvailableCommands();
    bool RegisterCommand(std::string, ConsoleCommandHandler);
private:
    void LogUserInput(char *);
    void Log(char *message, char *type, COLORREF color);
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
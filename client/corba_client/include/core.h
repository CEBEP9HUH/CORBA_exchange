#pragma once


#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#else
    #include "include/consoleRawMode.h"
#endif
#include "CORBAClient.h"

class Core
{
private:
    CORBAClient _client;
public:
    Core() = delete;
    Core(const Core&) = delete;
    Core(const Core&&) = delete;
    Core& operator=(const Core&) = delete;
    Core& operator=(const Core&&) = delete;
    Core(int argc, char** argv);
    ~Core() = default;
    void run();
};

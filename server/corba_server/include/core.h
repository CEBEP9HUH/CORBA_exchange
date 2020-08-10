#pragma once
#include "CORBAServer.h"

class Core
{
private:
    CORBAServer _server;
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

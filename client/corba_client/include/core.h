#pragma once


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

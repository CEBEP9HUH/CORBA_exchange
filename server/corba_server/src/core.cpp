#include "include/core.h"

Core::Core(int argc, char** argv) : _server{argc, argv} {

}

void Core::run(){
    _server.init();
}

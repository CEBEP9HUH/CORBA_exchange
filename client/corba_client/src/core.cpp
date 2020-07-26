#include "include/core.h"

Core::Core(int argc, char** argv) : _client{argc, argv} {

}

void Core::run(){
    if(_client.init()){
        ConsoleRawMode::enableRawMode();
        char c;
        while(true){
            if (read(STDIN_FILENO, &c, 1) == 1) {
                _client.send(static_cast<CORBA::Char>(c));
                if(c==10){
                    _client.send(13);
                }
            }
        }
    }
}

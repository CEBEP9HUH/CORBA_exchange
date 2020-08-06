#include "include/core.h"

Core::Core(int argc, char** argv) : _client{argc, argv} {

}


#if defined(_WIN32) || defined(_WIN64)

void Core::run(){
    if(_client.init()){
        char c;
        while(true){
            c = _getch();
            _client.send(static_cast<CORBA::Char>(c));
            if(c==10){
                _client.send(13);
            }
        }
    }
}

#else

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

#endif

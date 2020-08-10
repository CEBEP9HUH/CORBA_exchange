#include "include/core.h"

Core::Core(int argc, char** argv) : _client{argc, argv} {

}


#if defined(_WIN32) || defined(_WIN64)

#include <conio.h>
#include <cstdlib>
#include <iostream>

void Core::run(){
    if(_client.init()){
        char c;
        while(true){
            c = _getche();
            _client.send(static_cast<CORBA::Char>(c));
            if(c=='\r'){
                _client.send('\n');
                std::cout << '\n';
            }
        }
    }
}

#else
#include "include/consoleRawMode.h"

void Core::run(){
    if(_client.init()){
        ConsoleRawMode::enableRawMode();
        char c;
        while(true){
            if (read(STDIN_FILENO, &c, 1) == 1) {
                _client.send(static_cast<CORBA::Char>(c));
                if(c=='\r'){
                    _client.send('\n');
                }
            }
        }
    }
}

#endif

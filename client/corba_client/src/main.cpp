#include <QTextStream>
#include "../../idl/sendFunc.hh"
//-------------------------------------------


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
struct termios orig_termios;
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ICANON);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


//---
static CORBA::Object_ptr getObjRef(CORBA::ORB_ptr orb);

static void send(sendToServer_ptr e, CORBA::Char src){
    e->sendCharToServer(src);
}

void corbaInit(int argc, char *argv[]){
    QTextStream tStream(stdout);
    try {
      CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
      CORBA::Object_var obj = getObjRef(orb);
      sendToServer_var echoref = sendToServer::_narrow(obj);
      for(unsigned char i=0; i<26; i++){
          CORBA::Char ch = 'a'+i;
          send(echoref, ch);
      }
      orb->destroy();
    }
    catch (CORBA::Exception& ex) {
      tStream << "Caught CORBA::Exception: " << ex._name() << endl;
    }
}
#include<iostream>

int main(int argc, char *argv[]){
    QTextStream tStream(stdout);
    CORBA::ORB_var orb;
    sendToServer_var sender;
    try {
        orb = CORBA::ORB_init(argc, argv);
        CORBA::Object_var obj = getObjRef(orb);
        sender = sendToServer::_narrow(obj);
    }
    catch (CORBA::Exception& ex) {
        tStream << "Caught CORBA::Exception: " << ex._name() << endl;
    }

    enableRawMode();
    char c;
    while(1)
        if (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
          //if (!iscntrl(c)) {
            //printf("%c\r\n", c);
            send(sender, c);
            if(c==13)
                send(sender, 10);
            if(c == '!'){
                break;
           // }
      }
    }
    disableRawMode();

    orb->destroy();
    return 0;
}

static CORBA::Object_ptr getObjRef(CORBA::ORB_ptr orb){
    QTextStream tStream(stdout);
    CosNaming::NamingContext_var rootContext;
    try {
        CORBA::Object_var obj = orb->resolve_initial_references("NameService");

        rootContext = CosNaming::NamingContext::_narrow(obj);

        if(CORBA::is_nil(rootContext)){
            tStream << "root context is nil" << endl;
            return CORBA::Object::_nil();
        }

        CosNaming::Name name;
        name.length(2);
        name[0].id = "sending_context";
        name[0].kind = "context";
        name[1].id = "sender";
        name[1].kind = "object";

        return rootContext->resolve(name);
    }
    catch (CORBA::Exception& ex) {
        tStream << "Caught CORBA::Exception: " << ex._name() << endl;
    }
    return CORBA::Object::_nil();
}

#include <QTextStream>
#include "../../idl/sendFunc.hh"

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
    char qch;
    QTextStream ttStream(stdin);
    while(1){
       ttStream >> qch;
       send(sender, static_cast<unsigned char>(qch));
       if(qch == '!'){
           break;
       }
    }
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

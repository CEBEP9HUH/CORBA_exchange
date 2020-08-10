#include "include/CORBAClient.h"

CORBAClient::CORBAClient(int argc, char** argv) : _orb{CORBA::ORB_init(argc, argv)} {
}

CORBAClient::~CORBAClient(){
    _orb->destroy();
}

bool CORBAClient::init(){
    _obj = getObjRef();
    if(_obj == CORBA::Object::_nil()){
        return false;
    }
    _sender = sendToServer::_narrow(_obj);
    return true;
}

CORBA::Object_ptr CORBAClient::getObjRef(){
    CosNaming::NamingContext_var rootContext;
    CORBA::Object_var obj = _orb->resolve_initial_references("NameService");
    rootContext = CosNaming::NamingContext::_narrow(obj);
    if(CORBA::is_nil(rootContext)){
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

void CORBAClient::send(CORBA::Char ch){
    _sender->sendCharToServer(ch);
}

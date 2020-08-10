#include "include/CORBAServer.h"

CORBAServer::CORBAServer(int argc, char** argv) : _orb{CORBA::ORB_init(argc, argv)} {

}


CORBAServer::~CORBAServer(){

}


bool CORBAServer::init(){
    _obj = _orb->resolve_initial_references("RootPOA");
    _poa = PortableServer::POA::_narrow(_obj);
    _sender = new sendToServer_i();
    PortableServer::ObjectId_var sender_id = _poa->activate_object(_sender);
    _obj = _sender->_this();
    if(!bindObjToName()){
        return false;
    }
    PortableServer::POAManager_var pman = _poa->the_POAManager();
    pman->activate();
    _orb->run();
    return true;
}


bool CORBAServer::bindObjToName(){
    CosNaming::NamingContext_var rootContext;
    // root context initialization
    CORBA::Object_var obj = _orb->resolve_initial_references("NameService");
    rootContext = CosNaming::NamingContext::_narrow(obj);

    if(CORBA::is_nil(rootContext)){
        return 0;
    }

    // custom context binding
    CosNaming::Name contextName;
    contextName.length(1);
    contextName[0].id = "sending_context";
    contextName[0].kind = "context";

    CosNaming::NamingContext_var sendingContext;
    try {
        sendingContext = rootContext->bind_new_context(contextName);
    }
    catch(CosNaming::NamingContext::AlreadyBound& ex) {
        CORBA::Object_var obj = rootContext->resolve(contextName);
        sendingContext = CosNaming::NamingContext::_narrow(obj);
        if (CORBA::is_nil(rootContext)) {
          return 0;
        }
    }

    // object to custom context binding
    CosNaming::Name objectName;
    objectName.length(1);
    objectName[0].id = "sender";
    objectName[0].kind = "object";
    try {
        sendingContext->bind(objectName, _obj);
    }
    catch(CosNaming::NamingContext::AlreadyBound& ex) {
        sendingContext->rebind(objectName, _obj);
    }
    return 1;
}

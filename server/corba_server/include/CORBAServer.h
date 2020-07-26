#pragma once
#include "sendtoserver.h"

class CORBAServer{
private:
    CORBA::ORB_var _orb;
    CORBA::Object_var _obj;
    PortableServer::Servant_var<sendToServer_i> _sender;
    PortableServer::POA_var _poa;
    bool bindObjToName();
public:
    CORBAServer() = delete;
    CORBAServer(CORBAServer&) = delete;
    CORBAServer(CORBAServer&&) = delete;
    CORBAServer& operator=(CORBAServer&) = delete;
    CORBAServer& operator=(CORBAServer&&) = delete;
    CORBAServer(int argv, char** argc);
    ~CORBAServer();
    bool init();
    void send(CORBA::Char ch);
};

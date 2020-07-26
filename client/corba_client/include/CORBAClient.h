#pragma once
#include "../../idl/sendToServer.hh"

class CORBAClient{
private:
    CORBA::ORB_var _orb;
    CORBA::Object_var _obj;
    sendToServer_var _sender;
    CORBA::Object_ptr getObjRef();
public:
    CORBAClient() = delete;
    CORBAClient(CORBAClient&) = delete;
    CORBAClient(CORBAClient&&) = delete;
    CORBAClient& operator=(CORBAClient&) = delete;
    CORBAClient& operator=(CORBAClient&&) = delete;
    CORBAClient(int argv, char** argc);
    ~CORBAClient();
    bool init();
    void send(CORBA::Char ch);
};


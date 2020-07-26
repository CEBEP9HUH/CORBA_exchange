#pragma once
#include "../../idl/sendToServer.hh"


class sendToServer_i : public POA_sendToServer{
public:
    inline sendToServer_i() = default;
    virtual ~sendToServer_i() override = default;
    virtual void sendCharToServer(CORBA::Char character) override;
};

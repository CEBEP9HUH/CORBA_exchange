#include <QTextStream>
#include "../../idl/sendFunc.hh"

static CORBA::Boolean bindObjToName(CORBA::ORB_ptr orb, CORBA::Object_ptr objref);

class sendToServer_i : public POA_sendToServer{
public:
    inline sendToServer_i() = default;
    virtual ~sendToServer_i() override = default;
    virtual CORBA::Char sendCharToServer(CORBA::Char character) override;
};

CORBA::Char sendToServer_i::sendCharToServer(::CORBA::Char character){
    QTextStream tStream(stdout);
    tStream << QChar(character);
    return CORBA::Char(character);
}

int main(int argc, char** argv)
{
    QTextStream tStream(stdout);
    try{
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
        CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

        PortableServer::Servant_var<sendToServer_i> sender = new sendToServer_i();

        PortableServer::ObjectId_var sender_id = poa->activate_object(sender);

        obj = sender->_this();

        if(!bindObjToName(orb, obj)){
            return 1;
        }

        PortableServer::POAManager_var pman = poa->the_POAManager();
        pman->activate();

        orb->run();
    }
    catch(CORBA::Exception& e){
        tStream << e._name() << endl;
    }
    return 0;
  }

static CORBA::Boolean bindObjToName(CORBA::ORB_ptr orb, CORBA::Object_ptr objref){
    QTextStream tStream(stdout);
    CosNaming::NamingContext_var rootContext;
    try {
        // root context initialization
        CORBA::Object_var obj = orb->resolve_initial_references("NameService");
        rootContext = CosNaming::NamingContext::_narrow(obj);

        if(CORBA::is_nil(rootContext)){
            return 0;
        }

        // custom context binding
        CosNaming::Name contextName;
        contextName.length(1);
        contextName[0].id = "sending_context";
        contextName[0].kind = "context";

        CosNaming::NamingContext_var sendingContext = rootContext->bind_new_context(contextName);

        // object to custom context binding
        CosNaming::Name objectName;
        objectName.length(1);
        objectName[0].id = "sender";
        objectName[0].kind = "object";

        sendingContext->bind(objectName, objref);
    }
    catch(CORBA::Exception& e){
        tStream << e._name() << endl;
        return 0;
    }
    return 1;
}

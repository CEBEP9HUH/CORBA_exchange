#include <QTextStream>
#include "idl/echo.hh"

class Echo_i : public POA_Echo{
public:
    inline Echo_i() = default;
    virtual ~Echo_i() override = default;
    virtual char* echoString(const char* mesg) override;
};

char* Echo_i::echoString(const char *mesg){
    QTextStream tStream(stdout);
    tStream << "Upcall: " << mesg << endl;
    return CORBA::string_dup("Tyrannosaurus!");
}

void hello(CORBA::Object_ptr obj){
    Echo_var e = Echo::_narrow(obj);
    QTextStream tStream(stdout);
    if(CORBA::is_nil(e)){
        tStream << "cannot invoke on a nil object reference." << endl;
        return;
    }
    CORBA::String_var src = static_cast<const char *>("Hello!");
    CORBA::String_var dest;
    dest = e->echoString(src);

    tStream << "I said, \"" << src << "\"."
            << "The object said, \"" << dest << "\"." << endl;
}

int main(int argc, char** argv)
{
    QTextStream tStream(stdout);
    try {
      CORBA::ORB_var          orb = CORBA::ORB_init(argc, argv);
      CORBA::Object_var       obj = orb->resolve_initial_references("RootPOA");
      PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

      PortableServer::Servant_var<Echo_i> myecho = new Echo_i();

      PortableServer::ObjectId_var myechoid = poa->activate_object(myecho);

      // Obtain a reference to the object, and print it out as a
      // stringified IOR.
      obj = myecho->_this();
      CORBA::String_var sior(orb->object_to_string(obj));
      tStream << sior << endl;

      PortableServer::POAManager_var pman = poa->the_POAManager();
      pman->activate();

      // Block until the ORB is shut down.
      orb->run();
    }
    catch (CORBA::SystemException& ex) {
      tStream << "Caught CORBA::" << ex._name() << endl;
    }
    catch (CORBA::Exception& ex) {
      tStream << "Caught CORBA::Exception: " << ex._name() << endl;
    }
    return 0;
  }

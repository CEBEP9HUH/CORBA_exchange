#include <QTextStream>
#include "idl/echo.hh"

static void hello(Echo_ptr e)
{
    QTextStream tStream(stdout);
    CORBA::String_var src = static_cast<const char*>("Veloceraptor!");
    CORBA::String_var dest = e->echoString(src);
    tStream << "I said, \"" << static_cast<char*>(src) << "\"." << endl
        << "The Echo object replied, \"" << static_cast<char*>(dest) <<"\"." << endl;
}

int main(int argc, char *argv[])
{
    QTextStream tStream(stdout);
    try {
      CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

      if (argc != 2) {
        tStream << "usage:  eg2_clt <object reference>" << endl;
        return 1;
      }

      CORBA::Object_var obj = orb->string_to_object(argv[1]);

      Echo_var echoref = Echo::_narrow(obj);

      if (CORBA::is_nil(echoref)) {
        tStream << "Can't narrow reference to type Echo (or it was nil)." << endl;
        return 1;
      }

      for (CORBA::ULong count=0; count<10; count++)
        hello(echoref);

      orb->destroy();
    }
    catch (CORBA::TRANSIENT&) {
      tStream << "Caught system exception TRANSIENT -- unable to contact the "
           << "server." << endl;
    }
    catch (CORBA::SystemException& ex) {
      tStream << "Caught a CORBA::" << ex._name() << endl;
    }
    catch (CORBA::Exception& ex) {
      tStream << "Caught CORBA::Exception: " << ex._name() << endl;
    }
    return 0;
}

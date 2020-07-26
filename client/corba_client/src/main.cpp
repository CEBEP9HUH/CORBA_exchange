#include <QTextStream>
#include "include/core.h"

int main(int argc, char **argv){
    QTextStream tStream(stdout);
    try {
        Core core(argc, argv);
        core.run();
    } catch (std::exception& ex) {
        tStream << ex.what() << endl;
    } catch (CORBA::Exception& ex) {
        tStream << ex._name() << endl;
    }
    return 0;
}

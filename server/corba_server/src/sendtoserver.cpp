#include <QTextStream>
#include "include/sendtoserver.h"

void sendToServer_i::sendCharToServer(CORBA::Char character){
    QTextStream out(stdout);
    out << QChar(character);
}

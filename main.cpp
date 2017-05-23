#include <QCoreApplication>
#include <QDebug>

#include "macro.h"

#define FUNCTION(name) void name(int i);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << TOSTR(FIRST(1, 2, 3))   << "SHOULD BE 1";
    qDebug() << TOSTR(FIRST()0)         << "SHOULD BE 0";

    qDebug() << TOSTR(REST(1, 2))       << "SHOULD BE 2";
    qDebug() << TOSTR(REST(1)0)         << "SHOULD BE 0";

    qDebug() << TOSTR(ISEMPTY_())       << "SHOULD BE 1";
    qDebug() << TOSTR(ISEMPTY_(1))      << "SHOULD BE 0";

    qDebug() << ISEMPTY()               << "SHOULD BE 1";
    qDebug() << ISEMPTY(1, 4, 3)        << "SHOULD BE 0";

    qDebug() << NOT(ISEMPTY(arg1, arg2, arg3)) << "SHOULD BE 1";

    qDebug() << WHEN(NOT(ISEMPTY(arg1, arg2, arg3))) ( TOSTR(Correct) );
    qDebug() << WHEN(NOT(ISEMPTY())) ( TOSTR(Incorrect) ) "Correct";

    qDebug() << TOSTR(FOR_EACH(ECHO, arg1, arg2, arg3)) << "SHOULD BE arg1, arg2, arg3";
    qDebug() << TOSTR(FOR_EACH(ECHO, arg1)) << "SHOULD BE arg1";

    qDebug() << COUNT()                 << "SHOULD BE 0";
    qDebug() << COUNT(arg1)             << "SHOULD BE 1";
    qDebug() << COUNT(arg1, arg2)       << "SHOULD BE 2";

    qDebug() << TOSTR(FOR_EACH(FUNCTION, func1)) << "SHOULD BE void func1();";

    qDebug() << TOSTR(FOR_EACH(FUNCTION, func1, func2, func3, func4, func5, func6));

    return a.exec();
}

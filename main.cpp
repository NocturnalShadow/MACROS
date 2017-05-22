#include <QCoreApplication>
#include <QDebug>

#define VOID()
#define EXPAND(...) __VA_ARGS__
#define DEFER(macro) macro VOID()
#define STRINGIFY(...) #__VA_ARGS__

#define TOSTR(...) EXPAND(DEFER(STRINGIFY)(__VA_ARGS__))

#define PROBE(x) x, 1,
#define xxx 1, 2

#define func(a, b) a + b


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << TOSTR(xxx);
    qDebug() << EXPAND(DEFER(func)(xxx));

    return a.exec();
}

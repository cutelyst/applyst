#ifndef APPLYST_H
#define APPLYST_H

#include <Cutelyst/Application>

using namespace Cutelyst;

class Applyst : public Application
{
    Q_OBJECT
    CUTELYST_APPLICATION(IID "org.cutelyst.applyst"
                             "")
public:
    Q_INVOKABLE explicit Applyst(QObject *parent = 0);
    ~Applyst();

    bool init();
};

#endif // APPLYST_H

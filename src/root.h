#ifndef ROOT_H
#define ROOT_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

namespace Appstream {
class Database;
}

class Root : public Controller
{
    Q_OBJECT
    C_NAMESPACE("")
    public:
        explicit Root(QObject *parent = 0);
    ~Root();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);

    C_ATTR(search, :Local :AutoArgs)
    void search(Context *c);

    C_ATTR(app, :Local :AutoArgs)
    void app(Context *c, const QString &id);

    C_ATTR(defaultPage, :Path)
    void defaultPage(Context *c);

private:
    C_ATTR(End, :ActionClass("RenderView"))
    void End(Context *c) { Q_UNUSED(c); }

    Appstream::Database *m_db;
};

#endif // ROOT_H

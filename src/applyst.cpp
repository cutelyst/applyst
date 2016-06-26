#include "applyst.h"

#include <Cutelyst/Plugins/StaticSimple/staticsimple.h>
#include <Cutelyst/Plugins/View/Grantlee/grantleeview.h>

#include "root.h"

using namespace Cutelyst;

Applyst::Applyst(QObject *parent) : Application(parent)
{
}

Applyst::~Applyst()
{
}

bool Applyst::init()
{
    new Root(this);

    new StaticSimple(this);

    auto view = new GrantleeView(this);
    view->setIncludePaths({ pathTo({ QStringLiteral("root"), QStringLiteral("src") }) });
    view->setWrapper(QStringLiteral("base.html"));
    view->setCache(false);

    return true;
}


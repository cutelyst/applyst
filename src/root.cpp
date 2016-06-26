#include "root.h"

//using namespace Cutelyst;
using namespace Appstream;

#include <AppstreamQt/database.h>
#include <AppstreamQt/component.h>
#include <AppstreamQt/screenshot.h>
#include <AppstreamQt/image.h>

#include <QDebug>

Root::Root(QObject *parent) : Cutelyst::Controller(parent)
{
    m_db = new Appstream::Database;
    if (!m_db->open()) {
        qWarning() << "Failed to open Appstream db" << m_db->errorString();
    }
}

Root::~Root()
{
}

QVariantMap componentToMap(const Appstream::Component &component)
{
    QVariantMap app;
    app.insert(QStringLiteral("id"), component.id());
    app.insert(QStringLiteral("name"), component.name());
    QString icon = component.iconUrl(QSize(64, 64)).toLocalFile();
    icon.remove(QStringLiteral("/var/lib/app-info/"));
    app.insert(QStringLiteral("icon"), icon);
    app.insert(QStringLiteral("summary"), component.summary());
    app.insert(QStringLiteral("description"), component.description());
    QList<Appstream::Screenshot> screenshots =  component.screenshots();
//    qDebug() << component.name() << component.icon() << component.iconUrl(QSize(64, 64)) << component.summary();
    if (!screenshots.isEmpty()) {
        QList<Appstream::Image> images = screenshots.first().images();
        if (!images.isEmpty()) {
//            qDebug() << images.first().kind() << images.first().url();
            app.insert(QStringLiteral("screenshot"), images.first().url());
        }
    }
    return app;
}

void Root::index(Cutelyst::Context *c)
{
    static auto desktopListOrig = m_db->componentsByKind(Appstream::Component::KindDesktop);
    auto desktopList = desktopListOrig;
    if (!desktopList.isEmpty()) {
        auto desktop = desktopList.takeAt(qrand() % desktopList.size());
        c->setStash(QStringLiteral("mainApp"), componentToMap(desktop));
    }

    QVariantList showApps;
    while (showApps.size() < 12 && !desktopList.isEmpty()) {
        auto desktop = desktopList.takeAt(qrand() % desktopList.size());
        showApps.append(componentToMap(desktop));
    }
    c->setStash(QStringLiteral("apps"), showApps);
}

void Root::search(Context *c)
{
    auto result = m_db->findComponentsByString(c->request()->queryParam(QStringLiteral("q")));
    QVariantList apps;
    Q_FOREACH (const auto &desktop, result) {
        apps.append(componentToMap(desktop));
    }
    c->setStash(QStringLiteral("apps"), apps);
}

void Root::app(Context *c, const QString &id)
{
    auto desktop = m_db->componentById(id);
    c->setStash(QStringLiteral("app"), componentToMap(desktop));
}

void Root::defaultPage(Cutelyst::Context *c)
{
    c->response()->setBody(QStringLiteral("Page not found!"));
    c->response()->setStatus(404);
}


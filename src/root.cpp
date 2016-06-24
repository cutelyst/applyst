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
}

Root::~Root()
{
}

void Root::index(Cutelyst::Context *c)
{
    Appstream::Database db;
    if (!db.open()) {
        qWarning() << "Failed to open Appstream db" << db.errorString();
    }

    auto desktopList = db.componentsByKind(Appstream::Component::KindDesktop);
    if (!desktopList.isEmpty()) {
        auto desktop = desktopList.takeAt(qrand() % desktopList.size());

        QVariantMap app;
        app.insert(QStringLiteral("name"), desktop.name());
        app.insert(QStringLiteral("icon"), desktop.iconUrl(QSize(64, 64)));
        app.insert(QStringLiteral("summary"), desktop.summary());
        QList<Appstream::Screenshot> screenshots =  desktop.screenshots();
        qDebug() << desktop.name() << desktop.icon() << desktop.iconUrl(QSize(64, 64)) << desktop.summary();
        if (!screenshots.isEmpty()) {
            QList<Appstream::Image> images = screenshots.first().images();
            if (!images.isEmpty()) {
                qDebug() << images.first().kind() << images.first().url();
                app.insert(QStringLiteral("screenshot"), images.first().url());
            }
        }

        c->setStash(QStringLiteral("mainApp"), app);
    }

    QVariantList showApps;
    while (showApps.size() < 10 && !desktopList.isEmpty()) {
        auto desktop = desktopList.takeAt(qrand() % desktopList.size());
        QVariantMap app;
        app.insert(QStringLiteral("name"), desktop.name());
        app.insert(QStringLiteral("icon"), desktop.iconUrl(QSize(64, 64)));
        app.insert(QStringLiteral("summary"), desktop.summary());
        showApps.append(app);
    }
//    qDebug() << desktopList.size();
//    Q_FOREACH (const auto desktop, desktopList) {
//        qDebug() << desktop.name();
//    }
    c->setStash(QStringLiteral("apps"), showApps);
}

void Root::search(Context *c)
{

}

void Root::defaultPage(Cutelyst::Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}


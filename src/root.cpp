/***************************************************************************
 *   Copyright (C) 2017-2018 Daniel Nicoletti <dantti12@gmail.com>         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; see the file COPYING. If not, write to       *
 *   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,  *
 *   Boston, MA 02110-1301, USA.                                           *
 ***************************************************************************/
#include "root.h"

#include <Cutelyst/Plugins/Utils/Pagination>

#include <grantlee/safestring.h>

//using namespace Cutelyst;
using namespace AppStream;

#include <QDebug>

Root::Root(QObject *parent) : Cutelyst::Controller(parent)
{
    m_db = new AppStream::Pool;
    if (!m_db->load()) {
        qWarning() << "Failed to open AppStream db";// << m_db->errorString();
    }
}

Root::~Root()
{
}

QVariantMap componentToMap(Cutelyst::Context *c, const AppStream::Component &component)
{
    QVariantMap app;
    app.insert(QStringLiteral("id"), component.id());
    app.insert(QStringLiteral("name"), component.name());

    QUrl icon = component.icon(QSize(64, 64)).url();//.toLocalFile();
    QString iconPath = icon.toString();
    static QString appInfoPrefix = c->config(QStringLiteral("AppInfoPrefix")).toString();
    iconPath.remove(appInfoPrefix);
    //qWarning() << iconPath;
    app.insert(QStringLiteral("icon"), iconPath);

    app.insert(QStringLiteral("summary"), component.summary());

    const Grantlee::SafeString html(component.description(), true);
    app.insert(QStringLiteral("description"), html);

    QList<AppStream::Screenshot> screenshots =  component.screenshots();
    //qWarning() << component.name() << iconPath << component.summary();
    if (!screenshots.isEmpty()) {
        QList<AppStream::Image> images = screenshots.first().images();
        if (!images.isEmpty()) {
            //qDebug() << images.first().kind() << images.first().url();
            app.insert(QStringLiteral("screenshot"), images.first().url());
        }
    }
    return app;
}

void Root::index(Cutelyst::Context *c)
{
    static auto desktopListOrig = m_db->componentsByKind(AppStream::Component::KindDesktopApp);
    auto desktopList = desktopListOrig;
    if (!desktopList.isEmpty()) {
        auto desktop = desktopList.takeAt(qrand() % desktopList.size());
        c->setStash(QStringLiteral("mainApp"), componentToMap(c, desktop));
    }

    QVariantList showApps;
    while (showApps.size() < 12 && !desktopList.isEmpty()) {
        auto desktop = desktopList.takeAt(qrand() % desktopList.size());
        showApps.append(componentToMap(c, desktop));
    }
    c->setStash(QStringLiteral("apps"), showApps);
}

void Root::search(Context *c)
{
    /*const int appsPerPage = 100;
    int offset;*/

    QString searchText = c->req()->queryParam(QStringLiteral("q"));

    auto result = m_db->search(c->request()->queryParam(QStringLiteral("q")));
    QVariantList apps;
    Q_FOREACH (const auto &desktop, result) {
        apps.append(componentToMap(c, desktop));
    }
    c->setStash(QStringLiteral("apps"), apps);

    /*Pagination pagination(1000,
                          appsPerPage,
                          c->req()->queryParam(QStringLiteral("page"), QStringLiteral("1")).toInt());
    offset = pagination.offset();
    c->setStash(QStringLiteral("pagination"), pagination);
    c->setStash(QStringLiteral("posts_count"), 100);
    c->setStash(QStringLiteral("search"), searchText);*/
}

void Root::app(Context *c, const QString &id)
{
    auto desktops = m_db->componentsById(id);
    QVariantList apps;
    Q_FOREACH (const auto &desktop, desktops) {
        apps.append(componentToMap(c, desktop));
    }
    c->setStash(QStringLiteral("apps"), apps);

    /*
    auto desktop = m_db->componentsById(id);
    c->setStash(QStringLiteral("app"), componentToMap(c, desktop[0]));
    */
}

void Root::defaultPage(Cutelyst::Context *c)
{
    c->response()->setBody(QStringLiteral("Page not found!"));
    c->response()->setStatus(404);
}

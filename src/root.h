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
#ifndef ROOT_H
#define ROOT_H

#include <Cutelyst/Controller>

#include <AppStreamQt/pool.h>
#include <AppStreamQt/component.h>
#include <AppStreamQt/screenshot.h>
#include <AppStreamQt/image.h>
#include <AppStreamQt/icon.h>

using namespace Cutelyst;

namespace AppStream {
class Pool;
class Icon;
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
    bool End(Context *c) { Q_UNUSED(c); return true; }

    AppStream::Pool *m_db;
};

#endif // ROOT_H

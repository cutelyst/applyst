/***************************************************************************
 *   Copyright (C) 2016-2018 Daniel Nicoletti <dantti12@gmail.com>         *
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
    view->setCache(config(QStringLiteral("Production")).toBool());

    return true;
}


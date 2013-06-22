/**
 * Copyright (C) 2012-2013 Gauvain Pocentek <gauvain@pocentek.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "VpnIfAdaptor.h"
#include "VpnDaemon.h"

int main (int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    VpnDaemon* v = new VpnDaemon;
    new VpnIfAdaptor(v);

    QDBusConnection connection = QDBusConnection::systemBus();
    bool ret = connection.registerService("net.pocentek.vpn");
    if (! ret)
    {
        qDebug() << "No registration" << connection.lastError();
        return 1;
    }
    ret = connection.registerObject("/net/pocentek/vpn", v);
    if (! ret)
    {
        qDebug() << "No object registration" << connection.lastError();
        return 1;
    }

    return app.exec();
}


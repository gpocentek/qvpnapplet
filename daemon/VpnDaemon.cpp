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

#include <QDir>

#include "VpnDaemon.h"

VpnDaemon::VpnDaemon(QObject *parent)
    : QObject (parent)
{
    QDir confdir("/etc/net/vpn");
    QStringList filters;
    filters << "*.conf";
    confdir.setNameFilters(filters);

    foreach (QString conf, confdir.entryList())
    {
        conf = conf.remove(".conf");
        VpnProcess *p = new VpnProcess(conf, this);
        QObject::connect(p, SIGNAL(finished(QString &)),
                         this, SLOT(onProcessFinished(QString &)));
        configs[conf] = p;
    }
}

void VpnDaemon::onProcessFinished(QString &name)
{
    emit(StateChanged(name, false));
}

bool VpnDaemon::Start(const QString &name)
{
    if (!configs.contains(name))
        return false;

    VpnProcess *p = configs[name];
    if (!p->started())
    {
        p->start();
        emit(StateChanged(name, true));
    }

    return true;
}

QVariantMap VpnDaemon::Status()
{
    QVariantMap m;

    QMap<QString, VpnProcess *>::const_iterator i = configs.constBegin();
    while (i != configs.constEnd())
    {
        m[i.key()] = QVariant(i.value()->started());
        ++i;
    }

    return m;
}

bool VpnDaemon::Stop(const QString &name)
{
    if (!configs.contains(name))
        return false;

    VpnProcess *p = configs[name];
    if (p->started())
    {
        p->terminate();
        emit(StateChanged(name, false));
    }

    return true;
}


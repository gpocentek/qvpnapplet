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
#include <QFile>

#include "VpnProcess.h"

VpnProcess::VpnProcess(QString id, QObject *parent)
    : QProcess(parent)
{
    m_id = id;

    QString path = QString ("/etc/net/vpn/") + id + ".conf";
    QFile f(path);

    if (! f.exists())
        throw 0;

    m_command = QString("openvpn --syslog --config ") + path;
}

void VpnProcess::start()
{
    QObject::connect(this, SIGNAL(finished(int, QProcess::ExitStatus)),
                     this, SLOT(onFinished(int, QProcess::ExitStatus)));
    QProcess::start(m_command, QIODevice::ReadOnly);
}

bool VpnProcess::started()
{
    return QProcess::state() != QProcess::NotRunning;
}

void VpnProcess::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    emit(finished(m_id));
}


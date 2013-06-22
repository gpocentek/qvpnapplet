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

#ifndef VPNDAEMON_H
#define VPNDAEMON_H

#include <QVariantMap>

#include "VpnProcess.h"

class VpnDaemon : public QObject
{
Q_OBJECT
public:
    explicit VpnDaemon(QObject *parent = 0);

public slots:
    bool Start(const QString &name);
    QVariantMap Status();
    bool Stop(const QString &name);

private slots:
    void onProcessFinished(QString &name);

signals:
    void StateChanged(const QString &name, bool state);

private:
    QMap<QString,VpnProcess *> configs;
};

#endif


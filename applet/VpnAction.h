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

#ifndef VPNACTION_H
#define VPNACTION_H

#include <QAction>
#include <QString>
#include <QDBusConnection>
#include <QDBusInterface>

#include "VpnIf.h"

class VpnAction : public QAction
{
    Q_OBJECT

public:
    enum State {
        StateDown,
        StateUp,
        StateUnknown
    };

    VpnAction(QString name, QObject *parent = 0);
    void setState(State state);
    bool state();

signals:
    void triggered(QString &name, VpnAction::State curState);

public slots:
    void onTriggered();

private:
    QString m_name;
    State m_state;
};

#endif


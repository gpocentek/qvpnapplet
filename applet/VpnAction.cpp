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

#include <QtDebug>

#include <QtDBus>
#include <QDBusReply>

#include "VpnAction.h"
#include "config.h"

VpnAction::VpnAction(QString name, QObject *parent)
    : QAction (parent)
{
    m_name = name;
    m_state = StateUnknown;

    setText(m_name);
    setIconVisibleInMenu(true);

    QObject::connect(this, SIGNAL(triggered()),
                     this, SLOT(onTriggered()));
}

void VpnAction::setState(State state)
{
    m_state = state;
    if (state == StateUp)
        setIcon(QIcon(":images/on.png"));
    else
        setIcon(QIcon());
}

void VpnAction::onTriggered()
{
    emit(triggered(m_name, m_state));

    m_state = StateUnknown;
}


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
#include <QtDebug>
#include <QDBusReply>

#include "Window.h"

#include "config.h"

Window::Window()
{
    iface = new VpnIf("net.pocentek.vpn", "/net/pocentek/vpn",
                      QDBusConnection::systemBus(), this);

    QObject::connect(iface, SIGNAL(StateChanged(const QString &, bool)),
                     this, SLOT(onStateChanged(const QString &, bool)));
    createTrayIcon();
    trayIcon->show();
}

void Window::onStateChanged(const QString &name, bool state)
{
    bool active = false;
    VpnAction *a = buttons[name];
    a->setState(state ? VpnAction::StateUp : VpnAction::StateDown);
    if (state == VpnAction::StateUp)
        setIcon(true);


    /* Check if we have a connection to display the correct icon */
    QVariantMap rep = iface->Status();
    QMap<QString, QVariant>::const_iterator i = rep.constBegin();
    while (i != rep.constEnd())
    {
        VpnAction *action = new VpnAction(i.key(), this);
        if (i.value().toBool())
        {
            active = true;
            break;
        }
        ++i;
    }

    setIcon(active);
}

void Window::onActionTriggered(QString &name, VpnAction::State curState)
{
    if (curState != VpnAction::StateDown)
        iface->Stop(name);
    else /* TODO: handle unknown state properly */
        iface->Start(name);
}

void Window::setIcon(bool active)
{
    QIcon icon(active ? ":images/vpnapplet-active.png"
                      : ":images/vpnapplet.png");
    trayIcon->setIcon(icon);
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    populateMenu();

    QIcon icon(":images/vpnapplet.png");

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(icon);
}

void Window::populateMenu()
{
    QVariantMap rep = iface->Status();

    QMap<QString, QVariant>::const_iterator i = rep.constBegin();
    while (i != rep.constEnd())
    {
        VpnAction *action = new VpnAction(i.key(), this);
        action->setState(i.value().toBool() ? VpnAction::StateUp : VpnAction::StateDown);
        buttons[i.key()] = action;
        QObject::connect(action, SIGNAL(triggered(QString &, VpnAction::State)),
                         this, SLOT(onActionTriggered(QString &, VpnAction::State)));
        trayIconMenu->addAction(action);
        ++i;
    }
}


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

#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDBusConnection>
#include <QDBusInterface>

#include "VpnIf.h"
#include "VpnAction.h"

class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

private slots:
    void onStateChanged(const QString &name, bool state);
    void onActionTriggered(QString&, VpnAction::State);

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QMap<QString, VpnAction*> buttons;

    void createTrayIcon();
    void populateMenu();

    VpnIf *iface;
};

#endif


/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c VpnIf -p VpnIf.h:VpnIf.cpp ../net.pocentek.vpn.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef VPNIF_H_1351949667
#define VPNIF_H_1351949667

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface net.pocentek.vpn
 */
class VpnIf: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "net.pocentek.vpn"; }

public:
    VpnIf(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~VpnIf();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<bool> Start(const QString &name)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(name);
        return asyncCallWithArgumentList(QLatin1String("Start"), argumentList);
    }

    inline QDBusPendingReply<QVariantMap> Status()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Status"), argumentList);
    }

    inline QDBusPendingReply<bool> Stop(const QString &name)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(name);
        return asyncCallWithArgumentList(QLatin1String("Stop"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void StateChanged(const QString &name, bool state);
};

namespace net {
  namespace pocentek {
    typedef ::VpnIf vpn;
  }
}
#endif

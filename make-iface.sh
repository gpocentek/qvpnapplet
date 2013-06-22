#!/bin/sh

(cd daemon && qdbusxml2cpp -c VpnIfAdaptor -a VpnIfAdaptor.h:VpnIfAdaptor.cpp ../net.pocentek.vpn.xml)
(cd applet && qdbusxml2cpp -c VpnIf -p VpnIf.h:VpnIf.cpp ../net.pocentek.vpn.xml)


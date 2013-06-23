## QVpnApplet

QVpnApplet provides a daemon and a systray applet to handle OpenVPN connections
on Linux.

## Build

Only Qt4 is required.

To build:
`````bash
mkdir -p build
cd build
cmake ..
make
make install # as root
`````

You will also need to install `net.pocentek.vpn.xml` in `/etc/dbus-1/system.d/`
(tweak it to fit your needs).

## Debian package

You can also build a debian package:
`````bash
sudo apt-get install build-essential debhelper cmake libqt4-dev fakeroot devscripts
debuild -us -uc
sudo debi
`````

## Configuration

QVpnApplet uses OpenVPN configuration files, installed in `/etc/net/vpn/` and
named with a `.conf` extension. The basename of the file is used to display the
status for this connection in the applet contextual menu.

## Bugs

* The daemon fails to start as a DBus service. Make sure to start it with an
  init script or similar (I start it in `/etc/rc.local` on Debian/Ubuntu).


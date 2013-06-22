project(qvpnapplet)

cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE(Qt4 REQUIRED)

add_subdirectory(daemon)
add_subdirectory(applet)

set(VERSION 0.1)
set(SHAREDIR "${CMAKE_INSTALL_PREFIX}/share/qvpnapplet")

configure_file(config.h.cmake config.h)
configure_file(conf/net.pocentek.vpn.service.in
               conf/net.pocentek.vpn.service)
configure_file(conf/qvpnapplet.desktop.in
                conf/qvpnapplet.desktop)

install(FILES ${CMAKE_BINARY_DIR}/conf/net.pocentek.vpn.service
         DESTINATION /usr/share/dbus-1/system-services)
install(FILES ${CMAKE_BINARY_DIR}/conf/qvpnapplet.desktop
         DESTINATION /etc/xdg/autostart)

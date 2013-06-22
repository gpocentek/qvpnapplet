SET(qvpnapplet_SOURCES
    main.cpp
    VpnIf.cpp
    VpnAction.cpp
    Window.cpp)
SET(qvpnapplet_HEADERS
    VpnIf.h
    VpnAction.h
    Window.h)
SET(qvpnapplet_RESOURCES vpnapplet.qrc)

SET(QT_USE_QTGUI TRUE)
SET(QT_USE_QTDBUS TRUE)

QT4_WRAP_CPP(qvpnapplet_HEADERS_MOC ${qvpnapplet_HEADERS})
QT4_ADD_RESOURCES(qvpnapplet_RESOURCES_RCC ${qvpnapplet_RESOURCES})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
include_directories(${QT_INCLUDE_DIR} ${CMAKE_BINARY_DIR} .)

ADD_EXECUTABLE(qvpnapplet
                    ${qvpnapplet_SOURCES}
                    ${qvpnapplet_HEADERS_MOC}
                    ${qvpnapplet_RESOURCES_RCC})
TARGET_LINK_LIBRARIES(qvpnapplet ${QT_LIBRARIES} ${QT_QTDBUS_LIBRARY})

INSTALL(TARGETS qvpnapplet RUNTIME DESTINATION bin)

SET(qvpnd_SOURCES
    main.cpp
    VpnDaemon.cpp
    VpnIfAdaptor.cpp
    VpnProcess.cpp)
SET(qvpnd_HEADERS
    VpnDaemon.h
    VpnIfAdaptor.h
    VpnProcess.h)

SET(QT_USE_QTDBUS TRUE)
SET(QT_USE_QTGUI FALSE)

QT4_WRAP_CPP(qvpnd_HEADERS_MOC ${qvpnd_HEADERS})

INCLUDE(${QT_USE_FILE} common)
ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_EXECUTABLE(qvpnd ${qvpnd_SOURCES} ${qvpnd_HEADERS_MOC})
TARGET_LINK_LIBRARIES(qvpnd ${QT_LIBRARIES} ${QT_QTDBUS_LIBRARY})

INSTALL(TARGETS qvpnd RUNTIME DESTINATION sbin)

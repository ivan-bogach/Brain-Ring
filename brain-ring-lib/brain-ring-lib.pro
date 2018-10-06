QT -= gui
QT += sql
QT += network
TARGET = brain-ring-lib
TEMPLATE = lib

CONFIG += c++14

DEFINES += BRAINRINGLIB_LIBRARY

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)



INCLUDEPATH += source


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    source/controllers/master-controller.cpp \
    source/models/game.cpp \
    source/framework/command.cpp \
    source/controllers/command-controller.cpp \
    source/data/datadecorator.cpp \
    source/data/stringdecorator.cpp \
    source/data/intdecorator.cpp \
    source/data/datetimedecorator.cpp \
    source/data/enumeratordecorator.cpp \
    source/data/entity.cpp \
    source/controllers/database-controller.cpp \
    source/models/gamesearch.cpp \
    source/controllers/tcp-controller.cpp \
    source/models/tcpclient.cpp \
    source/models/tcpclientslist.cpp \
    source/framework/tcpclientcommand.cpp

HEADERS += source/brain-ring-lib_global.h \
    source/controllers/master-controller.h \
    source/models/game.h \
    source/controllers/navigation-controller.h \
    source/framework/command.h \
    source/controllers/command-controller.h \
    source/data/datadecorator.h \
    source/data/stringdecorator.h \
    source/data/intdecorator.h \
    source/data/datetimedecorator.h \
    source/data/enumeratordecorator.h \
    source/data/entity.h \
    source/data/entity-collection.h \
    source/controllers/i-database-controller.h \
    source/controllers/database-controller.h \
    source/models/gamesearch.h \
    source/controllers/tcp-controller.h \
    source/models/tcpclient.h \
    source/models/tcpclientslist.h \
    source/framework/tcpclientcommand.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

message(brain-ring-lib dir : $${PWD})

DESTDIR = $$PWD/../bin/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui
message(brain-ring-lib output dir: $${DESTDIR})

QMAKE_LFLAGS += -Wl,-rpath,"'\$$ORIGIN'"

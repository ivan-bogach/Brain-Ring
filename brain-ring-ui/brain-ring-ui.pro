QT += qml quick

TEMPLATE = app

CONFIG += c++14

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

INCLUDEPATH += source \
    ../brain-ring-lib/source

SOURCES += source/main.cpp

RESOURCES += views.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

LIBS += -L$$PWD/../bin/$$DESTINATION_PATH -lbrain-ring-lib

message(DESTINATION_PATH: $${DESTINATION_PATH})

DESTDIR = $$PWD/../bin/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

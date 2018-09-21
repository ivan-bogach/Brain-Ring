TEMPLATE = subdirs

SUBDIRS += \
    brain-ring-ui \
    brain-ring-lib \
    brain-ring-tests

message(brain-ring dir : $${PWD})

QMAKE_LFLAGS += -Wl,-rpath,"'\$$ORIGIN'"

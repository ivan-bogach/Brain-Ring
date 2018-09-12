TEMPLATE = subdirs

SUBDIRS += \
    brain-ring-ui \
    brain-ring-lib \
    brain-ring-tests

message(brain-ring dir : $${PWD})

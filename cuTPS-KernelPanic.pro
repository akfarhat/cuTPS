TEMPLATE = subdirs

SUBDIRS += \
    cuTPS-client \
    cuTPS-server \
    cuTPS-common

cuTPS-client.depends = cuTPS-common
cuTPS-server.depends = cuTPS-common

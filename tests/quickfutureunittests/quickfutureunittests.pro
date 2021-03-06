#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T18:56:34
#
#-------------------------------------------------

QT       += testlib qml concurrent
CONFIG += c++11

TARGET = quickfutureunittests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
ROOT_DIR = $$PWD/../..

SOURCES +=     main.cpp     \
    quickfutureunittests.cpp \
    actor.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(vendor/vendor.pri)
include($$ROOT_DIR/quickfuture.pri)

DEFINES += QUICK_TEST_SOURCE_DIR=\\\"$$PWD\\\"

DISTFILES +=     qpm.json     \
    ../../README.md \
    qmltests/PromiseIsNotInstalled.qml \
    qmltests/tst_Callback.qml \
    qmltests/tst_Promise.qml \
    qmltests/tst_Sync.qml \
    qmltests/CustomTestCase.qml \
    ../../qpm.json

HEADERS +=     \
    quickfutureunittests.h \
    actor.h

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

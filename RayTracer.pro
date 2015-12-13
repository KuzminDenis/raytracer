#-------------------------------------------------
#
# Project created by QtCreator 2015-11-21T19:10:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene_object.cpp \
    scene.cpp \
    light_source.cpp \
    world.cpp \
    renderer.cpp \
    tracer.cpp \
    ray.cpp \
    camera.cpp \
    triangle.cpp \
    sphere.cpp \
    plane.cpp \
    types.cpp \
    model.cpp

HEADERS  += mainwindow.h \
    scene_object.h \
    scene.h \
    light_source.h \
    world.h \
    renderer.h \
    tracer.h \
    ray.h \
    camera.h \
    triangle.h \
    sphere.h \
    plane.h \
    types.h \
    model.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/FreeImage/release/ -lfreeimage
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/FreeImage/debug/ -lfreeimage
else:unix: LIBS += -L$$PWD/lib/FreeImage/ -lfreeimage

INCLUDEPATH += $$PWD/lib/FreeImage/Source
DEPENDPATH += $$PWD/lib/FreeImage/Source

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/FreeImage/release/libfreeimage.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/FreeImage/debug/libfreeimage.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/FreeImage/release/freeimage.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/FreeImage/debug/freeimage.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/FreeImage/libfreeimage.a

win32:CONFIG(release, debug|release): LIBS += -L$$/usr/local/lib/release/ -l3ds
else:win32:CONFIG(debug, debug|release): LIBS += -L$$/usr/local/lib/debug/ -l3ds
else:unix: LIBS += -L$$/usr/local/lib/ -l3ds

INCLUDEPATH += $$PWD/lib/lib3ds/src
DEPENDPATH += $$PWD/lib/lib3ds/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$/usr/local/lib/release/lib3ds.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$/usr/local/lib/debug/lib3ds.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$/usr/local/lib/release/3ds.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$/usr/local/lib/debug/3ds.lib
else:unix: PRE_TARGETDEPS += $$/usr/local/lib/lib3ds.a

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS +=  -fopenmp
LIBS += -lgomp -lpthread

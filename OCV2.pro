QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OCV3
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui

SOURCES += \
    main.cpp \
    usermenu.cpp \
    slideshow.cpp \
    camerawrapper.cpp \
    smalltextstrategy1.cpp \
    largetextstrategy2.cpp


HEADERS += \
    usermenu.h \
    slideshow.h \
    camerawrapper.h \
    smalltextstrategy1.h \
    textstrategy1.h \
    largetextstrategy2.h



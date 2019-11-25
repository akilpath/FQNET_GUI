

QT       += core gui multimedia sql widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
DEFINES += LINUX linux
TARGET = PROGRAM
TEMPLATE = app
LIBS += -DLINUX -Dlinux -L$$PWD/../lib/ -lftd3xx -ltdcbase
PKGCONFIG += 
CONFIG += link_pkgconfig 


INCPATH +=




SOURCES += main.cpp\
           dbcontrol.cpp \
           mainwindow.cpp \
           qcustomplot.cpp \
           qutag_adq.cpp \
           qutag_anl.cpp
          

HEADERS  += mainwindow.h \
            dbcontrol.h \
            qcustomplot.h \
            qutag_adq.h \
            qutag_anl.h \
            tdcbase.h \
            tdcdecl.h \
            tdcstartstop.h
	   

FORMS    += mainwindow.ui


RESOURCES += \
    resources.qrc



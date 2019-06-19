

QT       += core gui multimedia


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
           mainwindow.cpp \
           qcustomplot.cpp \
           qutag_adq.cpp
          

HEADERS  += mainwindow.h \
            qcustomplot.h \
            qutag_adq.h \
            tdcbase.h \
            tdcdecl.h \
            tdcstartstop.h
	   

FORMS    += mainwindow.ui


RESOURCES += \
    resources.qrc



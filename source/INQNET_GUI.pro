

QT       += core gui multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

DEFINES += LINUX linux
TARGET = PROGRAM
TEMPLATE = app
LIBS += -DLINUX -Dlinux 
PKGCONFIG += 
CONFIG += link_pkgconfig 


INCPATH +=




SOURCES += main.cpp\
           mainwindow.cpp \
           qcustomplot.cpp
          

HEADERS  += mainwindow.h \
            qcustomplot.h
	   

FORMS    += mainwindow.ui

DISTFILES += \
    logo15.png


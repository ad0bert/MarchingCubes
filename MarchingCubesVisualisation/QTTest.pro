#-------------------------------------------------
#
# Project created by QtCreator 2015-08-04T14:48:35
#
#-------------------------------------------------

QT       += core gui widgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTTest
TEMPLATE = app
RC_FILE = myapp.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    fileHandler.cpp \
    tetrahedron.cpp \
    marchingcubes.cpp

HEADERS  += mainwindow.h \
    dbh.h \
    fileHandler.h \
    tabels.h \
    tetrahedron.h \
    marchingcubes.h

LIBS += -lopengl32 \
    -lglu32

FORMS    += mainwindow.ui

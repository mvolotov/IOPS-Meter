#-------------------------------------------------
#
# Project created by QtCreator 2019-06-23T13:01:34
#
#-------------------------------------------------

QT       += core gui printsupport concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport concurrent

TARGET = IOPSMaster
TEMPLATE = app

QMAKE_LFLAGS += -static -static-libgcc

#QMAKE_LIBS+=-lgomp -lpthread
#QMAKE_CXXFLAGS+=-fopenmp

RC_ICONS = app.ico

isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

win32 {
    DEPLOY_COMMAND = windeployqt
}
macx {
    DEPLOY_COMMAND = macdeployqt
}

CONFIG( debug, debug|release ) {
    # debug
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
} else {
    # release
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))
}

#  # Uncomment the following line to help debug the deploy command when running qmake
#  warning($${DEPLOY_COMMAND} $${DEPLOY_TARGET})

# Use += instead of = if you use multiple QMAKE_POST_LINKs
QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    about.cpp \
        main.cpp \
    qcustomplot.cpp \
    mainwindow.cpp \
    modeling/density.cpp \
    modeling/distribution.cpp \
    modeling/simulation.cpp

HEADERS += \
    about.h \
        mainwindow.h \
    qcustomplot.h \
    modeling/density.h \
    modeling/distribution.h \
    modeling/simulation.h

FORMS += \
        about.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res.qrc

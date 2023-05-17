QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./controller/controller.cc \
    ./model/calculation.cc \
    ./model/polish_notation.cc \
    ./model/support_methods.cc \
    ./model/loan_calculator.cc \
    ./view/form.cc \
    ./view/loancalc.cc \
    ./view/main.cc \
    ./view/mainwindow.cc \
    ./view/plot.cc \
    qcustomplot.cc

HEADERS += \
    ./controller/controller.h \
    ./model/model.h \
    ./model/s21_stack.h \
    ./view/form.h \
    ./view/loancalc.h \
    ./view/mainwindow.h \
    ./view/plot.h \
    qcustomplot.h

FORMS += \
    ./view/form.ui \
    ./view/loancalc.ui \
    ./view/mainwindow.ui \
    ./view/plot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

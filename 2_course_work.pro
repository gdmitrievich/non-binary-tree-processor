QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base_transport_window.cpp \
    src/utility/utility.cpp \
    src/utility/utility.ipp \
    transport_type_dialog.cpp \
    filling_in_transport_data_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    src/data_types/data_structures/tree.cpp \
    src/data_types/project_types/air_transport.cpp \
    src/data_types/project_types/airplane.cpp \
    src/data_types/project_types/bus.cpp \
    src/data_types/project_types/car.cpp \
    src/data_types/project_types/ground_transport.cpp \
    src/data_types/project_types/helicopter.cpp \
    src/data_types/project_types/metro.cpp \
    src/data_types/project_types/transport.cpp \
    src/data_types/project_types/underground_transport.cpp

HEADERS += \
    base_transport_window.h \
    filling_in_transport_data_dialog.h \
    mainwindow.h \
    src/data_types/data_structures/child.h \
    src/data_types/data_structures/child.ipp \
    src/data_types/data_structures/list/doubly_linked_list.h \
    src/data_types/data_structures/list/doubly_linked_list.ipp \
    src/data_types/data_structures/list/node.h \
    src/data_types/data_structures/list/node.ipp \
    src/data_types/data_structures/parent.h \
    src/data_types/data_structures/parent.ipp \
    src/data_types/data_structures/tree.h \
    src/data_types/data_structures/tree.ipp \
    src/data_types/project_types/air_transport.h \
    src/data_types/project_types/air_transport.ipp \
    src/data_types/project_types/airplane.h \
    src/data_types/project_types/airplane.ipp \
    src/data_types/project_types/bus.h \
    src/data_types/project_types/bus.ipp \
    src/data_types/project_types/car.h \
    src/data_types/project_types/car.ipp \
    src/data_types/project_types/ground_transport.h \
    src/data_types/project_types/ground_transport.ipp \
    src/data_types/project_types/helicopter.h \
    src/data_types/project_types/helicopter.ipp \
    src/data_types/project_types/metro.h \
    src/data_types/project_types/metro.ipp \
    src/data_types/project_types/transport.h \
    src/data_types/project_types/transport.ipp \
    src/data_types/project_types/transport_type.h \
    src/data_types/project_types/underground_transport.h \
    src/data_types/project_types/underground_transport.ipp \
    src/utility/utility.h \
    transport_type_dialog.h

FORMS += \
    base_transport_window.ui \
    filling_in_transport_data_dialog.ui \
    mainwindow.ui \
    transport_type_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT -= core gui
TARGET = steel
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

LIBS += -lhidapi-libusb
#LIBS += -lhidapi-hidraw
INCLUDEPATH += /usr/include

HEADERS += \
    actions/IActions.h \
    actions/MsiKeyboardActions.h \
    actions/Rival100Actions.h \
    actions/SteelActions.h \
    config/IConfig.h \
    config/IDeviceConfig.h \
    config/MsiKeyboardConfig.h \
    config/MsiKeyboardProfile.h \
    config/Rival100Config.h \
    config/Rival100Profile.h \
    config/SteelConfig.h \
    context/IContext.h \
    context/MsiKeyboardContext.h \
    context/Rival100Context.h \
    context/SteelContext.h \
    device/HidDeviceInfo.h \
    device/IHidDevice.h \
    device/MsiKeyboard.h \
    device/Rival100.h \
    parser/IDeviceParser.h \
    parser/MsiKeyboardParser.h \
    parser/Rival100Parser.h \
    parser/SteelParser.h \
    utils/Lookup.h \
    utils/SysLog.h \
    utils/Utils.h

SOURCES += \
    actions/IActions.cpp \
    actions/MsiKeyboardActions.cpp \
    actions/Rival100Actions.cpp \
    actions/SteelActions.cpp \
    config/IDeviceConfig.cpp \
    config/MsiKeyboardConfig.cpp \
    config/MsiKeyboardProfile.cpp \
    config/Rival100Config.cpp \
    config/Rival100Profile.cpp \
    config/SteelConfig.cpp \
    context/IContext.cpp \
    context/MsiKeyboardContext.cpp \
    context/Rival100Context.cpp \
    context/SteelContext.cpp \
    device/HidDeviceInfo.cpp \
    device/IHidDevice.cpp \
    device/MsiKeyboard.cpp \
    device/Rival100.cpp \
    parser/IDeviceParser.cpp \
    parser/MsiKeyboardParser.cpp \
    parser/Rival100Parser.cpp \
    parser/SteelParser.cpp \
    utils/SysLog.cpp \
    utils/Utils.cpp \
    main.cpp

QT       += core gui quick network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChatMessage.cpp \
    FileSendAndRecv.cpp \
    InputMessageItem.cpp \
    MsgItem.cpp \
    SearchUser.cpp \
    Socket.cpp \
    User.cpp \
    UserChatItem.cpp \
    UserChatListItem.cpp \
    UserInfoUI.cpp \
    UserMenuItem.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    register.cpp

HEADERS += \
    ChatMessage.h \
    FileSendAndRecv.h \
    InputMessageItem.h \
    MsgItem.h \
    SearchUser.h \
    Socket.h \
    User.h \
    UserChatItem.h \
    UserChatListItem.h \
    UserInfoUI.h \
    UserMenuItem.h \
    login.h \
    mainwindow.h \
    register.h

FORMS += \
    InputMessageItem.ui \
    MsgItem.ui \
    SearchUser.ui \
    UserChatItem.ui \
    UserChatListItem.ui \
    UserInfoUI.ui \
    UserMenuItem.ui \
    login.ui \
    mainwindow.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

QT += widgets
requires(qtConfig(filedialog))

HEADERS       = \
    texteditor.h \
    mainwindow.h
SOURCES       = main.cpp \
    texteditor.cpp \
    mainwindow.cpp
#! [0]
RESOURCES     = application.qrc
#! [0]

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
INSTALLS += target

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libraries/release/ -lyaml-cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libraries/debug/ -lyaml-cpp
else:unix: LIBS += -L$$PWD/libraries/ -lyaml-cpp

INCLUDEPATH += $$PWD/libraries
DEPENDPATH += $$PWD/libraries

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libraries/release/libyaml-cpp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libraries/debug/libyaml-cpp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libraries/release/yaml-cpp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libraries/debug/yaml-cpp.lib
else:unix: PRE_TARGETDEPS += $$PWD/libraries/libyaml-cpp.a

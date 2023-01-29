include(qtconfig)

INCLUDEPATH += include
QT += widgets
unix|macx {
  CONFIG += no_plugin_name_prefix
}
TARGET = mayaUiPluginTemplate
HEADERS += include/*.h
SOURCES += src/*.cpp

DESTDIR = $$PWD/build
OBJECTS_DIR = $${DESTDIR}/.o
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui

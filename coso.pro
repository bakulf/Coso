TEMPLATE = app
TARGET   = coso

QT      -= gui
QT      += xml

MOC_DIR     = .moc
OBJECTS_DIR = .obj

CONFIG    += link_pkgconfig
PKGCONFIG += gconf-2.0

QMAKE_CXXFLAGS *= -Werror

INCLUDEPATH += cmds        \
               cmds/switch \
               cmds/help   \
               cmds/new    \
               cmds/delete \
               cmds/info

INCLUDEPATH += tasks            \
               tasks/editFile   \
               tasks/removeFile \
               tasks/createFile \
               tasks/gconf      \
               tasks/kill       \
               tasks/exec

DEPENDPATH  += $${INCLUDEPATH}

CMDS_HEADERS = ccmdhelp.h   \
               ccmdswitch.h \
               ccmdnew.h    \
               ccmddelete.h \
               ccmdinfo.h

CMDS_SOURCES = ccmdhelp.cpp   \
               ccmdswitch.cpp \
               ccmdnew.cpp    \
               ccmddelete.cpp \
               ccmdinfo.cpp

TASKS_HEADERS = ctaskeditfile.h   \
                ctaskremovefile.h \
                ctaskcreatefile.h \
                ctaskgconf.h      \
                ctaskkill.h       \
                ctaskexec.h

TASKS_SOURCES = ctaskeditfile.cpp   \
                ctaskremovefile.cpp \
                ctaskcreatefile.cpp \
                ctaskgconf.cpp      \
                ctaskkill.cpp       \
                ctaskexec.cpp

HEADERS = constants.h       \
          capplication.h    \
          ccontext.h        \
          ctask.h           \
          chelper.h         \
          ccmd.h            \
          $${TASKS_HEADERS} \
          $${CMDS_HEADERS}

SOURCES = main.cpp          \
          capplication.cpp  \
          ccontext.cpp      \
          ctask.cpp         \
          chelper.cpp       \
          $${TASKS_SOURCES} \
          $${CMDS_SOURCES}

unix {
    isEmpty(PREFIX) {
        PREFIX = /usr
    }

    BINDIR = $$PREFIX/bin
    target.path =$$BINDIR

    INSTALLS += target
}

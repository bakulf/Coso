TEMPLATE = app
TARGET   = coso

QT      -= gui
QT      += xml

MOC_DIR     = .moc
OBJECTS_DIR = .obj

QMAKE_CXXFLAGS *= -Werror

INCLUDEPATH += cmds        \
               cmds/switch \
               cmds/help   \
               cmds/info

INCLUDEPATH += tasks      \
               tasks/file

DEPENDPATH  += $${INCLUDEPATH}

CMDS_HEADERS = ccmdhelp.h   \
               ccmdswitch.h \
               ccmdinfo.h

CMDS_SOURCES = ccmdhelp.cpp   \
               ccmdswitch.cpp \
               ccmdinfo.cpp

TASKS_HEADERS = ctaskfile.h

TASKS_SOURCES = ctaskfile.cpp

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
          chelper.cpp       \
          $${TASKS_SOURCES} \
          $${CMDS_SOURCES}

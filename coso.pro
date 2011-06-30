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
               cmds/new    \
               cmds/info

INCLUDEPATH += tasks            \
               tasks/editFile   \
               tasks/removeFile \
               tasks/createFile

DEPENDPATH  += $${INCLUDEPATH}

CMDS_HEADERS = ccmdhelp.h   \
               ccmdswitch.h \
               ccmdnew.h    \
               ccmdinfo.h

CMDS_SOURCES = ccmdhelp.cpp   \
               ccmdswitch.cpp \
               ccmdnew.cpp    \
               ccmdinfo.cpp

TASKS_HEADERS = ctaskeditfile.h   \
                ctaskremovefile.h \
                ctaskcreatefile.h

TASKS_SOURCES = ctaskeditfile.cpp   \
                ctaskremovefile.cpp \
                ctaskcreatefile.cpp

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

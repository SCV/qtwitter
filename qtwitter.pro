TEMPLATE = app
TARGET = qtwitter

SOURCES   += main.cpp mainwindow.cpp statusedit.cpp xmlparser.cpp httpconnection.cpp xmldownload.cpp imagedownload.cpp
HEADERS   += mainwindow.h statusfilter.h statusedit.h xmlparser.h entry.h httpconnection.h xmldownload.h imagedownload.h
FORMS     += mainwindow.ui authdialog.ui
RESOURCES += resources.qrc
QT        += network xml

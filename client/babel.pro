CONFIG += qt
QT += widgets network
INCLUDEPATH += include/

HEADERS += 	include/QTcpAsyncSocket.hh 	\
		include/BabelCoreClient.hh 	\
		include/IAsyncSocketListener.hh \
                include/ICoreListener.hh        \
                include/IWidgetListener.hh

SOURCES += 	src/main.cpp 			\
		src/QTcpAsyncSocket.cpp 	\
		src/BabelCoreClient.cpp

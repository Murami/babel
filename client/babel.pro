CONFIG += qt
QT += core gui widgets network
INCLUDEPATH += include/

HEADERS += 	include/QTcpAsyncSocket.hh 	\
		include/BabelCoreClient.hh 	\
		include/IAsyncSocketListener.hh \
                include/ICoreListener.hh        \
                include/IWidgetListener.hh      \
                include/IFunctor.hh             \
                include/Functor.hh              \
                include/Protocol.hh

SOURCES += 	src/main.cpp 			\
		src/QTcpAsyncSocket.cpp 	\
		src/BabelCoreClient.cpp         \
                src/Functor.cpp

OBJECTS_DIR	=	src/

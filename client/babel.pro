CONFIG += qt
QT += core gui widgets network
INCLUDEPATH += include/

HEADERS += 	include/QTcpAsyncSocket.hh 	\
		include/BabelCoreClient.hh 	\
		include/IAsyncSocketListener.hh \
                include/IWidgetListener.hh      \
                include/IFunctor.hh             \
                include/Functor.hh              \
                include/Protocol.hh             \
                include/ICallErrorListener.hh   \
                include/IConnectListener.hh     \
                include/IDisconnectListener.hh   \
                include/IMsgErrorListener.hh    \
                include/IRegisterListener.hh    \
                include/ICallListener.hh        \
                include/IErrorListener.hh       \
                include/ILoginListener.hh       \
                include/IMsgListener.hh         \
                include/IUserInfoListener.hh

SOURCES += 	src/main.cpp 			\
		src/QTcpAsyncSocket.cpp 	\
		src/BabelCoreClient.cpp         \
                src/Functor.cpp

OBJECTS_DIR	=	src/

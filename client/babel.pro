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
                include/IDisconnectListener.hh  \
                include/IMsgErrorListener.hh    \
                include/IRegisterListener.hh    \
                include/ICallListener.hh        \
                include/IErrorListener.hh       \
                include/ILoginListener.hh       \
                include/IMsgListener.hh         \
                include/IUserInfoListener.hh	\
		include/AddNewContactDialog.hh	\
		include/ConversationWindow.hh	\
		include/LoginDialog.hh		\
		include/MainWindow.hh		\
		include/User.hh			\
		include/WidgetButton.hh		\
		include/WidgetListView.hh	\
		include/WidgetTextView.hh	\
		include/ResourceManager.hpp	\
		include/LoginEntryDialog.hh	\
		include/RegisterEntryDialog.hh	\

SOURCES += 	src/main.cpp 			\
		src/QTcpAsyncSocket.cpp 	\
		src/BabelCoreClient.cpp         \
                src/Functor.cpp			\
		src/AddNewContactDialog.cpp	\
		src/ConversationWindow.cpp	\
		src/LoginDialog.cpp		\
		src/MainWindow.cpp		\
		src/User.cpp			\
		src/WidgetButton.cpp		\
		src/WidgetListView.cpp		\
		src/WidgetTextView.cpp		\
		src/LoginEntryDialog.cpp	\
		src/RegisterEntryDialog.cpp	\

OBJECTS_DIR	=	src/

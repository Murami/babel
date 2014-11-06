CONFIG += qt
QT += core gui widgets network
INCLUDEPATH += include/

QMAKE_CXXFLAGS += -g3

HEADERS += 	include/TcpAsyncSocket.hh               \
                include/UdpAsyncSocket.hh               \
		include/BabelCoreClient.hh              \
		include/ITcpAsyncSocketListener.hh      \
                include/IUdpAsyncSocketListener.hh      \
                include/IWidgetListener.hh              \
                include/IFunctor.hh                     \
                include/Functor.hh                      \
                include/Protocol.hh                     \
                include/IQTcpSocketListener.hh          \
                include/IQUdpSocketListener.hh          \
                include/ICallErrorListener.hh           \
                include/IConnectListener.hh             \
                include/IDisconnectListener.hh          \
                include/IMsgErrorListener.hh            \
                include/IRegisterListener.hh            \
                include/ICallListener.hh                \
                include/IErrorListener.hh               \
                include/ILoginListener.hh               \
                include/IMsgListener.hh                 \
                include/IUserInfoListener.hh            \
		include/AddNewContactDialog.hh          \
		include/ConversationWindow.hh           \
		include/LoginDialog.hh                  \
		include/MainWindow.hh                   \
		include/User.hh                         \
		include/WidgetButton.hh                 \
		include/WidgetListView.hh               \
		include/WidgetTextView.hh               \
		include/ResourceManager.hpp             \
		include/LoginEntryDialog.hh             \
		include/RegisterEntryDialog.hh          \
                include/ITimerListener.hh               \
                include/Timer.hh                        \
                include/IMutex.hh                       \
                include/Mutex.hh

SOURCES += 	src/main.cpp                            \
                src/UdpAsyncSocket.cpp                  \
		src/TcpAsyncSocket.cpp                  \
		src/BabelCoreClient.cpp                 \
                src/Functor.cpp                         \
		src/AddNewContactDialog.cpp             \
		src/ConversationWindow.cpp              \
		src/LoginDialog.cpp                     \
		src/MainWindow.cpp                      \
		src/User.cpp                            \
		src/WidgetButton.cpp                    \
		src/WidgetListView.cpp                  \
		src/WidgetTextView.cpp                  \
		src/LoginEntryDialog.cpp                \
		src/RegisterEntryDialog.cpp             \
                src/Timer.cpp                           \
                src/Mutex.cpp

OBJECTS_DIR	=	src/

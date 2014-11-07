CONFIG += qt
QT += core gui widgets network
LIBS += libportaudio/libs/libportaudio.a -lopus -lasound -ljack
INCLUDEPATH +=  include libportaudio/include

QMAKE_CXXFLAGS += -g3

HEADERS += 	include/TcpAsyncSocket.hh               \
		include/UdpAsyncSocket.hh               \
		include/BabelCoreClient.hh              \
		include/ITcpAsyncSocketListener.hh      \
		include/IUdpAsyncSocketListener.hh      \
		include/IWidgetListener.hh              \
		include/IFunctor.hh		     	\
		include/Functor.hh		      	\
		include/Protocol.hh		     	\
		include/IQTcpSocketListener.hh          \
		include/IQUdpSocketListener.hh          \
		include/ICallErrorListener.hh           \
		include/IConnectListener.hh             \
		include/IDisconnectListener.hh          \
		include/IMsgErrorListener.hh            \
		include/IRegisterListener.hh            \
		include/ICallListener.hh		\
		include/IErrorListener.hh               \
		include/ILoginListener.hh               \
		include/IMsgListener.hh		 	\
		include/IUserInfoListener.hh            \
		include/ConversationWindow.hh           \
		include/AudioConversationWindow.hh	\
		include/LoginDialog.hh		  	\
		include/MainWindow.hh		   	\
		include/User.hh		         	\
		include/WidgetButton.hh		 	\
		include/WidgetListView.hh               \
		include/WidgetTextView.hh               \
		include/ResourceManager.hpp             \
		include/LoginEntryDialog.hh             \
		include/RegisterEntryDialog.hh          \
		include/ITimerListener.hh               \
		include/Timer.hh		        \
		include/IMutex.hh		       	\
		include/Mutex.hh			\
                include/APAAudioStream.hh               \
                include/AudioBuffer.hh                  \
                include/AudioPlayer.hh                  \
                include/AudioRecorder.hh                \
                include/AudioStreamListener.hh          \
                include/CircularBuffer.hh               \
                include/IAudioCoder.hh                  \
                include/IAudioDevice.hh                 \
                include/IAudioInputStream.hh            \
                include/IAudioInputStreamListener.hh    \
                include/IAudioOutputStream.hh           \
                include/IAudioOutputStreamListener.hh   \
                include/IAudioService.hh                \
                include/IAudioStream.hh                 \
                include/OpusAudioCoder.hh               \
                include/PAAudioDevice.hh                \
                include/PAAudioInputStream.hh           \
                include/PAAudioOutputStream.hh          \
                include/PAAudioService.hh               \
                include/SampleFormat.hh                 \
                libportaudio/include/pa_asio.h          \
                libportaudio/include/pa_win_ds.h        \
                libportaudio/include/pa_win_wmme.h      \
                libportaudio/include/pa_jack.h          \
                libportaudio/include/pa_win_wasapi.h    \
                libportaudio/include/portaudio.h        \
                libportaudio/include/pa_linux_alsa.h    \
                libportaudio/include/pa_win_waveformat.h \
                libportaudio/include/pa_mac_core.h      \
                libportaudio/include/pa_win_wdmks.h

SOURCES += 	src/main.cpp		            	\
		src/UdpAsyncSocket.cpp		  	\
		src/TcpAsyncSocket.cpp		  	\
		src/BabelCoreClient.cpp		 	\
		src/Functor.cpp		         	\
		src/ConversationWindow.cpp              \
		src/AudioConversationWindow.cpp		\
		src/LoginDialog.cpp		     	\
		src/MainWindow.cpp		      	\
		src/User.cpp		            	\
		src/WidgetButton.cpp		    	\
		src/WidgetListView.cpp		  	\
		src/WidgetTextView.cpp		  	\
		src/LoginEntryDialog.cpp		\
		src/RegisterEntryDialog.cpp             \
		src/Timer.cpp		           	\
		src/Mutex.cpp				\
                src/APAAudioStream.cpp                  \
                src/AudioBuffer.cpp                     \
                src/AudioPlayer.cpp                     \
                src/AudioRecorder.cpp                   \
                src/CircularBuffer.cpp                  \
                src/OpusAudioCoder.cpp                  \
                src/PAAudioDevice.cpp                   \
                src/PAAudioInputStream.cpp              \
                src/PAAudioOutputStream.cpp             \
                src/PAAudioService.cpp                  \
                src/SampleFormat.cpp

OBJECTS_DIR	=	src/

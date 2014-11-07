#ifndef		__CONVERSATIONWINDOW_HH__
# define	__CONVERSATIONWINDOW_HH__

# include	<string>
# include	<QLabel>
# include	<QMainWindow>
# include	<QVBoxLayout>
# include	<QLineEdit>
# include	<QBrush>
# include	<QImage>
# include	<QHBoxLayout>

# include	"IMsgErrorListener.hh"
# include	"IMsgListener.hh"

class		BabelCoreClient;
class		WidgetButton;
class		WidgetTextView;

class		ConversationWindow : public QWidget, public IMsgListener, public IMsgErrorListener
{
  Q_OBJECT

public:
  static int	WIDTH;
  static int	HEIGHT;

private:
  WidgetButton		*_hangoutButton;
  WidgetButton		*_sendMessageButton;
  WidgetTextView	*_messageTextView;
  QLineEdit		*_messageEdit;
  WidgetButton		*_quitButton;
  BabelCoreClient&	_core;
  QString		_username;
  QString		_connectedMate;

public:
  virtual void		onMsg(NET::MsgInfo);
  virtual void		onMsgError(bool);

public:
  void		setUsername(const QString& username);

signals:
  void		closed(ConversationWindow*);

private slots:
  void		sendMessage();
  void		closeWindow();

public:
  ConversationWindow(BabelCoreClient&,
		     const std::string& user,
		     const std::string& mate, QWidget *parent = 0);
  ~ConversationWindow();
};

#endif

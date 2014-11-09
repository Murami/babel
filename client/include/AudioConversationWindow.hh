#ifndef		__AUDIOCONVERSATIONWINDOW_HH__
# define	__AUDIOCONVERSATIONWINDOW_HH__

# include	<string>
# include	<QMainWindow>

# include	"IKoCallListener.hh"
# include	"ICallErrorListener.hh"

class		WidgetButton;
class		BabelCoreClient;

class		AudioConversationWindow : public QWidget, public ICallErrorListener, public IKoCallListener
{
  Q_OBJECT

private:
  QString		_username;
  QString		_mate;
  BabelCoreClient&	_core;
  WidgetButton		*_hangoutButton;

public:
  AudioConversationWindow(BabelCoreClient&,
			  const std::string& mate,
			  const std::string& user,
			  QWidget *parent = 0);
  ~AudioConversationWindow();

public:
  virtual void	onCallError(bool);
  virtual void	onKoCall();

public:
  void		setUsername(const QString& username);

signals:
  void		closed();

private slots:
  void		hangout();

public:
  static int	WIDTH;
  static int	HEIGHT;
};

#endif

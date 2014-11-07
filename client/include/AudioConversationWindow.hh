#ifndef		__AUDIOCONVERSATIONWINDOW_HH__
# define	__AUDIOCONVERSATIONWINDOW_HH__

# include	<string>
# include	<QMainWindow>

class		BabelCoreClient;

class		AudioConversationWindow : public QMainWindow
{
  Q_OBJECT

private:
  QString		_username;
  BabelCoreClient&	_core;

public:
  AudioConversationWindow(BabelCoreClient&, const std::string& username, QWidget *parent = 0);
  ~AudioConversationWindow();

public:
  void		setUsername(const QString& username);

public:
  static int	WIDTH;
  static int	HEIGHT;
};

#endif

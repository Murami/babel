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

class		WidgetButton;
class		WidgetTextView;

class		ConversationWindow : public QWidget
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

private slots:
  void		sendMessage();

public:
  ConversationWindow(const std::string& username, QWidget *parent = 0);
  ~ConversationWindow();
};

#endif

#ifndef		__CONVERSATIONWINDOW_HH__
# define	__CONVERSATIONWINDOW_HH__

# include	<QLabel>
# include	<QMainWindow>
# include	<QVBoxLayout>
# include	<QLineEdit>
# include	<QBrush>
# include	<QImage>
# include	<QPalette>
# include	<QHBoxLayout>

class		WidgetButton;
class		WidgetTextView;

class		ConversationWindow : public QMainWindow
{
  Q_OBJECT

public:
  static int	WIDTH;
  static int	HEIGHT;

private:
  WidgetButton		*_hangoutButton;
  WidgetButton		*_sendMessageButton;
  WidgetTextView	*_messageTextView;
  QVBoxLayout		*_mainLayout;
  QLineEdit		*_messageEdit;
  WidgetButton		*_quitButton;
  QLabel		*_video;

private slots:
  void		sendMessage();

public:
  ConversationWindow(QWidget *parent = 0);
  ~ConversationWindow();
};

#endif

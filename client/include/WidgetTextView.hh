#ifndef		__WIDGETTEXTVIEW_HH__
# define	__WIDGETTEXTVIEW_HH__

# include	<QListWidget>

class		WidgetTextView : public QListWidget
{
  Q_OBJECT

private:
  QString	_user;
  QString	_mate;
  QBrush	_userBrush;
  QBrush	_mateBrush;

public:
  void		addMessageFromUser(const QString&);
  void		addMessageFromMate(const QString&);

public:
  WidgetTextView(const QString& user, const QString& mate, QWidget *parent = 0);
  ~WidgetTextView();
};

#endif

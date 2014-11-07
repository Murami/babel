#ifndef		__WIDGETTEXTVIEW_HH__
# define	__WIDGETTEXTVIEW_HH__

# include	<QFrame>

class		WidgetTextView : public QFrame
{
  Q_OBJECT

private:
  QScrollArea	*_scrollArea;

public:
  WidgetTextView(QWidget *parent = 0);
  ~WidgetTextView();
};

#endif

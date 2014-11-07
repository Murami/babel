#ifndef		__WIDGETTEXTVIEW_HH__
# define	__WIDGETTEXTVIEW_HH__

# include	<QTextEdit>

class		WidgetTextView : public QTextEdit
{
  Q_OBJECT

public:
  WidgetTextView(QWidget *parent = 0);
  ~WidgetTextView();
};

#endif

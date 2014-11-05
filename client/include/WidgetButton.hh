#ifndef		__WIDGETBUTTON_HH__
# define	__WIDGETBUTTON_HH__

# include	<QString>
# include	<QRect>
# include	<QPaintEvent>
# include	<QPushButton>

# include	"ICallListener.hh"
# include	"ResourceManager.hpp"

class		WidgetButton : public QPushButton, public ICallListener
{
private:
  QPixmap	*_image;
  QRect		_drawRect;
  QString	_text;

public:
  WidgetButton(const QString& text, QWidget *parent = 0);
  ~WidgetButton();

public:
  virtual void	onCall(NET::CallInfo);

public:
  virtual void	paintEvent(QPaintEvent *);
  virtual void	enterEvent(QEvent *);
  virtual void	leaveEvent(QEvent *);
  virtual void	mousePressEvent(QMouseEvent *);
  virtual void	mouseReleaseEvent(QMouseEvent *);

};

#endif

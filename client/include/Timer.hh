#ifndef TIMER_HH
#define TIMER_HH

#include <QTimer>
#include <QObject>

class ITimerListener;

class Timer : public QObject
{
Q_OBJECT

public slots:
  void onTimeout();

public:
  Timer();
  ~Timer();

  int	interval() const;
  bool	isActive() const;
  void	setInterval(int msec);
  void	start(int msec);
  void	start();
  void	stop();
  int	getTimerId();

  void addListener(ITimerListener * listener);

public:
  static int			global_timer_id;

private:
  std::list<ITimerListener *>	listenerList;
  QTimer			m_timer;
  int				m_id;
};

#endif

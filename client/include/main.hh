#ifndef MAIN_H
#define MAIN_H

#include <QWidget>
#include <QUdpSocket>

struct test
{
  int n;
};

class ClientReader : public QWidget
{
  Q_OBJECT

public:
  QUdpSocket	sock;

public:
  ClientReader(QWidget *parent = 0);
  ~ClientReader();

public:
  void writeUdp(test *data);
  void bind();

private slots:
  void readUdp();
  void setReadyRead(QAbstractSocket::SocketState s);
};

#endif

#include <QString>
#include <QApplication>
#include <QPushButton>
#include <QtNetwork>

#include <QSettings>

#include "BabelCoreClient.hh"
#include "QTcpAsyncSocket.hh"

int main(int argc, char *argv[])
{
QApplication app(argc, argv);
QPushButton bouton("Salut les Zéros, la forme ?");
BabelCoreClient core;

core.run();

  bouton.show();
  return app.exec();
}

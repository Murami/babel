#include <QString>
#include <QApplication>
#include <QPushButton>
#include <QtNetwork>

#include "BabelCoreClient.hh"
#include "QTcpAsyncSocket.hh"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPushButton bouton("Salut les Zéros, la forme ?");
    BabelCoreClient core;

    core.connect("127.0.0.1", 4242);
    char *str = strdup("toto");
    core.write(str);

    bouton.show();
    return app.exec();
}

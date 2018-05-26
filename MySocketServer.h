/*
Cette classe instancie un serveur avec un objet "server_stat" et "cache", écoutant sur le port 8080
Il utilise une socket "MySocketServeur" pour traiter les requetes et communiquer avec le client
*/

#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QStringList>
#include <QTcpServer>
#include "MyFileCache.h"
#include "Server_stat.h"
#include "MySocketClient.h"


class MySocketServer : public QTcpServer
{
Q_OBJECT

public:
        MySocketServer(QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);

private:
    Server_stat statServer;

signals:
    void serverMessage();
};

#endif

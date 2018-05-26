/*
Cette classe est instanciee par le serveur
Elle traite la requete du client en utilisant les fonctionnalités de la classe QThread dont elle hérite
elle utilise les methodes statiques de Server_stat et MyfileCache pour utiliser/actualiser les données
*/

#ifndef FORTUNETHREAD_H
#define FORTUNETHREAD_H

#include <iostream>
#include "server_stat.h"
#include "MyFileCache.h"
#include "admin.h"

using namespace std;

#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QDir>



class MySocketClient : public QThread
{
    Q_OBJECT

public:
    MySocketClient(int socketDescriptor, QObject *parent);

    static bool activate;
    admin *Admin = new admin();
    void run();
    void directory(QString path, QFileInfoList list, QString fileName);
    void read(QTcpSocket tcpSocket);
signals:
    void error(QTcpSocket::SocketError socketError);
    void requestHTML();
    void RequestTraited();
    void newClient();
    void newstat();


private:
    int socketDescriptor;
    QString text;
};

#endif

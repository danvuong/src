
#include "MySocketServer.h"

#include <stdlib.h>

//! [0]
MySocketServer::MySocketServer(QObject *parent)
    : QTcpServer(parent)
{ 
    statServer.repaintstat();
    statServer.show();
}

void MySocketServer::incomingConnection(int socketDescriptor)
{
    cout << ""<<endl;
    cout << ""<<endl;
    cout << ""<<endl;
    cout << ""<<endl;
    cout << "(II) Launching the Network monitor process" << endl;


    // CREATION DE L'OBJET EN CHARGE DES REPONSES RESEAU
    MySocketClient *thread = new MySocketClient(socketDescriptor, this);


    //CONNEXIONS DES SLOTS ET SIGNAUX
    connect(thread ,SIGNAL(requestHTML()), &statServer, SLOT(statHTML()));//Slot mettant a jour la page html statistiques
    connect(thread ,SIGNAL(newstat()), &statServer, SLOT(repaintstat()));//Slot mettant a jour le widget statistiques




    // ON INDIQUE QUE LORSQU'UN CLIENT SE CONNECTE ON DELEGE LA REPONSE
    // AU PROCESSUS DEFINI CI DESSUS...
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    // ON DEMARRE LE PROCESSUS DE REPONSE POUR LE METTRE EN ATTENTE !
    thread->start();

    // PUIS ON REND LA MAIN EN ATTENTE D'UN CLIENT
    cout << "(II) Network monitor process launch : OK" << endl;
}



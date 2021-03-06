/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the example classes of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include "MySocketClient.h"
#include <QtNetwork>
#include <QString>
#include <fstream>
#include <QDebug>
#include <QByteArray>
#include <QVector>

bool MySocketClient::activate=true;

MySocketClient::MySocketClient(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{


}

inline string removeEndLine(string s){
        while( s.at(s.length()-1) == '\r' ||
                        s.at(s.length()-1) == '\n' ){
                s = s.substr(0, s.length()-1);
        }
        return s;
}

void MySocketClient::run()
{
    emit requestHTML(); // Fonction mettant à jour la page de statistiques
    Server_stat::updateStat(NEWCLIENT, 1);//Met à jour le nombre de clients

    cout << "Starting MySocketClient::run()" << endl;
    QTcpSocket tcpSocket;




    // ON RECUPERE LE LIEN DE COMMUNICATION AVEC LE CLIENT ET ON QUITTE EN CAS
    // DE PROBLEME...
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    // SI LE CLIENT N'A PAS EU LE TEMPS DE NOUS TRANSMETTRE SA REQUETE,
    // ON SE MET EN ATTENTE PENDANT 1s
    while (tcpSocket.bytesAvailable() < (int)sizeof(quint16)) {
        if (!tcpSocket.waitForReadyRead( 1000 )) {
                cout << "(EE) Erreur de time out !" << endl;
                return;
        }
    }

    // LA PREMIERE REQUETE CORRESPOND AU GET NORMALEMENT
    char tampon[65536];

    // ON RECUPERE LA REQUETE ET SA TAILLE
    int lineLength = tcpSocket.readLine(tampon, 65536);

    //ON RECUPERE LES INFORMATIONS RECUS PAR LE SERVEUR
    QVector<QString> array;
    while (tcpSocket.bytesAvailable())
        {
           QString temp = tcpSocket.readLine();
           array.append(temp);
        }
    //DANS LE CAS DE LA PAGE ADMIN
    Admin->findId(array); //Récupère et vérifie le mot de passe de l'utilisateur

    //DANS LE CAS DE LA PAGE DE CONFIGURATION
    Admin->findActivate(array);//Verifie la demande d'activation/désactivation du serveur


    // ON ENREGISTRE LE NB D'OCTETS RECUS
    Server_stat::updateStat(NEWOCTETSRECEIVED, lineLength);

    // ON TRANSFORME LA REQUETE SOUS FORME DE STRING
    string ligne( tampon );
    ligne = removeEndLine( ligne );



    // ON AFFICHE LA COMMANDE A L'ECRAN...
    cout << "COMMANDE : =>" << ligne << "<=" << endl;
    Server_stat::updateStat(NEWREQUEST, 1);

   int pos1 = ligne.find(" ");
   string cmde = ligne.substr(0, pos1);
   ligne = ligne.substr(pos1+1, ligne.length()-pos1);

   cout << "1. : " << cmde  << endl;
   cout << "2. : " << ligne << endl;

   int pos2 = ligne.find(" ");
   string fileName = ligne.substr(0, pos2);
   ligne = ligne.substr(pos2+1, ligne.length()-pos2);

   cout << "3. : " << fileName  << endl;
   cout << "4. : '" << ligne << "'" << endl;

        while( tcpSocket.bytesAvailable() > 0 ){
        int lineLength = tcpSocket.readLine(tampon, 65536);
        if (lineLength != -1 &&  lineLength != 0) {

        }else if(lineLength != -1 ){
                cout << "Nothing for the moment !" << endl;
        }
    }

   QString str = tr("public_html") + tr(fileName.c_str());
   QFile f( str );
   QDir  d( str );

   Server_stat::addTypeOfRequest(str.toStdString());//enregistre le chemin demandé

   cout << " - Chemin du fichier : " << str.toStdString() << endl;
   cout << " - isFile :          : " << f.exists() << endl;
   cout << " - isDirectory       : " << d.exists() << endl;

   if( f.exists() == false &&  d.exists() == false ){

       // ERREUR 404 LE FICHIER N'EXISTE PAS...
       cout << "### erreur 404 ####" <<endl;
       str = tr("public_html") + tr("/err404.html");
       QFile* file = new QFile( str );
       int tailleFichier = file->bytesAvailable();
        if (!file->open(QIODevice::ReadWrite))
        {
                delete file;
                return;
        }
        tcpSocket.write("HTTP/1.1 200"); //pb : echappement necessaire apres <!DOCTYPE html> ???

        // enregistre le nb de bytes envoyes
        Server_stat::updateStat(NEWOCTETSSEND, tailleFichier);

        tcpSocket.write( file->readAll() );

//######################### Si c'est un DOSSIER ###################
   }else if( d.exists() == true ){
       d.setFilter(QDir::Files|QDir::NoDotAndDotDot|QDir::Dirs | QDir::Hidden | QDir::NoSymLinks);
       d.setSorting(QDir::Size | QDir::Reversed);

       QFileInfoList list = d.entryInfoList();//Liste contenant tout les fichiers du dossier
       for (int i = 0; i < list.size(); ++i) {
           QFileInfo fileInfo = list.at(i);
           std::cout << qPrintable(QString("%1").arg(fileInfo.fileName()));
           std::cout << std::endl;
        }

       directory("public_html/directory.html", list, d.dirName());//Fonction mettant à jour la page d'acces au dossier

       tcpSocket.write("HTTP/1.1 200\n");
       QString str2 = tr("public_html/directory.html");
       QFile* file2 = new QFile( str2 );
       if (!file2->open(QIODevice::ReadWrite))
       {
               delete file2;
               return;
       }
       tcpSocket.write( file2->readAll() );//Ouvre la page permettant d'acceder au dossier
       file2->close();

 //################ SI c'est un FICHIER ############################
   }else if( f.exists() == true ){
       tcpSocket.write("HTTP/1.1 200\n\n");
       int tailleFichier = 0;

   //Si le serveur est actif ou si la page requise est pour l'admin
   if(activate==true || !fileName.compare("/admin.html") || !fileName.compare("/config.html")){

                //Si le fichier n'est pas dans le cache
           if(MyFileCache::IsInCache( str ) == 0){

               QFile* file = new QFile( str );
               tailleFichier = file->bytesAvailable();
                if (!file->open(QIODevice::ReadWrite))
                {
                        delete file;
                        return;
                }

                    //Si on demande la page de config
                if(fileName.compare("/config.html") == 0)
                {
                    //Verif mdp recu pour droit d'acces
                    if(Admin->testMdp() )
                    {
                        cout << "  MDP  ----->   OK  " << endl;
                        QByteArray data = file->readAll();
                        tcpSocket.write( data );//On renvoit la page de config
                            // enregistre le nb de bytes envoyes
                        Server_stat::updateStat(NEWOCTETSSEND, tailleFichier);
                            //Comptabilise la nouvelle requete effectuée
                        Server_stat::updateStat(NEWREQUESTDONE, 1);
                            //on stocke le fichier dans le cache
                        MyFileCache::StoreInCache( str, data );
                        file->close();
                    }
                    else {//Mauvais mot de passe
                        cout << "   PAS LE BON MDP" << endl;
                        delete file;
                        QString str2 = tr("public_html/admin.html");
                        QFile* file2 = new QFile( str2 );
                        if (!file2->open(QIODevice::ReadWrite))
                        {
                                delete file2;
                                return;
                        }
                        tcpSocket.write( file2->readAll() );//On renvoit la page admin
                        file2->close();
                    }
                }

                else  //Si ce n'est pas la page config on envoie la page
                {
                    QByteArray data = file->readAll();
                    tcpSocket.write( data );    //On renvoit la page
                        // Enregistre le nb de bytes envoyes
                    Server_stat::updateStat(NEWOCTETSSEND, tailleFichier);
                        // Comptabilise la nouvelle requete effectuée
                    Server_stat::updateStat(NEWREQUESTDONE, 1);
                        // On stocke le fichier dans le cache
                    MyFileCache::StoreInCache( str, data ); // stoske la page dans le cache
                    file->close();
                }
       }else{   //si le fichier est dans le cache, on l'envoie a partir de celui-ci
               tailleFichier = MyFileCache::LoadFromCache( str ).size();    // Recupere taille depuis cache
               tcpSocket.write( MyFileCache::LoadFromCache( str ) );    // Recupere fichier depuis cache
                    // enregistre le nb de bytes envoyes
               Server_stat::updateStat(NEWOCTETSSEND, tailleFichier);
                    //Comptabilise la nouvelle requete effectuée
               Server_stat::updateStat(NEWREQUESTDONE, 1);

       }
   } //Fin si activate == true


   }else{  //Le serveur est desactive et la page requise n'est pas une exception  --> ne renvoie rien

   }
    // FIN DE LA CONNEXION CLIENT
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
    cout << "Finishing MySocketClient::run()" << endl;
    emit newstat();    // Signal pour Server_stat : rafraichir la fenetre des stats
}


//FONCTION GESTION DE REQUETE DOSSIER
void MySocketClient::directory(QString path,  QFileInfoList list, QString fileName){
    QString chemin = path;
    QFile fichier(chemin);
    if(fichier.open(QIODevice::WriteOnly))
    {
        QTextStream flux(&fichier);
        flux << "<!DOCTYPE html>\n";
        flux << "\n";
        flux << "<html>\n";
        flux << "<head>\n";
        flux << "   <title>"+ fileName +"</title>\n";
        flux << "</head>\n";

        flux << "<body>\n";
        flux << "<p> VOUS ETES DANS LE DOSSIER:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + fileName + "</p>\n";
        flux << "\n";

            //Cas particulier si on demande la dossier public_html (car par default "public_html" est ajouté
            //au chemin demandé pour se placer dans le dossier public_html qui contient les pages HTML)
        if(QString::compare(fileName, "public_html", Qt::CaseInsensitive) != 0)
        {
            for (int i = 0; i < list.size(); ++i) {
                QFileInfo fileInfo = list.at(i);
                flux << "<p><a href=\""+ fileName+"/"+ QString("%1").arg(fileInfo.fileName()) +"\">" + QString("%1").arg(fileInfo.fileName()) +"</a></p>\n";//Lien cliquable vers le fichier
             }
        }
        else// dans tout les autres cas
        {
            for (int i = 0; i < list.size(); ++i) {
                QFileInfo fileInfo = list.at(i);
                flux << "<p><a href=\""+ QString("%1").arg(fileInfo.fileName()) +"\">" + QString("%1").arg(fileInfo.fileName()) +"</a></p>\n";
             }
        }

        flux << "</body>\n";
        flux << "</html>\n";
        fichier.close();
    }
}



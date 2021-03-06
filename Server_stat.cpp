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

#include <QtWidgets>
#include <QtNetwork>
#include <QString>
#include <QTextEdit>   // Nous allons tout de même afficher le contenu du fichier ^^
#include <QFile>       // Pour utiliser le fichier
#include <QString>     // Stocke le contenu du fichier
#include <QTextStream> // Flux sortant du fichier
#include <QVector>

#include <stdlib.h>
#include <iostream>
#include <string>
#include <QDateTime>

#include "Server_stat.h"


// VARIABLES
int Server_stat::count_client = 0;  //nb clients tot
int Server_stat::count_request_received = 0; //nom tendancieux
int Server_stat::count_request_done = 0; //nb requetes traitees
int Server_stat::count_error = 0;    //nb erreur de chaque type
int Server_stat::count_octets_received = 0;   //nb octets recus
int Server_stat::count_octets_send = 0;    //nb octets transmis
int Server_stat::request_received = 0; //quel tyoe de donnee pr une requete ?
file_type Server_stat::files_requested[TAILLE_MAX_TABLEAU]; //noms+nb de tel des fichiers
all_file_type Server_stat::all_files_requested[TAILLE_MAX_TABLEAU];

Server_stat::Server_stat(QWidget *parent)
    : QDialog(parent)
{
    //CREATION DU WIDGET STAT SERVEUR
    statusLabel = new QLabel;
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    QString message = QString::number(count_client);
    statusLabel->setText(tr("stats du serveur !! tamere ") + message);


    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Stat Server"));

}

// SLOT

//Fonction mettant a jour la page HTML de statistiques
void Server_stat::statHTML()
{
    QString str_count_request_received = QString::number(count_request_received);

    QString str_count_request_done = QString::number(count_request_done);

    QString str_count_client = QString::number(count_client);

    QString str_count_octets_received = QString::number(count_octets_received);

    QString str_count_octets_send = QString::number(count_octets_send);

    QString chemin;
    chemin = "public_html/statistiques.html";
    QFile fichier(chemin); 
    QVector<QString> stats;

    if(fichier.open(QIODevice::WriteOnly))
    {
        std::cout << "####### FICHIER STATS OUVERT  #######" << std::endl;
        QTextStream flux(&fichier);

        //flux << "HTTP/1.1 200\n";
        flux << "<!DOCTYPE html>\n";
        flux << "\n";
        flux << "<style>\n";
        flux << "#container{\n";
        flux << "   width: 800px;\n";
        flux << "   height: 200px;\n";
        flux << "   border: 1px solid black;\n";
        flux << "   overflow: scroll;\n";
        flux << "}\n";
        flux << "</style>\n";
        flux << "<html>\n";
        flux << "<head>\n";
        flux << "   <title>Statistiques</title>\n";
        flux << "</head>\n";

        //####### CORPS DU TEXTE ########

        //Affiche les différentes statistiques du serveur
        flux << "<body>\n";
        flux << "   <p> STATISTIQUES: </p>\n";
        flux << "<p> Nombre de requetes reçues: " + str_count_request_received + "</p\n";
        flux << "<p> Nombre de requetes traitées: " + str_count_request_done + "</p>\n";
        flux << "<p> Nombre de clients: " + str_count_client + "</p>\n";
        flux << "<p> Nombre d'octets envoyés: " + str_count_octets_send + "</p>\n";
        flux << "<p> Nombre d'octets reçus: " + str_count_octets_received + "</p>\n";


            //## FENETRE DEROULANTE

        //Log des requetes effectuées
        flux << "<div id=\"container\">\n";

        int i=0;
        while ( all_files_requested[i].chemin.compare("") && i<TAILLE_MAX_TABLEAU && all_files_requested[i].chemin.compare("public_html/favicon.ico"))
        {
            flux << "<p>" + QString::fromStdString(all_files_requested[i].chemin)+"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+ all_files_requested[i].date + "</p>\n";
            i++;
        }
        flux << "</div>\n";
            //
        flux << "</body>\n";
        //##############################

        flux << "</html>\n";
        fichier.close();
    }
    else{
        std::cerr << "ERREUR FICHIER" << std::endl;
    }
}


// STATIC

//Fonction incrementant les statistiques du serveur
void Server_stat::updateStat(typeStat type, int data){
    //std::cout << "######## UPDATE DES STATS :::: " << type << " - " << data << "   ###############" << std::endl;
    switch ( type ) {
    case NEWCLIENT :
        count_client++;
        break;
    case NEWREQUEST:
        count_request_received++;
        break;
    case NEWREQUESTDONE:
        count_request_done++;
        break;
    case NEWERROR:
        count_error++;
        break;
    case NEWOCTETSRECEIVED:
        count_octets_received += data;
        break;
    case NEWOCTETSSEND:
        count_octets_send += data;
        break;
    default :
        std::cout << " ERROR : unknow updateStat string type \n" << std::endl;
        break;
    }
}


    //Fonction comptabilisant les requetes par types (ex : nb de requetes pour index.html, admin.html etc...)
void Server_stat::addTypeOfRequest(std::string chemin){
    int i = 0;
    int k = 0;
    bool already_added = false;
    while ( files_requested[i].chemin.compare("") && i<TAILLE_MAX_TABLEAU){
        if( !chemin.compare(files_requested[i].chemin) ){
            files_requested[i].nombre++;
            already_added = true;
        }
        i++;
    }
    if(!already_added && i<TAILLE_MAX_TABLEAU){
        files_requested[i].chemin = chemin;
        files_requested[i].nombre = 1;
    }
    while(all_files_requested[k].chemin.compare("") && k<TAILLE_MAX_TABLEAU){
        k++;
    }
    QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
    all_files_requested[k].chemin = chemin;
    all_files_requested[k].date = sDate;

    //std::cout << "       type de requete ajoutee : " << files_requested[i].chemin << "en position : " << i << std::endl;
}


// SLOT

//Fonction mettant à jour le widget statistiques (rafraichissement de la fenetre)
void Server_stat::repaintstat(){

    QString message1 = QString::number(count_request_received);
    QString message2 = QString::number(count_request_done);
    QString message3 = QString::number(count_client);
    QString message4 = QString::number(count_error);
    QString message5 = QString::number(count_octets_received);
    QString message6 = QString::number(count_octets_send);
    std::string message71 = files_requested[0].chemin + " : ";
    QString message72 = QString::number(files_requested[0].nombre);
    statusLabel->setText(tr(" nb de requetes recues :  ") + message1 +
                         tr("\n\n nb de requetes traitees :  ") + message2 +
                         tr("\n\n nb de clients enregistres :  ") + message3 +
                         tr("\n\n nb d'erreurs detectees :  ") + message4 +
                         tr("\n\n nb d'octets recus :  ") + message5 +
                         tr("\n\n nb d'octets envoyes :  ") + message6 +
                         tr("\n\n requetes effectuees : ") + tr(message71.c_str()) +  message72);

}

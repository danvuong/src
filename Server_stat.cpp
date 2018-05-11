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


#include <stdlib.h>
#include <iostream>

#include "Server_stat.h"

// VARIABLES
int Server_stat::count_client = 0;  //nb clients tot
int Server_stat::count_request_received = 0; //nom tendancieux
int Server_stat::count_request_done = 0; //nb requetes traitees
int Server_stat::count_error = 0;    //nb erreur de chaque type
int Server_stat::count_octets_received = 0;   //nb octets recus
int Server_stat::count_octets_send = 0;    //nb octets transmis
int Server_stat::request_received = 0; //quel tyoe de donnee pr une requete ?

Server_stat::Server_stat(QWidget *parent)
    : QDialog(parent)
{
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
void Server_stat::test()
{
    QString str_count_request_received = QString::number(count_request_received);

    QString str_count_request_done = QString::number(count_request_done);

    QString str_count_client = QString::number(count_client);

    QString str_count_octets_received = QString::number(count_octets_received);

    QString str_count_octets_send = QString::number(count_octets_send);

    QString chemin;
    chemin = "public_html/statistiques.html";
    QFile fichier(chemin);
    if(fichier.open(QIODevice::WriteOnly))
    {
        std::cout << "####### FICHIER OUVERT" << std::endl;
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
        flux << "<body>\n";
        flux << "   <p> STATISTIQUES: </p>\n";
        flux << "<p> Nombre de requetes reçues: " + str_count_request_received + "</p\n";
        flux << "<p> Nombre de requetes traitées: " + str_count_request_done + "</p>\n";
        flux << "<p> Nombre de clients: " + str_count_client + "</p>\n";
        flux << "<p> Nombre d'octets envoyés: " + str_count_octets_send + "</p>\n";
        flux << "<p> Nombre d'octets reçus: " + str_count_octets_received + "</p>\n";


            // Fenetre deroulante
        flux << "<div id=\"container\">\n";
        flux << "\n";
        flux << "</div>\n";
            //
        flux << "</body>\n";
        //##############################

        flux << "</html>\n";
        fichier.close();
    }
    else
        std::cerr << "ERREUR FICHIER" << std::endl;
}


// STATIC
void Server_stat::updateStat(typeStat type, int data){
    std::cout << "######## UPDATE DES STATS :::: " << type << " - " << data << "   ###############" << std::endl;
    switch ( type ) {
    case NEWCLIENT :
        count_client++;
        std::cout << " NEWCLIENT : nb de clients detectes :  " << count_client << std::endl;
        break;
    case NEWREQUEST:
        count_request_received++;
        std::cout << " NEWREQUEST : nb de requetes detectes :  " << count_request_received << std::endl;
        break;
    case NEWREQUESTDONE:
        count_request_done++;
        std::cout << " NEWREQUESTDONE : nb de requetes effectuees :  " << count_request_done << std::endl;
        break;
    case NEWERROR:
        count_error++;
        std::cout << " NEWERROR : nb d'erreurs detectees :  " << count_error << std::endl;
        break;
    case NEWOCTETSRECEIVED:
        count_octets_received += data;
        std::cout << " NEWOCTETS : nb d'octets recus :  " << count_octets_received << std::endl;
        break;
    case NEWOCTETSSEND:
        count_octets_send += data;
        std::cout << " NEWOCTETS : nb d'octets envoyes :  " << count_octets_send << std::endl;
        break;
    /*case NEWREQUEST:
        count_request_received++;
        std::cout << " NEWCLIENT : nb de clients detectes :  " << count_client << std::endl;
        break;
    */
    default :
        std::cout << " ERROR : unknow updateStat string type \n" << std::endl;
        break;
    }
}

// SLOT
void Server_stat::repaintstat(){

    QString message1 = QString::number(count_request_received);
    QString message2 = QString::number(count_request_done);
    QString message3 = QString::number(count_client);
    QString message4 = QString::number(count_error);
    QString message5 = QString::number(count_octets_received);
    QString message6 = QString::number(count_octets_send);
    statusLabel->setText(tr(" nb de requetes recues :  ") + message1 +
                         tr("\n\n nb de requetes traitees :  ") + message2 +
                         tr("\n\n nb de clients enregistres :  ") + message3 +
                         tr("\n\n nb d'erreurs detectees :  ") + message4 +
                         tr("\n\n b d'octets recus :  ") + message5 +
                         tr("\n\n b d'octets envoyes :  ") + message6 );

}

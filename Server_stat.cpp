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

Server_stat::Server_stat(QWidget *parent)
    : QDialog(parent)
{
    statusLabel = new QLabel;
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    count = 0;
    count_request_recu=0;
    QString message = QString::number(count);
    statusLabel->setText(tr("nb connections detectees : ") + message);


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

void Server_stat::messageFromServer(){
    count++;
    QString message = QString::number(count);

    std::cout << "######## MESSAGE FROM SERVER" << std::endl;
    statusLabel->setText(tr("nb connections detectees : ") + message);
}

void Server_stat::test()
{
    count_request_recu++;
    QString str_count_request_recu = QString::number(count_request_recu);
    std::cout << "######## NOMBRE REQUETE RECU: " << count_request_recu << std::endl;

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
        flux << "<html>\n";
        flux << "<head>\n";
        flux << "   <title>Statistiques</title>\n";
        flux << "</head>\n";

        //####### CORPS DU TEXTE ########
        flux << "<body>\n";
        flux << "   <p> STATISTIQUES: </p>\n";
        flux << "<p> Nombre de requetes reçues: " + str_count_request_recu + "</p>";
        flux << "</body>\n";
        //##############################

        flux << "</html>\n";
        fichier.close();
    }
    else
        std::cerr << "ERREUR FICHIER" << std::endl;


}

#include <QString>
#include <QTextEdit>   // Nous allons tout de même afficher le contenu du fichier ^^
#include <QFile>       // Pour utiliser le fichier
#include <QString>     // Stocke le contenu du fichier
#include <QTextStream> // Flux sortant du fichier


#include <stdlib.h>
#include <string>
#include <QDateTime>
#include <QVector>
#include <iostream>

#include "admin.h"

admin::admin()
{

}

void admin::findId(QVector<QString> array)
{
    std::string formLigne;
    for(int i=0;i<array.size();i++)
    {
        std::string tempLigne = array[i].toStdString();
        int found = tempLigne.find("usr");
        if(found!=std::string::npos)
        {
            std::cout << array[i].toStdString() << std::endl;
            formLigne = array[i].toStdString();
        }
    }

    int posi1 = formLigne.find("=");
    int posi2 = formLigne.find("&");
    user = formLigne.substr(posi1+1,posi2-posi1-1);
    formLigne = formLigne.substr(posi2+1,std::string::npos);
    std::cout << "|||||||||||||||||||||" << user << std::endl;

    posi1 = formLigne.find("=");
    mdp = formLigne.substr(posi1+1,std::string::npos);
    std::cout << "|||||||||||||||||||||" << mdp << std::endl;
}

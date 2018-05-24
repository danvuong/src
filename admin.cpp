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
#include "MySocketClient.h"



admin::admin()
{
    QVector<std::string> temp;
    temp.append("Dan");
    temp.append("admin");
    listAdmin.append(temp);
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
    std::cout << "|||||||||||||||||||||" << testMdp() << std::endl;

}

void admin::findActivate(QVector<QString> array)
{
    std::string formLigne;
    for(int i=0;i<array.size();i++)
    {
        std::string tempLigne = array[i].toStdString();
        int found = tempLigne.find("activate");
        if(found!=std::string::npos)
        {
            std::cout << array[i].toStdString() << std::endl;
            formLigne = array[i].toStdString();
        }
        int foundcache =  tempLigne.find("vider+le+cache");
        if(foundcache!=std::string::npos)
        {
            std::cout << array[i].toStdString() << std::endl;
            formLigne = array[i].toStdString();
        }
    }

    int posi1 = formLigne.find("=");
    int posi2 = formLigne.find("&");
    std::string testActivate;
    testActivate = formLigne.substr(posi1+1,posi2-posi1-1);
    formLigne = formLigne.substr(posi2+1,std::string::npos);

    if (!testActivate.compare("activate"))
    {
        MySocketClient::activate = !MySocketClient::activate;

    }
    if ( !testActivate.compare("vider+le+cache")){
        MyFileCache::EmptyCache();
    }

}

int admin::testMdp()
{
    for(int i=0;i<listAdmin.size();i++)
    {
        if(listAdmin[i][0].compare(user)==0)
        {
            if(listAdmin[i][1].compare(mdp)==0)
            {
                return 1;
            }
            else
                return 0;
        }
    }
    return 0;
}

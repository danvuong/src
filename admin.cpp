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

//FONCTION DE RECUPERATION MOT DE PASSE ET ID
void admin::findId(QVector<QString> array)
{
    std::string formLigne;
    for(int i=0;i<array.size();i++)
    {
        //on parcours toutes les lignes de la requetes pour trouver le mot "usr"
        std::string tempLigne = array[i].toStdString();
        int found = tempLigne.find("usr");
        if(found!=std::string::npos)
        {
            std::cout << "     DEMANDE DE DROITS DETECTEE :     " << array[i].toStdString() << std::endl;
            formLigne = array[i].toStdString();//on récupère la ligne contenant l'identifiant et le mot de passe
        }
    }

    int posi1 = formLigne.find("=");
    int posi2 = formLigne.find("&");
    user = formLigne.substr(posi1+1,posi2-posi1-1);//On ne recupere que l'identifiant
    formLigne = formLigne.substr(posi2+1,std::string::npos);

    posi1 = formLigne.find("=");
    mdp = formLigne.substr(posi1+1,std::string::npos);//On ne recupere que le mot de passe
}


//FONCTION DE VERIFICATION ACTIVATION/DESACTIVATTION SERVEUR
void admin::findActivate(QVector<QString> array)
{
    std::string formLigne;
    for(int i=0;i<array.size();i++)
    {
        //on parcours toutes les lignes de la requetes pour trouver le mot "activate"...
        std::string tempLigne = array[i].toStdString();
        int found = tempLigne.find("activate");
        if(found!=std::string::npos)
        {
            formLigne = array[i].toStdString();
        }
        //... ou le mot "vider le cache"
        int foundcache =  tempLigne.find("vider+le+cache");
        if(foundcache!=std::string::npos)
        {
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
        std::cout << "      ACTIVATION OU DESACTIVATION DU SERVEUR   :    " << std::endl;
        MySocketClient::activate = !MySocketClient::activate;

    }
    if ( !testActivate.compare("vider+le+cache")){
        MyFileCache::EmptyCache();
    }

}

//FONCTION TESTANT LE MOT DE PASSE ET L'IDENTIFIANT
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

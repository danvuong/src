/*
 * Cette classe possede des methodes et des attributs statiques pour enregistrer les donnees d'utilisation du serveur
 *
*/


#ifndef SERVER_STAT_H
#define SERVER_STAT_H

#include <QtWidgets/QDialog>
#include <QString>
#include <string>


QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

#define TAILLE_MAX_TABLEAU 512



typedef enum typestat{
    NEWCLIENT,
    NEWREQUEST,
    NEWREQUEST_TYPE,
    NEWREQUESTDONE,
    NEWERROR,
    NEWOCTETSRECEIVED,
    NEWOCTETSSEND
} typeStat;

struct file_type{
    std::string chemin = "";
    int nombre = 0;
};


struct all_file_type{
    std::string chemin = "";
    QString date = "";
};

class Server_stat : public QDialog
{
    Q_OBJECT

public:
    Server_stat(QWidget *parent = 0);
    static void updateStat(typeStat type, int data);
    static void addTypeOfRequest(std::string chemin);


private:
    QLabel *statusLabel;
    QPushButton *quitButton;

    static int count_client;   //nb clients tot
    static int count_request_received; //nom tendancieux
    static int count_request_done; //nb requetes traitees
    static int count_error;    //nb erreur de chaque type
    static int count_octets_received;   //transmis/recus
    static int count_octets_send;   //transmis/recus
    static int request_received; //quel tyoe de donnee pr une requete ?
    static file_type files_requested[TAILLE_MAX_TABLEAU]; //noms+nb de tel des fichiers
    static all_file_type all_files_requested[TAILLE_MAX_TABLEAU];


public slots:
    void statHTML();
    void repaintstat();

};

#endif

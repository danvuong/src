/*
 * Cette classe permet de verifier les droits de l'utilisateur
*/


#ifndef ADMIN_H
#define ADMIN_H


#include <string>
#include <QVector>



class admin
{


   private:
    std::string mdp;
    std::string user;
    QVector< QVector < std::string > > listAdmin;

   signals:
    void signalActivate();

   public:
    static bool activate;
    admin();
    void findId(QVector<QString> array);
    void findActivate(QVector<QString> array);
    int testMdp();

};

#endif // ADMIN_H

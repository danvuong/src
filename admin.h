#ifndef ADMIN_H
#define ADMIN_H


#include <string>
#include <QVector>



class admin
{
   private:
    std::string mdp;
    std::string user;
    QVector<QVector<std::string>> listAdmin;

   public:
    admin();
    void findId(QVector<QString> array);
    int testMdp();

};

#endif // ADMIN_H

#ifndef ADMIN_H
#define ADMIN_H


#include <string>
#include <QVector>



class admin
{
   private:
    std::string mdp;
    std::string user;

   public:
    admin();
    void findId(QVector<QString> array);

};

#endif // ADMIN_H

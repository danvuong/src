#ifndef MYFILECACHE_H
#define MYFILECACHE_H


#include <QtWidgets/QDialog>
#include <QString>
#include <string>
#include <QHash>
#include <QFile>
#include <QByteArray>



class MyFileCache
{

public:
    MyFileCache();
    ~MyFileCache();
    static void StoreInCache(QString name, QByteArray array);
    static QByteArray LoadFromCache(QString name);
    static int IsInCache(QString name);
    static void EmptyCache();


private:
    static int count;   //
    static QHash<QString , QByteArray> cache;


public slots:


};

#endif

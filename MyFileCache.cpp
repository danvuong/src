#include "myfilecache.h"
#include <iostream>

QHash<QString, QByteArray> MyFileCache::cache;



MyFileCache::MyFileCache(QWidget *parent){

}

//STATIC
void MyFileCache::UpdateCache(QString name){
    if (!cache.contains(name)){
        QFile *file = new QFile( name );
        cache.insert(name, file->readAll());
        std::cout << "###### CACHE UPDATED : " << name.toStdString() << std::endl;
    }
}

int MyFileCache::IsInCache(QString name){
    if (cache.contains(name)){
        return 1;  //le fichier est deja dans le cache
    }else{
        return 0;   //Le fichier n'est pas dans le cache
    }
}


void MyFileCache::LoadCache(QString name, QFile *file){
    file->write(cache[name]);
    std::cout << "###### LOADED FROM CACHE : " << name.toStdString() << std::endl;
}

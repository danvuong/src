#include "myfilecache.h"
#include <iostream>

QHash<QString, QByteArray> MyFileCache::cache;



MyFileCache::MyFileCache(QWidget *parent){

}

//STATIC
void MyFileCache::StoreInCache(QString name, QByteArray array){
    if (!cache.contains(name)){
        cache.insert(name, array);
        std::cout << "###### CACHE UPDATED : " << name.toStdString() << std::endl;
    }
}



QByteArray MyFileCache::LoadFromCache(QString name){
    QByteArray array = cache[name];
    std::cout << "###### LOADED FROM CACHE : " << name.toStdString() << std::endl;
    std::cout << "######### on a ca :: " << array.data() << std::endl;
    return array;
}


int MyFileCache::IsInCache(QString name){
    if (cache.contains(name)){
        return 1;  //le fichier est deja dans le cache
    }else{
        return 0;   //Le fichier n'est pas dans le cache
    }
}

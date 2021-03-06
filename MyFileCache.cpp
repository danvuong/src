#include "myfilecache.h"
#include <iostream>


// Hash contenant le cache
QHash<QString, QByteArray> MyFileCache::cache;



MyFileCache::MyFileCache(){

}

// ajoute une donnee dans le Hash
void MyFileCache::StoreInCache(QString name, QByteArray array){
    // on verifie que le fichier n'est pas dans le cache et n'est pas une page dynamique :
    if (!cache.contains(name) && QString::compare(name, "public_html/statistiques.html") != 0 && QString::compare(name, "public_html/config.html") != 0 ){
        cache.insert(name, array);
        std::cout << "###### CACHE UPDATED : " << name.toStdString() << std::endl;
    }
}


// Recupere une donnee stockée dans le hash
QByteArray MyFileCache::LoadFromCache(QString name){
    if(cache.contains(name)){
        QByteArray array = cache[name];
        std::cout << "###### LOADED FROM CACHE : " << name.toStdString() << std::endl;
        return array;
    }else{
        std::cout << "###### ERROR LOAD UNKNOWN FROM CACHE !!! " << std::endl;
        QByteArray array = "erreur cache";
        return array;
    }
}


// Indique si une donnée est deja dans le hash à partir de sa clef d'identification
int MyFileCache::IsInCache(QString name){
    if (cache.contains(name)){
        return 1;  //le fichier est deja dans le cache
    }else{
        return 0;   //Le fichier n'est pas dans le cache
    }
}

// Vide le cache
void MyFileCache::EmptyCache(){
    std::cout << "########## VIDAGE CACHE DEMANDE ########"<< std::endl;
    std::cout << "########## TAILLE AVANT VIDAGE : " << cache.size() << std::endl;
    cache.clear();  //Vide le hash
    std::cout << "##########  TAILLE APRES VIDAGE : " << cache.size() << std::endl;
}

#include "Server_stat.h"

Server_stat::Server_stat()
{
    count_request_received = 0; //nom tendancieux
    count_request_traited = 0; //nb requetes traitees
    count_error_occured = 0;    //nb erreur de chaque type
    count_client = 0;   //nb clients tot
    count_bytes = 0;   //transmis/recus
//    StatCount request_received[256]; //quel tyoe de donnee pr une requete ?
//    StatCount fich_down[256]; //noms+nb de tel des fichiers

}

void Server_stat::show(){

}


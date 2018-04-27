#ifndef SERVER_STAT_H
#define SERVER_STAT_H

class Server_stat
{
public:
    Server_stat(){
        count_request_recu = 0;
        count_request_done = 0;
        count_error = 0;
        count_client = 0;
        count_octets = 0;
        request_received = 0;
        //fich_down = 0;
    }

private:
    int count_request_recu; //nom tendancieux
    int count_request_done; //nb requetes traitees
    int count_error;    //nb erreur de chaque type
    int count_client;   //nb clients tot
    int count_octets;   //transmis/recus
    int request_received; //quel tyoe de donnee pr une requete ?
    int fich_down[256]; //noms+nb de tel des fichiers


};

#endif // SERVER_STAT_H

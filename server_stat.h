#ifndef SERVER_STAT_H
#define SERVER_STAT_H



#include <string>

using namespace std;


struct StatCount {
    string name;
    int number;
};


class Server_stat
{
public:
    Server_stat();
    void fileSend(string _name, int _number);
    void add_A_Request(string _type);
    void add_A_Done_request();
    void addError();
    void addClient();
    void addBytes(int _nb);
    void show();



private:
    int count_request_received; //nom tendancieux
    int count_request_traited; //nb requetes traitees
    int count_error_occured;    //nb erreur de chaque type
    int count_client;   //nb clients tot
    int count_bytes;   //transmis/recus
    StatCount request_received[256]; //quel tyoe de donnee pr une requete ?
    StatCount fich_down[256]; //noms+nb de tel des fichiers



};

#endif // SERVER_STAT_H

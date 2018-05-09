// MaFenetre.h

#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QtWidgets/QDialog>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class testducul : public QDialog
{
    Q_OBJECT

    public:
    int count_request_recu = 0; //nom tendancieux
    int count_request_done=0; //nb requetes traitees
    int count_error=0;    //nb erreur de chaque type
    int count_client=0;   //nb clients tot
    int count_octets=0;   //transmis/recus
    int request_received; //quel tyoe de donnee pr une requete ?
    int fich_down[256]; //noms+nb de tel des fichiers
    testducul(QWidget *parent = 0);
    void _addrequete();

    public slots:
    void ouvrirDialogue();

    private:
    QPushButton *m_boutonDialogue;
    QLabel *statusLabel;


};

#endif

/*
Classe appelée dans le main ouvrant une boite de dialogue avec un message d'acceuil et lancant le serveur
*/

#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets/QDialog>
#include "MySocketServer.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

private:
    QLabel *statusLabel;
    QPushButton *quitButton;

    //
    // CREATION ET LANCEMENT DU SERVEUR RESEAU
    //
    MySocketServer server;
};

#endif

// MaFenetre.cpp

#include "testducul.h"
#include <QString>
#include <QMessageBox>
#include <stdlib.h>
#include <QtNetwork>



testducul::testducul(QWidget *parent)
    : QDialog(parent)
{
    statusLabel = new QLabel;
    setFixedSize(230, 120);
   // QString message = QString::number(count_request_recu);
   // QMessageBox::information(this, "requete recu", "Requetes reçu: "+ message);
    statusLabel->setText(tr("The server is running on port %1.\n"
                            "Use internet navigator now.")
                         .arg(count_request_recu));
}

void testducul::_addrequete()
{
    count_request_recu++;
}

void testducul::ouvrirDialogue()
{
    // Vous insérerez ici le code d'ouverture des boîtes de dialogue
}

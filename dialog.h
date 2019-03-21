#ifndef DIALOG_H
#define DIALOG_H

//objects.h ?  MyFileCache.h ? defintion de void error client. creation 2eme fenetre client dans le dialog
#include <QDialog>
#include "MySocketServer.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr); //utiliser 0 ou NULL pour un int et nullptr pour un pointeur

private:
    QLabel *statusLabel;
    QPushButton *quitButton;

    //
    // CREATION ET LANCEMENT DU SERVEUR RESEAU
    //
    MySocketServer server;
};

#endif

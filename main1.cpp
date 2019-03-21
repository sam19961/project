#include <QApplication>
#include <QtCore>
#include <QMovie>

#include "dialog.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    // ON CREE UNE APPLICATION
    QApplication app(argc, argv);

    // ON CREE UNE BOITE DE DIALOGUE
    Dialog dialog;

    // ON L'AFFICHE...
    dialog.show();
    return dialog.exec();
}

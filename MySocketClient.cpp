#include "MySocketClient.h"

#include <QtNetwork>


MySocketClient::MySocketClient(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}

inline string removeEndLine(string s){              //retire la partie de la ligne après un \r ou un \n
        while( s.at(s.length()-1) == '\r' ||
                        s.at(s.length()-1) == '\n' ){
                s = s.substr(0, s.length()-1);
        }
        return s;
}

void MySocketClient::run()
{
    cout << "Starting MySocketClient::run()" << endl;
    QTcpSocket tcpSocket;

    // ON RECUPERE LE LIEN DE COMMUNICATION AVEC LE CLIENT ET ON QUITTE EN CAS
    // DE PROBLEME...
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    // SI LE CLIENT N'A PAS EU LE TEMPS DE NOUS TRANSMETTRE SA REQUETE,
    // ON SE MET EN ATTENTE PENDANT 1s
    while (tcpSocket.bytesAvailable() < (int)sizeof(quint16)) {
        if (!tcpSocket.waitForReadyRead( 1000 )) {
                cout << "(EE) Erreur de time out !" << endl;
                return;
        }
    }
    char tampon[65536];                                      // LA PREMIERE REQUETE CORRESPOND AU GET NORMALEMENT
    int lineLength = (int)tcpSocket.readLine(tampon, 65536); //(qint64 a la base) ON RECUPERE LA REQUETE ET SA TAILLE
    string ligne( tampon );                                  // ON TRANSFORME LA REQUETE SOUS FORME DE STRING
    ligne = removeEndLine( ligne );
    cout << "COMMANDE : =>" << ligne << "<=" << endl;        // ON AFFICHE LA COMMANDE A L'ECRAN...

   int pos1 = (int)ligne.find(" ");
   string cmde = ligne.substr(0, pos1);                     //substr coupe le string entre 0 et pos2
   ligne = ligne.substr(pos1+1, ligne.length()-pos1);

   cout << "1. : " << cmde  << endl;
   cout << "2. : " << ligne << endl;

   int pos2 = (int)ligne.find(" ");
   string file = ligne.substr(0, pos2);
   ligne = ligne.substr(pos2+1, ligne.length()-pos2);

   cout << "3. : " << file  << endl;
   cout << "4. : '" << ligne << "'" << endl;

        while( tcpSocket.bytesAvailable() > 0 ){
        int lineLength = (int)tcpSocket.readLine(tampon, 65536);
        if (lineLength != -1 &&  lineLength != 0) {
                //cout << "C" << lineLength << " :: " << tampon;
        }else if(lineLength != -1 ){
                cout << "Nothing for the moment !" << endl;
        }
    }

   QString str = tr("./public_html") + tr(file.c_str()); //pk un pointeur sur file avec c_str() ?
   QFile f( str );
   QDir  d( str );

   cout << " - Chemin du fichier : " << str.toStdString() << endl;
   cout << " - isFile :          : " << f.exists() << endl;
   cout << " - isDirectory       : " << d.exists() << endl;

   if( f.exists() == false &&  d.exists() == false ){
       // ERREUR 404 LE FICHIER N'EXISTE PAS...

   }else if( d.exists() == true ){
       // C'EST UN REPERTOIRE !

   }else if( f.exists() == true ){
       QFile* file = new QFile( str );
        if (!file->open(QIODevice::ReadOnly))
        {
                delete file;
                return;
        }
        tcpSocket.write( file->readAll() );
        file->close();

   }else{

   }

//! [2] //! [3]

    /*QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << text;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
//! [3] //! [4]

    tcpSocket.write(block);*/

    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
    cout << "Finishing MySocketClient::run()" << endl;
}
//! [4]

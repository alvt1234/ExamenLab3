#ifndef CTUNES_H
#define CTUNES_H
#include <fstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <qfile.h>
#include <genero.h>
using namespace std;

class ctunes
{
public:
    ctunes();
    int getCodigo(long);
    void addSong(string, string, Genero::Tipo,double,QString);
    void reviewSong(int, int);
    string downloadSong(int , string );
    QString songs(QString);
    string infoSong(int);
    template <typename tipodato>
    void buscarCode(tipodato codigo);
private:
    int codecancion = 1;
    int codedownload = 1;
};


#endif

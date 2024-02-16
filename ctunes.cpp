#include "ctunes.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <stdlib.h>
#include <genero.h>
#include <QDate>
#include <QDebug>

using namespace std;

struct Cancion{
    int code;
    QString nombre;
    QString cantante;
    QString generoCantante;
    double precio;
    int cantEstrellas;
    int reviews;
    QString duracion;
};

struct download
{
    int codedown;
    QString fecha;

    int codesong;
    QString cliente;
    double precio;
};

QFile codigoArchivo("codigo.itn");
QFile downloadArchivo("download.itn");
QFile songsArchivo("song.itn");

QDataStream Leer(&codigoArchivo);
QDataStream Escribir(&codigoArchivo);
QDataStream EscribirCancion(&songsArchivo);
QDataStream LeerCancion(&songsArchivo);
QDataStream writeD(&downloadArchivo);


ctunes::ctunes() {
    codigoArchivo.open(QIODevice::ReadWrite);
    downloadArchivo.open(QIODevice::ReadWrite);
    songsArchivo.open(QIODevice::ReadWrite);

    qint64 size = codigoArchivo.size();
    if(size == 0) {
        int codecancion = 1;
        int codedownload = 1;
        Escribir << codecancion << codedownload;
    }
}

int ctunes::getCodigo(long offset){
   codigoArchivo.open(QIODevice::ReadWrite);
    int code=1,download=1,valor=0;
    Leer>>code>>download;
    if(offset==0){
        valor=code;
        code++;
    }else if(offset==4){
        valor=download;
        download++;
    }
    codigoArchivo.seek(0);
    Escribir<<code<<download;
    codigoArchivo.close();
    return valor;
}
void ctunes::addSong(string nombre,string Cantante, Genero::Tipo generoCantante,double precio,QString duracion){
    songsArchivo.open(QIODevice::ReadWrite);
    getCodigo(0);
    Cancion aggCancion;
    aggCancion.nombre=QString::fromStdString(nombre).toUtf8();
    aggCancion.cantante=QString::fromStdString(Cantante).toUtf8();
    aggCancion.generoCantante= reinterpret_cast<const char*>(&aggCancion.generoCantante), sizeof(int);
    aggCancion.precio=precio;
    aggCancion.cantEstrellas=0;
    aggCancion.reviews=0;
    aggCancion.duracion=duracion;
    songsArchivo.seek(songsArchivo.size());
    EscribirCancion<<aggCancion.nombre<<aggCancion.cantante<<aggCancion.generoCantante<<aggCancion.precio<<aggCancion.cantEstrellas<<aggCancion.reviews<<aggCancion.duracion;
    songsArchivo.flush();
}

void ctunes::reviewSong(int code,int stars){
    if(buscarCode(code)){
    songsArchivo.open(QIODevice::ReadWrite);
    Cancion aggCancion;
    LeerCancion>>aggCancion.nombre>>aggCancion.cantante>>aggCancion.generoCantante>>aggCancion.precio>>aggCancion.cantEstrellas>>aggCancion.reviews>>aggCancion.duracion;
    int stars=aggCancion.cantEstrellas;
    aggCancion.cantEstrellas=stars+1;
    int reviewss=aggCancion.reviews;
    aggCancion.reviews=reviewss+1;
    EscribirCancion<<aggCancion.nombre<<aggCancion.cantante<<aggCancion.generoCantante<<aggCancion.precio<<aggCancion.cantEstrellas<<aggCancion.reviews<<aggCancion.duracion;
    }
}

string ctunes::downloadSong(int codeSong,string cliente){

}

QString ctunes::songs(string txtFile){

}

string ctunes::infoSong(int codeSong){

}

bool ctunes::buscarCode(int codigo){
   codigoArchivo.open(QIODevice::ReadOnly);
   codigoArchivo.seek(0);
   int code,download;
   Leer>>code>>download;
   if(code==codigo){
       return true;
   }
   return false;
}

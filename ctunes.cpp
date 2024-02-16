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
#include <QMessageBox>
#include "invalidrateexception.h"
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
    int codedownload;
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
QDataStream EscribirDown(&downloadArchivo);


ctunes::ctunes() {
    codigoArchivo.open(QIODevice::ReadWrite);
    downloadArchivo.open(QIODevice::ReadWrite);
    songsArchivo.open(QIODevice::ReadWrite);

    qint64 size = codigoArchivo.size();
    if(size == 0) {
        int codecancion = 1;
        int codedownload = 1;
        Escribir << codecancion << codedownload;
    } else {
        Leer >> codecancion >> codedownload;
    }
    codigoArchivo.close();
}

int ctunes::getCodigo(long offset){
    codigoArchivo.open(QIODevice::ReadWrite);
    int code=1,download=0,valor=0;
    Leer>>code>>download;
    if(offset==0){
        valor=code;
        code++;
        codigoArchivo.seek(0);
        Escribir<<code<<download;
    }else if(offset==4){
        valor=download;
        download++;
        codigoArchivo.seek(0);
        Escribir<<code<<download;
    }
    codigoArchivo.close();
    return valor;
}

void ctunes::addSong(string nombre,string Cantante, Genero::Tipo generoCantante,double precio,QString duracion){
    string genero;
    if (generoCantante == Genero::POP) {
        genero = "Pop";
    } else if (generoCantante == Genero::ROCK) {
        genero = "Rock";
    } else if (generoCantante == Genero::RAP) {
        genero = "Rap";
    } else if (generoCantante == Genero::DANCE) {
        genero = "Dance";
    } else if (generoCantante == Genero::REGGAE) {
        genero = "Raggae";
    } else if (generoCantante == Genero::ELECTRONICA) {
        genero = "Electronica";
    } else if (generoCantante == Genero::RANCHERA) {
        genero = "Ranchera";
    }

    songsArchivo.open(QIODevice::ReadWrite);

    Cancion aggCancion;
    aggCancion.code=getCodigo(0);
    aggCancion.nombre=QString::fromStdString(nombre).toUtf8();
    aggCancion.cantante=QString::fromStdString(Cantante).toUtf8();
    aggCancion.generoCantante = QString::fromStdString(genero);
    aggCancion.precio=precio;
    aggCancion.cantEstrellas=0;
    aggCancion.reviews=0;
    aggCancion.duracion=duracion;
    songsArchivo.seek(songsArchivo.size());
    EscribirCancion<<aggCancion.code<<aggCancion.nombre<<aggCancion.cantante<<aggCancion.generoCantante<<aggCancion.precio<<aggCancion.cantEstrellas<<aggCancion.reviews<<aggCancion.duracion;
    songsArchivo.flush();
    QMessageBox::information(nullptr, "Agregar Cancion", "Cancion Agregada Correctamente.");

}

void ctunes::reviewSong(int code, int stars) {

    /*if(stars<0||stars>5){
        throw std::invalid_argument("La cantidad de estrellas debe estar entre 0 y 5.");
    }*/
    int contarreview,estrellas;
        songsArchivo.seek(0);
        Cancion aggCancion;
        while (!songsArchivo.atEnd()) {
            qint64 pos = songsArchivo.pos();
            LeerCancion >> aggCancion.code>> aggCancion.nombre >> aggCancion.cantante >> aggCancion.generoCantante
                >> aggCancion.precio >> aggCancion.cantEstrellas >> aggCancion.reviews
                >> aggCancion.duracion;

            if (aggCancion.code == code) {
                if(stars>=0 && stars<=5){
                contarreview=aggCancion.reviews+1;
                estrellas=aggCancion.cantEstrellas+stars;
                songsArchivo.seek(pos);
                EscribirCancion << aggCancion.code<< aggCancion.nombre << aggCancion.cantante <<aggCancion.generoCantante<<aggCancion.precio << estrellas << contarreview<< aggCancion.duracion;
                songsArchivo.flush();
                QMessageBox::information(nullptr, "Review", "Review.");
                break;
                }else
                    throw InvalidRateException(stars);
            }
        }


}

string ctunes::downloadSong(int codeSong, string cliente) {
    songsArchivo.seek(0);
    Cancion aggCancion;
    while(!songsArchivo.atEnd()){
    LeerCancion >> aggCancion.code >> aggCancion.nombre >> aggCancion.cantante >> aggCancion.generoCantante
        >> aggCancion.precio >> aggCancion.cantEstrellas >> aggCancion.reviews
        >> aggCancion.duracion;
    if (aggCancion.code == codeSong) {
        download descarga;
        descarga.codedownload = getCodigo(4);
        QDate fechainicial = QDate::currentDate();
        descarga.fecha = QDate::currentDate().toString("yyyy-MM-dd");

        // Usar QString para cliente también
        descarga.cliente = QString::fromStdString(cliente);
        descarga.codesong = aggCancion.code;
        downloadArchivo.seek(downloadArchivo.size());
        EscribirDown << descarga.codedownload << descarga.fecha << descarga.codesong << descarga.cliente;
        return "Codigo de descarga: "+to_string(descarga.codedownload)+"\nFecha: "+descarga.fecha.toStdString()+"\nGRACIAS "+descarga.cliente.toStdString() + " Por bajar " + aggCancion.nombre.toStdString()+" a un costo de Lps. "+to_string(aggCancion.precio);

    }
    }
    return "Cancion no encontrada";
}


QString ctunes::songs(QString txtFile) {
    QString line="";
    QFile file(txtFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return "Error al abrir el archivo.";
    }

    file.resize(0);

    songsArchivo.seek(0);
    QTextStream out(&file);
    while (!songsArchivo.atEnd()) {
        Cancion aggCancion;
        LeerCancion >> aggCancion.code >> aggCancion.nombre >> aggCancion.cantante >> aggCancion.generoCantante
            >> aggCancion.precio >> aggCancion.cantEstrellas >> aggCancion.reviews
            >> aggCancion.duracion;

        double rating = aggCancion.reviews != 0 ? static_cast<double>(aggCancion.cantEstrellas) / aggCancion.reviews : 0.0;


        line += " CODIGO – TITULO – CANTANTE – DURACION – PRECIO – RATING\n   "+QString::number(aggCancion.code) + "   -   " + aggCancion.nombre + "   -   " +
                aggCancion.cantante + " - " + aggCancion.duracion + " - " +
                QString::number(aggCancion.precio) + "   -   " + QString::number(rating) + "\n";

    }

    // Cierra el archivo
    out<<line+"\n";
    file.close();

    return line;
}



string ctunes::infoSong(int codeSong) {
    songsArchivo.seek(0);
    while (!songsArchivo.atEnd()) {
        Cancion aggCancion;
        LeerCancion >> aggCancion.code >> aggCancion.nombre >> aggCancion.cantante >> aggCancion.generoCantante
            >> aggCancion.precio >> aggCancion.cantEstrellas >> aggCancion.reviews
            >> aggCancion.duracion;
        if (aggCancion.code == codeSong) {
            string texto;
            double estrellas = static_cast<double>(aggCancion.cantEstrellas);
            double review= static_cast<double>(aggCancion.reviews);
            double rating=estrellas/review;
            texto = "Codigo: " + to_string(aggCancion.code) + "\nCancion: " + aggCancion.nombre.toStdString() + "\nCantante: "
                    + aggCancion.cantante.toStdString() + "\nGenero: " + aggCancion.generoCantante.toStdString() + "\nPrecio: " +
                    to_string(aggCancion.precio) + "\nReviews: " + to_string(aggCancion.reviews) + "\nEstrellas: " +
                    to_string(aggCancion.cantEstrellas)+"\nRating: "+ to_string(rating) + "\nDuracion: " + aggCancion.duracion.toStdString();
            return texto;
        }
    }
    return "Cancion no encontrada";
}




template <class tipodato>
void ctunes::buscarCode(tipodato codigo){
   codigoArchivo.open(QIODevice::ReadOnly);
   codigoArchivo.seek(0);
   int code,download;
   Leer>>code>>download;
   if(code==codigo){
       return;
   }

}

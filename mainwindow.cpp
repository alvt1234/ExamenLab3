#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ctunes.h"
#include "genero.h"
#include <QTimeEdit>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_pressed()
{
    ui->Stack->setCurrentIndex(1);
}

void MainWindow::on_pushButton_6_pressed()
{
    ui->Stack->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_pressed()
{
    ui->Stack->setCurrentIndex(2);
}
void MainWindow::on_pushButton_3_pressed()
{
     ui->Stack->setCurrentIndex(3);
}

void MainWindow::on_pushButton_4_pressed()
{
     ui->Stack->setCurrentIndex(4);
}
void MainWindow::on_pushButton_5_pressed()
{
     ui->Stack->setCurrentIndex(5);
}

void MainWindow::on_pushButton_8_pressed()
{
    ui->Stack->setCurrentIndex(0);
}

void MainWindow::on_pushButton_10_pressed()
{
    ui->Stack->setCurrentIndex(0);
}

void MainWindow::on_pushButton_12_pressed()
{
    ui->Stack->setCurrentIndex(0);

}

void MainWindow::on_pushButton_15_pressed()
{
    ui->Stack->setCurrentIndex(0);

}


void MainWindow::on_btSongsVolver_pressed()
{
   ui->Stack->setCurrentIndex(0);
}


void MainWindow::on_btAgregarAdd_pressed()
{
    ctunes principal;
    Genero::Tipo Enumeracion;
    QString nombre=ui->txtnombreAdd->text();
    string name=nombre.toStdString();
    QString cantante=ui->txtcantanteAdd->text();
    string namecantante=cantante.toStdString();
    double precio=ui->txtprecioAdd->text().toDouble();
    QString genero=ui->cbGeneroAdd->currentText();
    string gen2=genero.toStdString();
    QTime tiempo = ui->timeEdit->time();
    QString timeString = tiempo.toString("mm:ss");
    if(!ui->txtnombreAdd->text().isEmpty() && !ui->txtcantanteAdd->text().isEmpty() && !ui->txtprecioAdd->text().isEmpty())
        if (genero == "Pop") {
            Enumeracion = Genero::POP;
        } else if (genero == "Rock") {
            Enumeracion = Genero::ROCK;
        } else if (genero == "Rap") {
            Enumeracion = Genero::RAP;
        } else if (genero == "Dance") {
            Enumeracion = Genero::DANCE;
        } else if (genero == "Reggae") {
            Enumeracion = Genero::REGGAE;
        } else if (genero == "Electronica") {
            Enumeracion = Genero::ELECTRONICA;
        } else if (genero == "Ranchera") {
            Enumeracion = Genero::RANCHERA;
        }
        principal.addSong(name,namecantante,Enumeracion,precio,timeString);
}


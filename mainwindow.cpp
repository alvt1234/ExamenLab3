#include "mainwindow.h"
#include "ui_mainwindow.h"

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


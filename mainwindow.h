#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();

    void on_pushButton_6_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_pushButton_8_pressed();

    void on_pushButton_10_pressed();

    void on_pushButton_12_pressed();

    void on_pushButton_15_pressed();

    void on_btSongsVolver_pressed();

    void on_btAgregarAdd_pressed();

    void on_pushButton_14_pressed();

    void on_pushButton_11_pressed();

    void on_pushButton_7_pressed();

    void on_pushButton_13_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

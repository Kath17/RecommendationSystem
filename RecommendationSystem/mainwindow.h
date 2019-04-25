#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    int k;
    QString nombre1;
    QString nombre2;
    QString item;
    float umbral;

    QString opcion = "K-vecinos más cercanos";
    QString distancia = "manhattan";
};

#endif // MAINWINDOW_H

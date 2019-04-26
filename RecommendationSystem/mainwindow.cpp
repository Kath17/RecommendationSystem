#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recommender.cpp"
#include <QStandardItem>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    k = ui->spinBox->value();
    nombre1 = ui->lineEdit_2->text();
    nombre2 = ui->lineEdit_3->text();
    item = ui->lineEdit_4->text();
    umbral = ui->doubleSpinBox->value();

    string nombre_1 = nombre1.toStdString();
    string nombre_2 = nombre2.toStdString();
    string item_ = item.toStdString();

    // ----------------------__TABLA__-----------------------//
    QStandardItemModel *mod = new QStandardItemModel;
    QStandardItem *it = new QStandardItem(QObject::tr("Vecino"));
    mod->setHorizontalHeaderItem(0,it);
    QStandardItem *it1 = new QStandardItem(QObject::tr("Distancia"));
    mod->setHorizontalHeaderItem(1,it1);
    QStandardItem *it2 = new QStandardItem(QObject::tr("Pelicula"));
    mod->setHorizontalHeaderItem(2,it2);
    QStandardItem *it3 = new QStandardItem(QObject::tr("Puntaje"));
    mod->setHorizontalHeaderItem(3,it3);

    //and so on
    ui->tableView->setModel(mod);

    // Llenar tabla
    QStandardItem *item1;
    QStandardItem *item2;
//    mod->setItem(0,0,item1); // 0,0 is row/colum.
//    mod->setItem(0,1,item1);
//    ui->tableView->show();

    RecomenderSystem RS;
    RS.load_data("/home/crhistian/Documents/semestreIX/TBD/SystemRecommendation/RecommendationSystem/BD/MovieRatings.csv",';');
//    RS.load_data("/home/kat/Documentos/TBD-Recommendation-System/Interfaz/RecommendationSystem/BD/BDLibro.csv",';');
//    RS.load_data("/home/kat/Documentos/TBD-Recommendation-System/Interfaz/RecommendationSystem/BD/BDLibros.csv",';');
//    RS.load_data("/home/kat/Documentos/TBD-Recommendation-System/Interfaz/RecommendationSystem/BD/BDMovieLens.csv",',');

    if(opcion=="K-vecinos más cercanos"){
        vector<tuple<float,string>> Vecinos = RS.vecino_cercano(nombre_1,k,distancia.toStdString());
//        print_vector(Vecinos);
        for(int i=0; i<Vecinos.size(); i++)
        {
            item1 = new QStandardItem(QString::fromStdString(get<1>(Vecinos[i])));
            item2 = new QStandardItem(QString::number(get<0>(Vecinos[i])));
            mod->setItem(i,0,item1);
            mod->setItem(i,1,item2);
            ui->tableView->show();
        }
     }

     else if(opcion == "Recomendar películas")
    {
       vector <tuple<float,string,int>> rec = RS.RecomendarPorKUsuarios(nombre_1,distancia.toStdString(),k,umbral);
       print_vector(rec);
       for(int i=0; i<rec.size(); i++)
       {
           item1 = new QStandardItem(QString::fromStdString(get<1>(rec[i])));
           item2 = new QStandardItem(QString::number(get<0>(rec[i])));
           mod->setItem(i,2,item1);
           mod->setItem(i,3,item2);
           ui->tableView->show();
       }
    }

    else if(opcion == "Hallar puntaje aprox.")
    {
        float res = RS.prob_movie(nombre_1,item_,k,distancia.toStdString());
//        QString a = QString::number(res);
        if(res == 0)
        {
            ui->lineEdit_5->setText("El usuario ya vio la película y la calificó con: "+QString::number(RS.data[nombre_1][item_]));
        }
        else {
            ui->lineEdit_5->setText("El puntaje aproximado de "+nombre1+" al item: "+item+" es: "+ QString::number(res));
        }
    }

    else if(opcion=="Comparar dos usuarios")
    {
        float res;
        if(distancia == "Manhattan")
        {
            res = RS.manhattan(nombre_1,nombre_2);
        }
        else if(distancia == "Euclidean")
        {
            res = RS.euclidean(nombre_1,nombre_2);
        }
        else if(distancia == "Pearson")
        {
            res = RS.pearson(nombre_1,nombre_2);
        }
        else if(distancia == "Similitud del Coseno")
        {
            res = RS.sim_coseno(nombre_1,nombre_2);
        }
        ui->lineEdit_5->setText("La distancia de "+distancia+" es: "+QString::number(res));
    }

//    QString s = QString::number(i);

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "K-vecinos más cercanos")
    {
        opcion = "K-vecinos más cercanos";
    }
    else if(arg1 == "Recomendar películas")
    {
        opcion = "Recomendar películas";
    }
    else if(arg1 == "Hallar puntaje aprox.")
    {
        opcion = "Hallar puntaje aprox.";
    }
    else if(arg1 == "Comparar dos usuarios")
    {
        opcion = "Comparar dos usuarios";
    }
}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{
    distancia = arg1;
//    if(arg1 == "Manhattan")
//    {
//        distancia = "manhattan";
//    }
//    else if(arg1 == "Euclidean")
//    {
//        distancia = "euclidean";
//    }
//    else if(arg1 == "Pearson")
//    {
//        distancia = "pearson";
//      comentario prueba para hacer commit
//    }
//    else if(arg1 == "Similitud del Coseno")
//    {
//        distancia = "sim_coseno";
//    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{

}

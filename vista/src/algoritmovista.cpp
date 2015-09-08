#include "algoritmovista.h"
#include "ui_algoritmovista.h"

AlgoritmoVista::AlgoritmoVista(Matrix *matriz, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgoritmoVista)
{
    ui->setupUi(this);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                         this->size(),
                                         qApp->desktop()->availableGeometry()));
    this->matriz = matriz;
}

AlgoritmoVista::~AlgoritmoVista()
{
    delete ui;
}

void AlgoritmoVista::on_eucli_clicked()
{
    if(!ui->eucli->isChecked()){
        ui->maha->setChecked(false);
        ui->diagonal->setChecked(false);
    }
}

void AlgoritmoVista::on_diagonal_clicked()
{
    if(!ui->diagonal->isChecked()){
        ui->maha->setChecked(false);
        ui->eucli->setChecked(false);
    }
}

void AlgoritmoVista::on_maha_clicked()
{
    if(!ui->maha->isChecked()){
        ui->eucli->setChecked(false);
        ui->diagonal->setChecked(false);
    }
}

void AlgoritmoVista::on_clasificarBoton_clicked()
{

    fuzzines = ui->fuzzyExponent->text().toFloat();

    cluster = ui->maxZones->text().toInt() - ui->minZones->text().toInt();

    epsilon = ui->convergenceCriteria->text().toFloat();

    Matrix B = boost::numeric::ublas::trans(*this->matriz);


    for (int i = ui->minZones->text().toInt();
         i <= ui->maxZones->text().toInt(); i ++){
            qDebug() << "cluster: " << i;
            Fuzzy f(B, i, fuzzines, epsilon);
            f.clustering();
    }
}

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

    Matrix B = boost::numeric::ublas::trans(*this->matriz); // Transpuesta

    ks.resize(ui->maxZones->text().toInt() - ui->minZones->text().toInt() + 1,
              this->matriz->size2()+1); // Para incluir las columnas

    for (int i = ui->minZones->text().toInt(), a = 0;
         i <= ui->maxZones->text().toInt(); i ++ , a++)
    {
        qDebug() << "cluster: " << i;
        ks.insert_element(a,0,i);
        Fuzzy f(B, i, fuzzines, epsilon);
        f.clustering();
        f.clusterClassification(&ks,a);
    }

    for(int j = 0; j < ks.size2();j++)
    {
        for(int i = 0 ; i <= ui->maxZones->text().toInt() -
            ui->minZones->text().toInt(); i++)
        {
            std::cout << ks.at_element(i,j) << " ";
        }
        std::cout << std::endl;

    }
}

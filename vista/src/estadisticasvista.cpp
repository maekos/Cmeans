#include "estadisticasvista.h"
#include "ui_vistaestadisticas.h"

#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

EstadisticasVista::EstadisticasVista(CsvData *data, QWidget *parent) :
    QWidget(parent),
    av(),
    ui(new Ui::VistaEstadisticas)
{
    ui->setupUi(this);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                          this->size(),
                                          qApp->desktop()->availableGeometry()));
    this->data = data;
}

EstadisticasVista::~EstadisticasVista()
{
    delete ui;
}

void EstadisticasVista::inputFile(const QString file)
{
    ui->inputText->setText(file);
}

void EstadisticasVista::mostrarVistaEstadistica(QStringList selectedVectors)
{
    this->ui->plainTextEdit->insertPlainText("Estadisticas");

    this->show();

    this->matriz.resize(selectedVectors.size(),this->data->getDataAt(0).size());

    /* Lleno la matriz con los elementos seleccionados */
    for(int col = 0; col < selectedVectors.size(); col++){
        int i = 0;
        foreach(const QString num, data->getDataFrom(selectedVectors.at(0))){
            this->matriz.insert_element(col, i, num.toFloat());
            i++;
        }
    }
}

void EstadisticasVista::on_nextButton_clicked()
{
    this->hide();
    av.show();
}


void EstadisticasVista::on_estadisticasBoton_clicked()
{
    //Vector v;
    //boost::numeric::ublas::column(matriz,0) = v;
}

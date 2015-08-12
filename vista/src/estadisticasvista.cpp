#include "estadisticasvista.h"
#include "ui_vistaestadisticas.h"
#include <stdio.h>
#include <stdlib.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
EstadisticasVista::EstadisticasVista(CsvData *data, QWidget *parent) :
    QWidget(parent),
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

void EstadisticasVista::mostrarVistaEstadistica(QStringList selectedVectors)
{
    this->show();

    matriz.resize(selectedVectors.size(),this->data->getDataAt(0).size());

    for(int col = 0; col < selectedVectors.size(); col++){
        int i = 0;
        foreach(const QString num, data->getDataFrom(selectedVectors.at(0))){
            matriz.insert_element(col, i, num.toFloat());
            i++;
        }
    }
    using namespace boost::numeric::ublas;
    std::cout << "Matriz de datos" << std::endl
      << " " << (matriz) << std::endl;
}

void EstadisticasVista::on_nextButton_clicked()
{
    this->hide();
    emit cambiarVistaAlgortimo();
}

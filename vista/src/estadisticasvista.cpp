#include "estadisticasvista.h"
#include "ui_vistaestadisticas.h"

EstadisticasVista::EstadisticasVista(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VistaEstadisticas)
{
    ui->setupUi(this);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                          this->size(),
                                          qApp->desktop()->availableGeometry()));
}

EstadisticasVista::~EstadisticasVista()
{
    delete ui;
}

void EstadisticasVista::mostrarVistaEstadistica(QStringList selectedVectors)
{
    this->show();

}

void EstadisticasVista::on_nextButton_clicked()
{
    this->hide();
    emit cambiarVistaAlgortimo();
}

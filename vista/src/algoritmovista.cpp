#include "algoritmovista.h"
#include "ui_algoritmovista.h"

AlgoritmoVista::AlgoritmoVista(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgoritmoVista)
{
    ui->setupUi(this);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                         this->size(),
                                         qApp->desktop()->availableGeometry()));
}

AlgoritmoVista::~AlgoritmoVista()
{
    delete ui;
}

#include "estadisticasvista.h"
#include "ui_vistaestadisticas.h"

#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

/**
 * @brief EstadisticasVista::EstadisticasVista
 *
 * COnstructor por defecto de la clase.
 *
 * @param data Archivo de datos a procesar
 */
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

/**
 * @brief EstadisticasVista::~EstadisticasVista
 *
 * Destructor.
 *
 */
EstadisticasVista::~EstadisticasVista()
{
    delete ui;
}

/**
 * @brief EstadisticasVista::inputFile
 *
 * Coloca en el linebox la ruta al archivo que se le estan ejecutando las
 * operaciones.
 *
 * @param file Ruta al archivo de datos.
 */
void EstadisticasVista::inputFile(const QString file)
{
    ui->inputText->setText(file);
}

/**
 * @brief EstadisticasVista::mostrarVistaEstadistica
 *
 * Muestra la ventana en donde a su vez se muestran los resultados estadisticos
 * realizados sobre las variables previamente elegidas.
 *
 * @param selectedVectors Variable con el conjunto de datos elegidos.
 *
 */
void EstadisticasVista::mostrarVistaEstadistica(QStringList selectedVectors)
{
    this->columns = selectedVectors;
    this->show();

    this->matriz.resize(selectedVectors.size(),this->data->getDataAt(0).size());

    /* Lleno la matriz con los elementos seleccionados */
    for(int col = 0; col < selectedVectors.size(); col++){
        int i = 0;
        foreach(const QString num, data->getDataFrom(selectedVectors.at(col))){
            this->matriz.insert_element(col, i, num.toFloat());
            i++;
        }
    }
}


/**
 * @brief EstadisticasVista::on_nextButton_clicked
 *
 * Pasa a la vista de algortimo
 *
 */
void EstadisticasVista::on_nextButton_clicked()
{
    this->hide();
    av.show();
}

/**
 * @brief EstadisticasVista::on_estadisticasBoton_clicked
 *
 * Muestra las estadisticas del conjunto de datos seleccionado previamente.
 *
 */
void EstadisticasVista::on_estadisticasBoton_clicked()
{
    this->ui->plainTextEdit->clear();
    Stats *sta[100]; // Cuidado de no elegir mas de 100 variables.

    this->ui->plainTextEdit->insertPlainText("Estadisticas\n");
    this->ui->plainTextEdit->insertPlainText("Numero de Variables: " +
                                             QString::number(matriz.size1()));
    this->ui->plainTextEdit->insertPlainText("\nNumero de observaciones: " +
                                             QString::number(matriz.size2()) +
                                             "\n\n");

/******************************************************************************/
    // Calculo de estadisticas
    for(int i = 0; i< matriz.size1();i++)
    {
        Vector v;
        v = boost::numeric::ublas::row(matriz,i);
        sta[i]  = new Stats(&v);
    }

    // Matriz de covarianza y coeficiente de correlacion
    Matrix covar, cc;
    covar.resize(matriz.size1(),matriz.size1());
    cc.resize(matriz.size1(),matriz.size1());
    Vector v1, v2;
    for(int i = 0; i< matriz.size1(); i++){        
        v1 = boost::numeric::ublas::row(matriz,i);
        float stdV1 = Stats::desviacionEstandar(&v1);
        for(int j = i; j < matriz.size1(); j++)
        {
            v2 = boost::numeric::ublas::row(matriz,j);
            float stdV2 = Stats::desviacionEstandar(&v2);
            float cv = Stats::Covarianza(&v1,&v2);
            cc.insert_element(i,j,cv/(stdV1*stdV2));
            cc.insert_element(j,i,cv/(stdV1*stdV2));
            covar.insert_element(i,j,cv);
            covar.insert_element(j,i,cv);
        }
    }

/******************************************************************************/
    this->ui->plainTextEdit->insertPlainText("Mean\n");
    foreach(const QString col, this->columns)
    {
        this->ui->plainTextEdit->insertPlainText(col + "\t\t");
    }
    this->ui->plainTextEdit->insertPlainText("\n");
    for(int i = 0; i< matriz.size1();i++)
    {        
        this->ui->plainTextEdit->
                insertPlainText(
                    QString::number(sta[i]->getMedia()) + "\t\t");
    }
/******************************************************************************/
    this->ui->plainTextEdit->insertPlainText("\n\nStandar Deviation\n");
    foreach(const QString col, this->columns)
    {
        this->ui->plainTextEdit->insertPlainText(col + "\t\t");
    }
    this->ui->plainTextEdit->insertPlainText("\n");
    for(int i = 0; i< matriz.size1();i++)
    {
        this->ui->plainTextEdit->
                insertPlainText(
                    QString::number(sta[i]->getDesviacionEstandar()) + "\t\t");
    }
/******************************************************************************/
    this->ui->plainTextEdit->insertPlainText("\n\nCoefficient of variation (%)\n");
    foreach(const QString col, this->columns)
    {
        this->ui->plainTextEdit->insertPlainText(col + "\t\t");
    }
    this->ui->plainTextEdit->insertPlainText("\n");
    for(int i = 0; i< matriz.size1();i++)
    {
        this->ui->plainTextEdit->
                insertPlainText(
                    QString::number(
                        sta[i]->getDesviacionEstandar() / sta[i]->getMedia() *
                        100) + "\t\t");
    }
/******************************************************************************/
    this->ui->plainTextEdit->insertPlainText("\n\nMinimum values\n");
    foreach(const QString col, this->columns)
    {
        this->ui->plainTextEdit->insertPlainText(col + "\t\t");
    }
    this->ui->plainTextEdit->insertPlainText("\n");
    for(int i = 0; i< matriz.size1();i++)
    {
        this->ui->plainTextEdit->
                insertPlainText(
                    QString::number(sta[i]->getMinNumber()) + "\t\t");
    }
/******************************************************************************/
    this->ui->plainTextEdit->insertPlainText("\n\nMaximum values\n");
    foreach(const QString col, this->columns)
    {
        this->ui->plainTextEdit->insertPlainText(col + "\t\t");
    }
    this->ui->plainTextEdit->insertPlainText("\n");
    for(int i = 0; i< matriz.size1();i++)
    {
        this->ui->plainTextEdit->
                insertPlainText(
                    QString::number(sta[i]->getMaxNumber()) + "\t\t");
    }
/******************************************************************************/
    this->ui->plainTextEdit->insertPlainText("\n\nSum of squares\n");
    foreach(const QString col, this->columns)
    {
        this->ui->plainTextEdit->insertPlainText(col + "\t\t");
    }
    this->ui->plainTextEdit->insertPlainText("\n");
    for(int i = 0; i< matriz.size1();i++)
    {
        this->ui->plainTextEdit->
                insertPlainText(
                    QString::number(sta[i]->getSumaCuadrados()) + "\t\t");
    }
/******************************************************************************/
    this->ui->plainTextEdit->insertPlainText("\n\nVariance-Covariance Matrix\n");
    foreach(const QString col, this->columns)
    {
        this->ui->plainTextEdit->insertPlainText("\t"+ col + "\t");
    }
    this->ui->plainTextEdit->insertPlainText("\n");

    for(int i = 0; i < matriz.size1(); i++){
        this->ui->plainTextEdit->insertPlainText(this->columns.at(i) + "\t");
        for(int j = 0; j < matriz.size1(); j++)
        {
            this->ui->plainTextEdit->insertPlainText(
                                    QString::number(covar.at_element(i,j),'f',3)
                                                     + "\t\t");
        }
        this->ui->plainTextEdit->insertPlainText("\n");
    }
/******************************************************************************/
    this->ui->plainTextEdit->insertPlainText("\nCorrelation Matrix\n");
    foreach(const QString col, this->columns)
    {
        this->ui->plainTextEdit->insertPlainText("\t" + col + "\t");
    }
    this->ui->plainTextEdit->insertPlainText("\n");
    for(int i = 0; i < matriz.size1(); i++){
        this->ui->plainTextEdit->insertPlainText(this->columns.at(i) + "\t");
        for(int j = 0; j < matriz.size1(); j++)
        {
            this->ui->plainTextEdit->insertPlainText(
                                    QString::number(cc.at_element(i,j),'f',3)
                                                     + "\t\t");
        }
        this->ui->plainTextEdit->insertPlainText("\n");
    }
/******************************************************************************/
}

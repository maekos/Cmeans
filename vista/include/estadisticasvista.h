#ifndef VISTAESTADISTICAS_H
#define VISTAESTADISTICAS_H

#include <QWidget>
#include <QDesktopWidget>
#include <QString>
#include <QStringList>
#include <QDebug>

#include "fuzzy_clustering.hpp"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include "csvdata.h"
#include "algoritmovista.h"

typedef double Value;
typedef boost::numeric::ublas::matrix<Value> Matrix;
typedef boost::numeric::ublas::vector<Value> Vector;

namespace Ui {
class VistaEstadisticas;
}

class EstadisticasVista : public QWidget
{
    Q_OBJECT

public:
    explicit EstadisticasVista(CsvData *data, QWidget *parent = 0);
    ~EstadisticasVista();

    void inputFile(const QString file);

public slots:
    void mostrarVistaEstadistica(QStringList selectedVectors);

signals:
    void cambiarVistaAlgortimo();

private slots:
    void on_nextButton_clicked();

    void on_estadisticasBoton_clicked();

private:
    Ui::VistaEstadisticas *ui;

    QStringList columns;

    CsvData *data;

    Matrix matriz;

    AlgoritmoVista av;
};

#endif // VISTAESTADISTICAS_H

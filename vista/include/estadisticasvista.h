#ifndef VISTAESTADISTICAS_H
#define VISTAESTADISTICAS_H

#include <QWidget>
#include <QDesktopWidget>
#include <QString>
#include <QStringList>
#include <QDebug>

#include <boost/numeric/ublas/matrix.hpp>
#include "csvdata.h"

typedef float Value;
typedef boost::numeric::ublas::matrix<Value> Matrix;

namespace Ui {
class VistaEstadisticas;
}

class EstadisticasVista : public QWidget
{
    Q_OBJECT

public:
    explicit EstadisticasVista(CsvData *data, QWidget *parent = 0);
    ~EstadisticasVista();

public slots:
    void mostrarVistaEstadistica(QStringList selectedVectors);

signals:
    void cambiarVistaAlgortimo();

private slots:
    void on_nextButton_clicked();

private:
    Ui::VistaEstadisticas *ui;

    CsvData *data;

    Matrix matriz;
};

#endif // VISTAESTADISTICAS_H

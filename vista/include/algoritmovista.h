#ifndef ALGORITMOVISTA_H
#define ALGORITMOVISTA_H

#include <QWidget>
#include <QDesktopWidget>

#include "fuzzy_clustering.hpp"
#include "csvdata.h"

using namespace Clustering;

namespace Ui {
class AlgoritmoVista;
}

class AlgoritmoVista : public QWidget
{
    Q_OBJECT

public:
    explicit AlgoritmoVista(Matrix *matriz, CsvData *data, QWidget *parent = 0);
    ~AlgoritmoVista();

private slots:
    void on_eucli_clicked();

    void on_diagonal_clicked();

    void on_maha_clicked();

    void on_clasificarBoton_clicked();

private:
    Ui::AlgoritmoVista *ui;

    CsvData *data;

    int cluster;

    float fuzzines;

    float epsilon;

    Matrix *matriz;

    Matrix ks; // Guarda la clasificacion de las muestras de acuerdo a las zonas
};

#endif // ALGORITMOVISTA_H

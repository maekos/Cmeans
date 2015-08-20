#ifndef ALGORITMOVISTA_H
#define ALGORITMOVISTA_H

#include <QWidget>
#include <QDesktopWidget>

#include "fuzzy_clustering.hpp"

using namespace Clustering;

namespace Ui {
class AlgoritmoVista;
}

class AlgoritmoVista : public QWidget
{
    Q_OBJECT

public:
    explicit AlgoritmoVista(Matrix *matriz, QWidget *parent = 0);
    ~AlgoritmoVista();

private slots:
    void on_eucli_clicked();

    void on_diagonal_clicked();

    void on_maha_clicked();

    void on_clasificarBoton_clicked();

private:
    Ui::AlgoritmoVista *ui;

    int cluster;

    float fuzzines;

    float epsilon;

    Matrix *matriz;
};

#endif // ALGORITMOVISTA_H

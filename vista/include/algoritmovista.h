#ifndef ALGORITMOVISTA_H
#define ALGORITMOVISTA_H

#include <QWidget>
#include <QDesktopWidget>

namespace Ui {
class AlgoritmoVista;
}

class AlgoritmoVista : public QWidget
{
    Q_OBJECT

public:
    explicit AlgoritmoVista(QWidget *parent = 0);
    ~AlgoritmoVista();

private:
    Ui::AlgoritmoVista *ui;
};

#endif // ALGORITMOVISTA_H

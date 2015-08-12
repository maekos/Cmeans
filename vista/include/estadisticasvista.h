#ifndef VISTAESTADISTICAS_H
#define VISTAESTADISTICAS_H

#include <QWidget>
#include <QDesktopWidget>

namespace Ui {
class VistaEstadisticas;
}

class EstadisticasVista : public QWidget
{
    Q_OBJECT

public:
    explicit EstadisticasVista(QWidget *parent = 0);
    ~EstadisticasVista();

public slots:
    void mostrarVistaEstadistica(QStringList selectedVectors);

signals:
    void cambiarVistaAlgortimo();

private slots:
    void on_nextButton_clicked();

private:
    Ui::VistaEstadisticas *ui;
};

#endif // VISTAESTADISTICAS_H

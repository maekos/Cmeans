#include "mainwindow.h"
#include "estadisticasvista.h"
#include "algoritmovista.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QStringList>

#include <QDesktopWidget>


using namespace Clustering;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    EstadisticasVista ev;
    AlgoritmoVista av;


    QObject::connect(&mw, SIGNAL(cambiarVistaEstadisticas()),
                     &ev, SLOT(show()));
    QObject::connect(&ev, SIGNAL(cambiarVistaAlgortimo()),
                     &av, SLOT(show()));

    mw.show();
    //CsvData csv("lote.csv");

    return a.exec();

}

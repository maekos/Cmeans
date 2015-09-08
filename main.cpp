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

    //QObject::connect(&ev, SIGNAL(cambiarVistaAlgortimo()),
    //                 &av, SLOT(show()));

    mw.show();
    return a.exec();

}

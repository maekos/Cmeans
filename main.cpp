#include "fuzzy_clustering.hpp"
#include "stats.h"
#include "csvdata.h"
#include "mainwindow.h"

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
    MainWindow w;
    w.show();
    //CsvData csv("lote.csv");

    return a.exec();

}

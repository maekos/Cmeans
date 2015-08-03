#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tableHeader = new QHeaderView(Qt::Horizontal);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                          this->size(),qApp->desktop()->availableGeometry()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile_clicked()
{

    QString fileName;
    QStringList columnNames;
    QStringList datos;

    int columnSize;
    int rowSize;

    fileName = QFileDialog::getOpenFileName(this,tr("Open file"), "./",
                                            tr("Csv Files (*.csv)"));
    data = new CsvData(fileName);

    columnNames = data->getColumnNames();

    columnSize = columnNames.size();
    datos = data->getColumnData(0);
    rowSize = datos.size()-1;

    ui->filePath->setText(fileName);
    ui->tableWidget->setColumnCount(columnSize); // coloco columnas
    ui->tableWidget->setRowCount(rowSize);  // coloco filas

    ui->tableWidget->setHorizontalHeaderLabels(columnNames); //coloco nombre a columnas
    tableHeader = ui->tableWidget->horizontalHeader();
    tableHeader->setStretchLastSection(true);

    QObject::connect(tableHeader,SIGNAL(sectionClicked(int)),
                     this, SLOT(on_section_Clicked(int)));

    // Relleno la tabla con los datos
    for(int i = 0; i < columnSize; i++)
    {
        datos = data->getColumnData(i);

        for(int j = 0; j < rowSize; j++)
        {
            ui->tableWidget->setItem(j,i,new QTableWidgetItem(datos.at(j+1)));
        }

    }
}

void MainWindow::on_section_Clicked(int section)
{
    Vector v;
    bool ok = false;
    QStringList stData;

    stData = data->getColumnData(section); // Guardo los datos de la columna.

    v.resize(stData.size()-1); // Asigno memoria al nuevo vector de datos.

    /*--------- Comienzo la conversion de string a double --------------------*/
    QStringListIterator it(stData); // Recorro la lista de strings
    it.next(); // Salteo el titulo
    int i = 0;
    while(it.hasNext())
    {
        v(i) = it.next().toDouble(&ok);
        i++;
    }

    Stats statics(&v);
    ui->mediaLabel->setText(QString::number(statics.getMedia()));
    ui->varLabel->setText(QString::number(statics.getVarianza()));
    ui->minLabel->setText(QString::number(statics.getMinNumber()));
    ui->maxlabel->setText(QString::number(statics.getMaxNumber()));
    ui->covarLabel->setText(QString::number(statics.getCovarianza()));
    ui->squareSum->setText(QString::number(statics.getSumaCuadrados()));
}

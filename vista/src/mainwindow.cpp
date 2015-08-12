
#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                          this->size(),
                                          qApp->desktop()->availableGeometry()));
    this->selectedItemRow = 0;

    this->horizontalAval = ui->avalvars->horizontalHeader();
    this->verticalAval = ui->avalvars->verticalHeader();
    this->horizontalSel = ui->selvars->horizontalHeader();
    this->verticalSel = ui->selvars->verticalHeader();

    this->horizontalAval->hide();
    this->verticalAval->hide();

    this->horizontalSel->hide();
    this->verticalSel->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile_clicked()
{

    QString fileName;
    QStringList columnNames;

    horizontalAval->setStretchLastSection(true);
    horizontalSel->setStretchLastSection(true);

    int columnSize;

    fileName = QFileDialog::getOpenFileName(this,tr("Open file"), "./",
                                            tr("Csv Files (*.csv)"));
    data = new CsvData(fileName);

    columnNames = data->getColumnNames();

    columnSize = columnNames.size();

    ui->filePath->setText(fileName);

    ui->numberOfFields->setText(QString::number(columnSize));

    ui->avalvars->setColumnCount(1); // coloco columnas
    ui->selvars->setColumnCount(1); // coloco columnas
    ui->avalvars->setRowCount(columnSize);  // coloco filas

    for(int i = 0; i < columnSize; i++)
        ui->avalvars->setItem(i,0, new QTableWidgetItem(columnNames.at(i)));
}

void MainWindow::on_nextButton_clicked()
{
    if(ui->selvars->rowCount() > 0){
        this->hide();
        QStringList list;
        for(int i = 0; i < ui->selvars->rowCount(); i++){
            qDebug() << ui->selvars->item(i,0)->text();
            list.append(ui->selvars->item(i,0)->text());
         }
         emit cambiarVistaEstadisticas(list);
    }else
    {
        qDebug()<< "No selecciono items para procesar.";
    }

}

void MainWindow::on_addVariableButton_clicked()
{
    if(ui->avalvars->selectedItems().size() < 2 &&
            ui->avalvars->selectedItems().size() > 0)
    {
        int row = ui->selvars->rowCount();
        if(row >= 0)
        {
            ui->selvars->insertRow(row);
            ui->selvars->setItem(row,0,
                 new QTableWidgetItem(ui->avalvars->currentItem()->text()));
        }
    }
    else
    {
        qDebug()<< "Debe seleccionar solo un item";
    }
}

void MainWindow::on_delVariableButton_clicked()
{
    if(ui->selvars->selectedItems().size() < 2 &&
            ui->selvars->selectedItems().size() > 0 )
        ui->selvars->removeRow(ui->selvars->currentItem()->row());
    else
        qDebug() << "Debe seleccionar solo un item para eliminar.";
}

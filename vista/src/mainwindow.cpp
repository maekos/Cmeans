
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

    horizontalAval = ui->avalvars->horizontalHeader();
    verticalAval = ui->avalvars->verticalHeader();
    horizontalSel = ui->selvars->horizontalHeader();
    verticalSel = ui->selvars->verticalHeader();

    horizontalAval->hide();
    verticalAval->hide();

    horizontalSel->hide();
    verticalSel->hide();
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
    this->hide();
    emit cambiarVistaEstadisticas();

}

void MainWindow::on_addVariableButton_clicked()
{
    this->selectedItemRow++;
    ui->selvars->insertRow(this->selectedItemRow-1);
    ui->selvars->setRowCount(this->selectedItemRow);
    ui->selvars->setItem(this->selectedItemRow-1,0,
                         new QTableWidgetItem(ui->avalvars->currentItem()->text()));
}

void MainWindow::on_delVariableButton_clicked()
{

    this->selectedItemRow--;
    ui->selvars->removeRow(ui->avalvars->currentItem()->row());
}

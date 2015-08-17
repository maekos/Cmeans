
#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>

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

/**
 * @brief MainWindow::on_openFile_clicked
 * Al presionar el boton se abre un cuadro de dialogo para seleccion de un
 * archivo .csv que permite el procesamiento de los datos.
 */
void MainWindow::on_openFile_clicked()
{
    QStringList columnNames;

    /* ajusto las columnas al ancho de la tabla */
    horizontalAval->setStretchLastSection(true);
    horizontalSel->setStretchLastSection(true);

    int columnSize;

    fileName = QFileDialog::getOpenFileName(this,tr("Open file"), "./",
                                            tr("Csv Files (*.csv)"));
    this->data = new CsvData(fileName);
    this->ev = new EstadisticasVista(this->data);

    columnNames = this->data->getColumnNames();

    columnSize = columnNames.size();

    ui->filePath->setText(fileName);

    ui->numberOfFields->setText(QString::number(columnSize));

    /* Armo las tablas */
    ui->avalvars->setColumnCount(1); // Coloco columnas para las variables
                                     // disponibles
    ui->avalvars->setRowCount(columnSize);  // Coloco filas del tamano de las
                                            // variables.

    ui->selvars->setColumnCount(1); // coloco columnas

    /* Inserto las variables seleccionadas en la tabla */
    for(int i = 0; i < columnSize; i++)
        ui->avalvars->setItem(i,0, new QTableWidgetItem(columnNames.at(i)));
}

/**
 * @brief MainWindow::on_nextButton_clicked
 * Se verifica que se hayan seleccionado las variables para procesar y se
 * pasa a la pantalla para generar las estadisticas de las mismas.
 */
void MainWindow::on_nextButton_clicked()
{
    if(ui->selvars->rowCount() > 0){
        /* Oculto la vista principal */
        this->hide();
        /* Obtengo la lista de variables seleccionadas */
        QStringList list;
        for(int i = 0; i < ui->selvars->rowCount(); i++){
            list.append(ui->selvars->item(i,0)->text());
        }
        /* Cambio a la vista de estadisticas */
        this->ev->inputFile(this->fileName);
        this->ev->mostrarVistaEstadistica(list);
    }
    else
    {
        /* Caja de dialogo con un mensaje de error */
        QMessageBox(QMessageBox::Critical,"ERROR","No selecciono items para procesar.").exec();
    }
}

/**
 * @brief MainWindow::on_addVariableButton_clicked
 * Una vez seleccionada una variable en la tabla avalvars con este boton se la
 * coloca en la tabla selvars. En esta columna se encuentran todas las variables
 * que se procesaran con el algoritmo.
 */
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
        QMessageBox(QMessageBox::Information,"INFORMACION","Debe seleccionar"
                    " solo un item a la vez.").exec();;
    }
}

/**
 * @brief MainWindow::on_delVariableButton_clicked
 * Una vez seleccionada solo una variable de la columna selvars se elimina de
 * dicha columna una vez que se presiona este boton.
 */
void MainWindow::on_delVariableButton_clicked()
{
    if(ui->selvars->selectedItems().size() < 2 &&
            ui->selvars->selectedItems().size() > 0 )
        ui->selvars->removeRow(ui->selvars->currentItem()->row());
    else
        QMessageBox(QMessageBox::Information,"INFORMACION","Debe seleccionar"
                    " solo un item a la vez.").exec();;
}

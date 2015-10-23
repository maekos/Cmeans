#include "algoritmovista.h"
#include "ui_algoritmovista.h"

AlgoritmoVista::AlgoritmoVista(Matrix *matriz, CsvData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgoritmoVista)
{
    download.setParent(this);
    download.setMinimum(0);
    download.setMaximum(100);
    download.setMinimumDuration(0);
    download.setWindowModality(Qt::WindowModal);
    download.setWindowTitle("Generando Archivo");
    download.setLabelText("Generando archivo .csv");
    download.setCancelButtonText(QString());
    download.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                            Qt::CustomizeWindowHint);
    clasify.setParent(this);
    clasify.setMinimum(0);
    clasify.setMaximum(0);
    clasify.setMinimumDuration(0);
    clasify.setWindowModality(Qt::WindowModal);
    clasify.setWindowTitle("Clasificando...");
    clasify.setLabelText("Clasificando");
    clasify.setCancelButtonText(QString());
    clasify.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                           Qt::CustomizeWindowHint);

    ui->setupUi(this);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                          this->size(),
                                          qApp->desktop()->availableGeometry()));
    this->matriz = matriz;

    this->data = data;

    this->ui->inputFileText->setText(this->data->getFileName());
    this->ui->outputFileText->setText("default.csv");
}

AlgoritmoVista::~AlgoritmoVista()
{
    delete ui;
}

void AlgoritmoVista::on_eucli_clicked()
{
    if(!ui->eucli->isChecked()){
        ui->maha->setChecked(false);
        ui->diagonal->setChecked(false);
    }
}

void AlgoritmoVista::on_diagonal_clicked()
{
    if(!ui->diagonal->isChecked()){
        ui->maha->setChecked(false);
        ui->eucli->setChecked(false);
    }
}

void AlgoritmoVista::on_maha_clicked()
{
    if(!ui->maha->isChecked()){
        ui->eucli->setChecked(false);
        ui->diagonal->setChecked(false);
    }
}

void AlgoritmoVista::on_clasificarBoton_clicked()
{

    fuzzines = ui->fuzzyExponent->text().toFloat();
    cluster = ui->maxZones->text().toInt() - ui->minZones->text().toInt();
    epsilon = ui->convergenceCriteria->text().toFloat();

    Matrix B = boost::numeric::ublas::trans(*this->matriz); // Transpuesta

    ks.resize(ui->maxZones->text().toInt() - ui->minZones->text().toInt() + 1,
              this->matriz->size2()+1); // Para incluir las columnas

    for (int i = ui->minZones->text().toInt(), a = 0;
         i <= ui->maxZones->text().toInt(); i ++ , a++)
    {
        qDebug() << "cluster: " << i;
        ks.insert_element(a,0,i);
        Fuzzy f(B, i, fuzzines, epsilon);
        f.clustering();
        f.clusterClassification(&ks,a);
        clasify.show();
        QApplication::processEvents();
    }

    clasify.hide();

    if(ui->genFile->isChecked())
        this->makeFile();
}

void AlgoritmoVista::makeFile(QString file)
{
    QFile output(file);

    if(this->ui->outputFileText->text().isEmpty())
        output.setFileName(file);
    else
        output.setFileName(this->ui->outputFileText->text());

    if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&output);

    for(int i = 0; i < this->data->getRowCount() + 1; i++)
    {
        // Matriz de enteros de clasificaciones.
        for(int j = 0; j < this->ks.size1(); j++)
        {
            out << QString::number(ks.at_element(j,i)) << ",";
        }

        // Datos de archivo .csv
        for(int j = 0, k = 1; j < this->data->getColumnCount(); j++, k++)
        {
            if(k == this->data->getColumnCount())
                out << this->data->getDataAt(j,i);
            else
                out << this->data->getDataAt(j,i) << ",";
        }
        download.setValue((int)(i*100/this->data->getRowCount()));
        QApplication::processEvents();
    }
    download.setValue(100);
    output.close();
}

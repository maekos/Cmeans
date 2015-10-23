#ifndef CSVDATA_H
#define CSVDATA_H

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QFile>
#include <QMap>
#include <QDebug>

/**
 * @brief Clase para la manipulacion de archivos csv.
 *
 * Es importante que el archivo csv que se lea en la primera linea contenga
 * el nombre de la columna.
 * En caso de que contenga datos estos seran ignorados y tomados como nombre
 * de la columna.
 *
 */
class CsvData
{
public:

    CsvData(QString file);
    ~CsvData();

    QString getFileName();
    QStringList getColumnNames();
    QStringList getDataAt(int column);
    QString getDataAt(int col, int row);
    QStringList getDataFrom(const QString columnName);
    int getColumnCount();
    int getRowCount();

private:

    QFile file;                                         /**< Archivo de datos */
    QStringList columnNames;         /**< Lista con el nombre de las columnas */
    int rows;                              /**< Cantidad de filas del archivo */
    int columns;                        /**< Cantidad de columnas del archivo */
    QMap<QString,int> map;    /**< Para mapear el nombre de la columna con el */
                                                                  /*<  numero */
};

#endif // CSVDATA_H

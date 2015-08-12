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
private:

    QFile file;                                         /**< Archivo de datos */

    QStringList columnNames;         /**< Lista con el nombre de las columnas */

    int rows;                              /**< Cantidad de filas del archivo */

    int columns;                        /**< Cantidad de columnas del archivo */

    QMap<QString,int> map;    /**< Para mapear el nombre de la columna con el */
                              /*<  numero */

public:

    CsvData(QString file);

    /**
     * @brief Destructor
     *
     * Debe cerrar el archivo abierto para ser manipulado.
     *
     */
    ~CsvData();

    QStringList getColumnNames();
    QStringList getDataAt(int column);
    QStringList getDataFrom(const QString columnName);
    int getColumnCount();
    int getRowCount();
};

#endif // CSVDATA_H

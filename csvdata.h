#ifndef CSVDATA_H
#define CSVDATA_H

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QFile>
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

    QFile file; /**< Archivo de datos */

    QStringList columnNames; /**< Lista con el nombre de las columnas */

    int rows;

    int columns;

public:

    /**
     * @brief Constructor de la clase
     *
     * @param file Nombre del archivo a utilizar.
     *
     * @warning El nombre del archivo se toma en el lugar en donde se encuentra
     * el ejecutable del programa (Path relativo) .
     *
     */
    CsvData(QString file);

    /**
     * @brief Destructor
     *
     * Debe cerrar el archivo abierto para ser manipulado.
     *
     */
    ~CsvData();

    /**
     * @brief Devuelve una lista con el nombre de las columnas.
     *
     *  A partir de la lectura del archivo obtiene la primera linea que supone
     *  contiene el nombre de las columnas y devuelve una lista con los nombres
     *  ordenadas.
     *
     * @return Lista de Strings con el nombre de las columnas del archivo
     *        abierto.
     */
    QStringList getColumnNames();

    /**
     * @brief Obtiene una lista con los datos de la columna.
     *
     * Devuelve una lista con todos los datos en la columna @par column que es
     * un numero que se le pasa como parametro.
     *
     * @return Lista de datos de la columna.
     */
    QStringList getColumnData(int column);
};

#endif // CSVDATA_H

#include "csvdata.h"

/**
 * @brief Constructor de la clase
 *
 * @param file Nombre del archivo a utilizar.
 *
 * @warning El nombre del archivo se toma en el lugar en donde se encuentra
 * el ejecutable del programa (Path relativo) .
 *
 */
CsvData::CsvData(QString file)
{
    this->file.setFileName(file);
    if (!this->file.open(QIODevice::ReadOnly)) {
        qDebug() << this->file.errorString();
    }

    /* Lee la primera linea */
    QByteArray line = this->file.readLine();

    /* Divide la linea separada por comas y obtiene el numero de columnas*/
    this->columns = line.split(',').size();

    /* Obtiene de la primera fila el nombre de las columnas */
    for(int i = 0; i < this->columns; i++)
    {
        this->columnNames.append(line.split(',').at(i));
        this->map.insert(line.split(',').at(i),i);
    }

    /* Obtiene el numero de filas del archivo */
    while (!this->file.atEnd()) {
        this->file.readLine();
        this->rows++;
    }
    this->file.seek(0);
}

/**
 * @brief Destructor
 *
 * Debe cerrar el archivo abierto para ser manipulado.
 *
 */
CsvData::~CsvData()
{
    this->file.close();
}

/**
 * @brief CsvData::getColumnCount
 *
 * Devuelve el numero de columnas que tiene el archivo .csv.
 *
 * @return numero de columnas.
 */
int CsvData::getColumnCount()
{
    return (this->columns);
}

/**
 * @brief CsvData::getRowCount
 *
 * Devuelve el numero de filas que contiene el archivo .csv
 *
 * @return Numero de filas.
 */
int CsvData::getRowCount()
{
    return (this->rows-1);
}

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
QStringList CsvData::getColumnNames()
{
    return (this->columnNames);
}

/**
 * @brief Obtiene una lista con los datos de la columna.
 *
 * Devuelve una lista con todos los datos en la columna @par column que es
 * un numero que se le pasa como parametro.
 *
 * @return Lista de datos de la columna.
 */
QStringList CsvData::getDataAt(int column)
{
    QStringList wordList;
    this->file.readLine(); // Elimino los nombres de las columnas
    while (!this->file.atEnd()) {
        QByteArray line = this->file.readLine();
        wordList.append(line.split(',').at(column));
    }
    this->file.seek(0);
    return wordList;
}

/**
 * @brief CsvData::getDataFrom
 *
 * A partir del nombre de la columna pasado como parametro, devuelve un vector
 * con los datos pertenecientes a esa columna.
 *
 * @param columnName Nombre de la columnna de la cual se van a extraer los
 *                   datos.
 *
 * @return Lista de datos de la columna.
 */
QStringList CsvData::getDataFrom(const QString columnName)
{
    return (this->getDataAt(this->map[columnName]));
}

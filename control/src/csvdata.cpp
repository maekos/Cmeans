#include "csvdata.h"

CsvData::CsvData(QString file)
{
    this->file.setFileName(file);
    if (!this->file.open(QIODevice::ReadOnly)) {
        qDebug() << this->file.errorString();
    }

    QByteArray line = this->file.readLine();
    this->columns = line.split(',').size();

    for(int i = 0; i < this->columns; i++)
    {
        this->columnNames.append(line.split(',').at(i));
    }
}

CsvData::~CsvData()
{
    this->file.close();
}

QStringList CsvData::getColumnNames()
{
    return (this->columnNames);
}

QStringList CsvData::getColumnData(int column)
{
    QStringList wordList;

    while (!this->file.atEnd()) {
        QByteArray line = this->file.readLine();
        wordList.append(line.split(',').at(column));
    }
    this->file.seek(0);
    return wordList;
}

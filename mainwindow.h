#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QRect>
#include <QDesktopWidget>

#include "stats.h"
#include "csvdata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openFile_clicked();

    void on_section_Clicked(int section);

private:
    Ui::MainWindow *ui;

    QHeaderView *tableHeader;

    CsvData *data;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QHeaderView>
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

signals:
    void cambiarVistaEstadisticas();

private slots:
    void on_openFile_clicked();

    void on_nextButton_clicked();

    void on_addVariableButton_clicked();

    void on_delVariableButton_clicked();

private:
    Ui::MainWindow *ui;

    CsvData *data;

    QHeaderView *horizontalAval, *verticalAval;
    QHeaderView *horizontalSel, *verticalSel;

    int selectedItemRow;
};

#endif // MAINWINDOW_H

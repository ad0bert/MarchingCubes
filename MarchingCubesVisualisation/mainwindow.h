#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fileHandler.h"
#include "marchingcubes.h"

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
    void on_selectHeaderBtn_clicked();

    void on_selectImageBtn_clicked();

    void on_generateObjectBtn_clicked();

    void on_isolevelSlider_valueChanged(int value);

    void on_thresholdSlider_valueChanged(int value);

    void on_actionSaveAsStl_triggered();

    void on_enableWiring_toggled(bool checked);

    void on_enableSlicing_toggled(bool checked);

    void on_slicerSlider_valueChanged(int value);

private:
    void readFiles();
    Ui::MainWindow *ui;
    fileHandler *hdrFile;
    fileHandler *imgFile;
    marchingCubes *mc;
};

#endif // MAINWINDOW_H

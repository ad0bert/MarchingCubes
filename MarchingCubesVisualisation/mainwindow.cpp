#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hdrFile = new fileHandler();
    hdrFile->setType(hdr);
    imgFile = new fileHandler();
    imgFile->setType(img);
    mc = new marchingCubes();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete hdrFile;
    delete imgFile;
    delete mc;
}

void MainWindow::on_selectHeaderBtn_clicked()
{
    ui->headerPath->setText(QFileDialog::getOpenFileName(this, tr("Choose Header File"), "C://Users//Adobert//Downloads//Ortner//", "*.hdr files (*.hdr)"));
}

void MainWindow::on_selectImageBtn_clicked()
{
    ui->imagePath->setText(QFileDialog::getOpenFileName(this, tr("Choose Image File"), "C://Users//Adobert//Downloads//Ortner//", "*.img files (*.img)"));
}

void MainWindow::readFiles(){
    hdrFile->setPath(ui->headerPath->text().toStdString());
    imgFile->setPath(ui->imagePath->text().toStdString());
    hdrFile->readFile();
    imgFile->setHdr(hdrFile->getHdr());
    imgFile->readFile();
    //ui->isolevelSlider->setRange(hdrFile->getHdr().dime.cal_min, hdrFile->getHdr().dime.cal_min);
}

void MainWindow::on_generateObjectBtn_clicked()
{
    if (ui->headerPath->text() != "" && ui->imagePath->text() != ""){
        readFiles();
        mc->setAllData(imgFile->getData(),
                       hdrFile->getHdr().dime.glmax,
                       hdrFile->getHdr().dime.glmin,
                       200,
                       hdrFile->getHdr().dime.dim[1],
                       hdrFile->getHdr().dime.dim[2],
                       hdrFile->getHdr().dime.dim[3]
                       );
        mc->perform(ui->thresholdSlider->value());
        ui->widget->setObject(&mc->getResult());
        ui->widget->updateUI();
    }
}

void MainWindow::on_isolevelSlider_valueChanged(int value)
{
    mc->setIsolevel(value);
    mc->perform(ui->thresholdSlider->value());
    ui->widget->setObject(&mc->getResult());
    ui->widget->updateUI();
}

void MainWindow::on_thresholdSlider_valueChanged(int value)
{
    mc->perform(value);
    ui->widget->setObject(&mc->getResult());
    ui->widget->updateUI();
}

void MainWindow::on_actionSaveAsStl_triggered()
{
    mc->GenerateStlFile(QFileDialog::getSaveFileName(0, "Save file", "C://Users//Adobert//Desktop//", "STL files (*.stl)").toStdString());
}

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
}

void MainWindow::on_generateObjectBtn_clicked()
{
    if (ui->headerPath->text() != "" && ui->imagePath->text() != ""){
        readFiles();
        mc->setAllData(imgFile->getData(),
                       ui->isolevelSlider->value());

		ui->slicerSlider->setRange(0, hdrFile->getHdr().dime.dim[3] - 2);

		if (ui->enableSlicing->isChecked()){
			mc->perform(ui->thresholdSlider->value(), ui->slicerSlider->value());
		}
		else{
			mc->perform(ui->thresholdSlider->value());
		}
		
		ui->widget->setObject(&mc->getResult());
        
		ui->widget->updateUI(); 
        
    }
}

void MainWindow::on_isolevelSlider_valueChanged(int value)
{
    mc->setIsolevel(value);
	if (ui->enableSlicing->isChecked()){
		mc->perform(ui->thresholdSlider->value(), ui->slicerSlider->value());
	}
	else{
		mc->perform(ui->thresholdSlider->value());
	}
    ui->widget->setObject(&mc->getResult());
    ui->widget->updateUI();
}

void MainWindow::on_thresholdSlider_valueChanged(int value)
{
	if (ui->enableSlicing->isChecked()){
		mc->perform(value, ui->slicerSlider->value());
	}
	else{
		mc->perform(value);
	}
    ui->widget->setObject(&mc->getResult());
    ui->widget->updateUI();
}

void MainWindow::on_actionSaveAsStl_triggered()
{
    mc->generateStlFile(QFileDialog::getSaveFileName(0, "Save file", "C://Users//Adobert//Desktop//", "STL files (*.stl)").toStdString());
}

void MainWindow::on_enableWiring_toggled(bool checked)
{
    ui->widget->setWiring(checked);
}

void MainWindow::on_enableSlicing_toggled(bool checked)
{
    ui->slicerSlider->setEnabled(checked);
	if (ui->enableSlicing->isChecked()){
		mc->perform(ui->thresholdSlider->value(), ui->slicerSlider->value());
	}
	else{
		mc->perform(ui->thresholdSlider->value());
	}
	ui->widget->setObject(&mc->getResult());
	ui->widget->updateUI();

}

void MainWindow::on_slicerSlider_valueChanged(int value)
{
	mc->perform(ui->thresholdSlider->value(), value);
	ui->widget->setObject(&mc->getResult());
	ui->widget->updateUI();
}

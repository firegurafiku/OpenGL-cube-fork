#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
                ui->openGLWidget, SLOT(setDepth(int)));

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
            this, SLOT(sliderChanged(int)));

    connect(ui->spinBox, SIGNAL(valueChanged(int)),
                this, SLOT(depthSpinBoxChanged(int)));

    connect(ui->openGLWidget, SIGNAL(setMaxDepthSignal(int)),
                this, SLOT(setMaxDepth(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMaxDepth(int d)
{
    this->ui->horizontalSlider->setRange(0, d);
    this->ui->spinBox->setRange(0, d);
}

void MainWindow::depthSpinBoxChanged(int d)
{
    ui->horizontalSlider->setValue(d);
}

void MainWindow::sliderChanged(int d)
{
    ui->spinBox->setValue(d);
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open...");
    if (file_name != "") {
        ui->openGLWidget->readFile(file_name);
    }
}

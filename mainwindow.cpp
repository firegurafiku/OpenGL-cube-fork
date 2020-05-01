#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    this->ui->horizontalSlider->setMaximum(d);
    this->ui->spinBox->setMaximum(d);
}

void MainWindow::depthSpinBoxChanged(int d)
{
    ui->horizontalSlider->setValue(d);
}

void MainWindow::sliderChanged(int d)
{
    ui->spinBox->setValue(d);
}


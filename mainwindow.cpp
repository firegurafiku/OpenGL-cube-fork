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

    //connect(ui->uxParameterComboBox, SIGNAL(currentIndexChanged))
    connect(ui->uxSliceAxisX, &QRadioButton::toggled, [this] (bool ena) {
        if (ena) ui->openGLWidget->setSliceAxis(0);
    });
    connect(ui->uxSliceAxisY, &QRadioButton::toggled, [this] (bool ena) {
        if (ena) ui->openGLWidget->setSliceAxis(1);
    });
    connect(ui->uxSliceAxisZ, &QRadioButton::toggled, [this] (bool ena) {
        if (ena) ui->openGLWidget->setSliceAxis(2);
    });
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
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть...");
    if (file_name != "") {
        ui->openGLWidget->readFile(file_name);
        ui->horizontalSlider->setDisabled(false);
        ui->spinBox->setDisabled(false);
    }
}

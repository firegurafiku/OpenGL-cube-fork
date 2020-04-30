#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
                ui->openGLWidget, SLOT(setDepth(int)));
    connect(ui->openGLWidget, SIGNAL(setMaxDepthSignal(int)),
                this, SLOT(setMaxDepth(int)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setMaxDepth(int d)
{
    this->ui->horizontalSlider->setMaximum(d);
}

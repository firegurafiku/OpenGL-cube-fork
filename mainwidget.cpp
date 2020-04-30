#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
                ui->openGLWidget, SLOT(zoom(int)));
    ui->horizontalSlider->setMaximum(200);
}

MainWidget::~MainWidget()
{
    delete ui;
}

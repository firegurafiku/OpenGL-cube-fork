#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <stdexcept>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private:
    Ui::MainWidget *ui;
private slots:
    void setMaxDepth(int d);
    void depthSpinBoxChanged(int d);
    void sliderChanged(int d);
};

#endif // MAINWIDGET_H

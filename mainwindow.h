#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void on_actionOpen_triggered();
private:
    Ui::MainWindow *ui;
private slots:
    void setMaxDepth(int d);
    void depthSpinBoxChanged(int d);
    void sliderChanged(int d);
};

#endif // MAINWINDOW_H

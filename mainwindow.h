#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <iostream>
#include <vector>

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void resizeEvent(QResizeEvent *event);
private:
    void loadVertexData();
    int cube_width;
    int cube_height;
    int cube_depth;
    GLuint texBufferID;
    GLuint texCoordID;
    std::vector<GLfloat> data;
    std::vector<GLfloat> bitmap;
};

#endif // MAINWINDOW_H

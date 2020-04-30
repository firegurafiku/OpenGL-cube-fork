#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <iostream>
#include <vector>

class Widget : public QGLWidget
{
    Q_OBJECT
public slots:
    void zoom(int val);
public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void resizeEvent(QResizeEvent *event);
private:
    void loadVertexData();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int curr_zoom;
    QPoint m_position;
    QVector2D diff;
    size_t cube_width;
    size_t cube_height;
    size_t cube_depth;
    GLuint texBufferID;
    GLuint texCoordID;
    std::vector<GLfloat> data;
    std::vector<GLfloat> bitmap;
};

#endif // MAINWINDOW_H

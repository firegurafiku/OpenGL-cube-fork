#ifndef GLWIDGET_H
#define GLWIDGET_H

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
public:
    Widget(QWidget *parent = 0);
    ~Widget();
signals:
    void setMaxDepthSignal(int d);
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
    void wheelEvent(QWheelEvent  *event);
    void zoom(int val);
    void createTexture();
    int curr_zoom;
    QPoint m_position;
    QVector2D diff;
    size_t cube_width;
    size_t cube_height;
    size_t cube_depth;
    size_t curr_depth;
    GLuint texBufferID;
    GLuint texCoordID;
    std::vector<GLfloat> data;
    std::vector<GLfloat> bitmap;
private slots:
    void setDepth(int d);
};

#endif // GLWIDGET_H

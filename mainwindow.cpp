#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeGL()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_COLOR_ARRAY);
    glEnable(GL_VERTEX_ARRAY);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glColorMaterial(GL_FRONT, GL_EMISSION);
//    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glNormal3f(0.0f, 0.0f, 1.0f);

    GLfloat vertices[] = {
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
    };

    GLubyte indices[] = {
        0, 1, 2, 3,
        1, 5, 6, 2,
        5, 4, 7, 6,
        0, 4, 5, 1,
        0, 3, 7, 4,
        3, 2, 6, 7
    };
    glColorPointer(4, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
}

void MainWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    qreal aspect_ratio = qreal(w) / h;
    glOrtho(-2 * aspect_ratio, 2 * aspect_ratio, -2, 2, 2, -2);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(), this->height());
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_position = event->pos();
    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton){
        m_position = event->pos();
    }
    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton){
        return;
    }
    diff = QVector2D(event->pos() - m_position);
    m_position = event->pos();
    glRotatef(diff.length() / 2.0f, diff.y(), diff.x(), 0.0f);

    update();
}

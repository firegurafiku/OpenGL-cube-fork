#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeGL()
{
    loadVertexData();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_ambient[] =  { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] =  { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat mat_shininess[]={50.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColorPointer(4, GL_FLOAT, 0, colors.data());
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());
    glNormalPointer(GL_FLOAT, 0, normals.data());
    glDrawArrays(GL_QUADS, 0, 24);
}

void MainWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    qreal aspect_ratio = qreal(w) / h;
    glOrtho(-1 * aspect_ratio, 1 * aspect_ratio, -1, 1, 1, -1);
    glMatrixMode(GL_MODELVIEW);
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_L:
            if(glIsEnabled(GL_LIGHTING)){
                glDisable(GL_LIGHTING);
            }else{
                glEnable(GL_LIGHTING);
            }

            update();
            break;
    }
}

void MainWindow::loadVertexData()
{
    std::ifstream fin("vertices.txt");
    GLfloat x;
    while(fin >> x){
        vertices.push_back(x);
    }
    fin.close();
    fin = std::ifstream("colors.txt");
    while(fin >> x){
        colors.push_back(x);
    }
    fin.close();
    fin = std::ifstream("normals.txt");
    while(fin >> x){
        normals.push_back(x);
    }
}

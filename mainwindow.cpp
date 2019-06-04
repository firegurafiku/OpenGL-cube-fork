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
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_ambient[] =  { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] =  { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[]={50};

    glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT,GL_AMBIENT, light_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, light_diffuse);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glInterleavedArrays(GL_N3F_V3F, 0, vertices.data());
    glDrawArrays(GL_QUADS, 0, numberOfVertices);
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
    QFile vertexDataFile("vertices.txt");
    vertexDataFile.open(QFile::ReadOnly | QFile::Text);

    QTextStream in(&vertexDataFile);
    in >> numberOfVertices;
    vertices.resize(numberOfVertices * 6);
    int i = 0;
    while(!in.atEnd()){
        in >> vertices[i++];
    }
}

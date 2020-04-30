#include "glwidget.h"

void Widget::zoom(int val)
{
    curr_zoom = val;
    glLoadIdentity();
    glScalef( 1.0f + static_cast<GLfloat>(val) / 25,
                  1.0f + static_cast<GLfloat>(val) / 25, 1.0f);
    this->setCursor(curr_zoom == 0 ? Qt::ArrowCursor : Qt::OpenHandCursor);
    update();
}

Widget::Widget(QWidget *parent)
    : QGLWidget(parent),
      curr_zoom(0)
{
    loadVertexData();
}

Widget::~Widget()
{

}

void Widget::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glDepthRange(1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texCoordID);
    glBindTexture(GL_TEXTURE_2D, texCoordID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    size_t curr_depth = 0;
    for (size_t i = 0; i < cube_height; ++i) {
        for (size_t j = 0; j < cube_width; ++j) {
            size_t offset = curr_depth * cube_width * cube_height;
            size_t data_idx = offset + i * cube_width + j;
            size_t bitmap_idx = ((cube_height - 1 - i) * cube_width + j) * 4;
            bitmap[bitmap_idx] = 1.0f;
            bitmap[bitmap_idx + 1] = 0.0f;
            bitmap[bitmap_idx + 2] = 0.0f;
            bitmap[bitmap_idx + 3] = data[data_idx];
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cube_width,
           cube_height, 0, GL_RGBA, GL_FLOAT,
           bitmap.data());
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    qreal aspect_ratio = qreal(w) / h;
    glOrtho(-1 * aspect_ratio, 1 * aspect_ratio, -1, 1, 1, -1);
    glMatrixMode(GL_MODELVIEW);
}

void Widget::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(), this->height());
    update();
}

void Widget::loadVertexData()
{
    QFile vertexDataFile("data.txt");
    vertexDataFile.open(QFile::ReadOnly | QFile::Text);

    QTextStream in(&vertexDataFile);
    in >> cube_width >> cube_height >> cube_depth;
    size_t size = cube_width * cube_height * cube_depth;

    data.resize(size);
    bitmap.resize(cube_width * cube_height * 4);
    for (size_t i = 0; i < size; ++i) {
        in >> data[i];
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton) {
        return;
    }
    if (curr_zoom > 0) {
        this->setCursor(Qt::ClosedHandCursor);
    }
    m_position = event->pos();
    event->accept();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton){
        m_position = event->pos();
    }
    if (curr_zoom > 0) {
        this->setCursor(Qt::OpenHandCursor);
    }
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton || curr_zoom == 0){
        return;
    }
    diff = QVector2D(event->pos() - m_position);
    m_position = event->pos();
    float d = curr_zoom / 10.0 + 1.0;
    glTranslatef(diff.x() / 400 / d, - diff.y() / 400 / d, 0.0);
    update();
}


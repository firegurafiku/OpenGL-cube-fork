#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent),
      curr_zoom(0),
      curr_depth(0)
{

}

void GLWidget::zoom(int val)
{
    curr_zoom = val;
    glLoadIdentity();
    glScalef( 1.0f + static_cast<GLfloat>(val) / 25,
                  1.0f + static_cast<GLfloat>(val) / 25, 1.0f);
    this->setCursor(curr_zoom == 0 ? Qt::ArrowCursor : Qt::OpenHandCursor);
    update();
}

void GLWidget::setDepth(int d)
{
    curr_depth = d;
    createTexture();
    update();
}

void GLWidget::initializeGL()
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
}

void GLWidget::createTexture()
{
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
    setMaxDepthSignal(cube_depth - 1);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    qreal aspect_ratio = qreal(w) / h;
    glOrtho(-1 * aspect_ratio, 1 * aspect_ratio, -1, 1, 1, -1);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(), this->height());
    update();
}

void GLWidget::readFile(const QString& file_name)
{
    QFile vertexDataFile(file_name);
    vertexDataFile.open(QFile::ReadOnly | QFile::Text);

    QTextStream in(&vertexDataFile);
    in >> cube_width >> cube_height >> cube_depth;
    size_t size = cube_width * cube_height * cube_depth;

    data.resize(size);
    bitmap.resize(cube_width * cube_height * 4);
    for (size_t i = 0; i < size; ++i) {
        in >> data[i];
    }
    createTexture();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
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

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton){
        m_position = event->pos();
    }
    if (curr_zoom > 0) {
        this->setCursor(Qt::OpenHandCursor);
    }
    event->accept();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
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

void GLWidget::wheelEvent(QWheelEvent  *event)
{
    if (event->angleDelta().y() > 0) {
        this->zoom(curr_zoom + 2);
    } else {
        this->zoom(curr_zoom - 2);
    }
}

GLWidget::~GLWidget()
{

}

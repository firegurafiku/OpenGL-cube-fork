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

void GLWidget::setParameterKind(int parameterKindIdx)
{

}

void GLWidget::setSliceAxis(int sliceAxisIdx)
{

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
    netCDF::NcVar var;
    switch (curr_parameter_kind) {
        case 0: var = dataFile->getVar("epsilon"); break;
        case 1: var = dataFile->getVar("epsilon"); break;
        case 2: var = dataFile->getVar("epsilon"); break;
        case 3: var = dataFile->getVar("mu"); break;
        case 4: var = dataFile->getVar("mu"); break;
        case 5: var = dataFile->getVar("mu"); break;
        case 6: var = dataFile->getVar("sigmaX"); break;
        case 7: var = dataFile->getVar("sigmaY"); break;
        case 8: var = dataFile->getVar("sigmaZ"); break;
    }

    std::size_t numDataPoints;
    std::size_t textureWidth, textureHeight;
    std::vector<std::size_t> start, count;

    switch (curr_slice_axis) {
        case 0:
            if (curr_depth >= cube_width)
                curr_depth = cube_width - 1;

            emit setMaxDepthSignal(cube_width);

            numDataPoints = cube_height * cube_depth;
            start = {curr_depth, 0, 0};
            count = {1, cube_height, cube_depth};
            textureWidth = cube_height;
            textureHeight = cube_depth;
            break;

        case 1:
            if (curr_depth >= cube_height)
                curr_depth = cube_height - 1;

            emit setMaxDepthSignal(cube_height);

            numDataPoints = cube_width * cube_depth;
            start = {0, curr_depth, 0};
            count = {cube_width, 1, cube_depth};
            textureWidth = cube_width;
            textureHeight = cube_depth;
            break;

        case 2:
            if (curr_depth >= cube_depth)
                curr_depth = cube_depth - 1;

            emit setMaxDepthSignal(cube_depth);

            numDataPoints = cube_width * cube_depth;
            start = {0, 0, curr_depth};
            count = {cube_width, cube_height, 1};
            textureWidth = cube_width;
            textureHeight = cube_height;
            break;
    }

    bitmap.resize(numDataPoints);
    var.getVar(start, count, &bitmap[0]);

    for (auto& f: bitmap)
        f = f - 1.0f;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth,
           textureHeight, 0, GL_RED, GL_FLOAT,
           bitmap.data());

    /*

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
    */
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float ratio = static_cast<float>(cube_width) / cube_height;
    if (ratio < 1) {
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f * ratio, -0.5, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f(0.5f * ratio, -0.5, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f(0.5f * ratio, 0.5, 0.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f * ratio, 0.5, 0.0);
        glEnd();
    } else {
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5f / ratio, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5f / ratio, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5f / ratio, 0.0);
            glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5f / ratio, 0.0);
        glEnd();
    }
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
    using namespace netCDF;
    dataFile.emplace(file_name.toStdString(), NcFile::read);

    cube_width  = dataFile->getDim("Nx").getSize();
    cube_height = dataFile->getDim("Ny").getSize();
    cube_depth  = dataFile->getDim("Nz").getSize();

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

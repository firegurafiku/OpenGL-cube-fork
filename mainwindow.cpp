#include "mainwindow.h"
#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define YELLOW 1.0f, 1.0f, 0.0f

MainWindow::MainWindow(QWidget *parent)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::drawLayer(int n)
{
    GLfloat x = -0.5f;
    GLfloat y = 0.5f;
    std::vector<GLfloat> vect;
    GLfloat idx = n * cube_width * cube_height;
    for (int i = 0; i < cube_height; ++i) {
        for (int j = 0; j < cube_width; ++j) {
            vect = { RED, data[idx], 0.0f, 0.0f, 1.0f, x, y, 0.0f };
            interleaved_array.insert(interleaved_array.end(), vect.begin(), vect.end());
            vect = { RED, data[idx], 0.0f, 0.0f, 1.0f, x, y - rect_size, 0.0f };
            interleaved_array.insert(interleaved_array.end(), vect.begin(), vect.end());
            vect = { RED, data[idx], 0.0f, 0.0f, 1.0f, x + rect_size, y - rect_size, 0.0f };
            interleaved_array.insert(interleaved_array.end(), vect.begin(), vect.end());
            vect = { RED, data[idx], 0.0f, 0.0f, 1.0f, x + rect_size, y, 0.0f };
            interleaved_array.insert(interleaved_array.end(), vect.begin(), vect.end());
            x += rect_size;
            ++idx;
        }
        x = -0.5f;
        y -= rect_size;
    }
    glInterleavedArrays(GL_C4F_N3F_V3F, 0, interleaved_array.data());
    glDrawArrays(GL_QUADS, 0, cube_width * cube_height * 4);
}

void MainWindow::initializeGL()
{
    loadVertexData();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glDepthRange(1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawLayer(0);
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

void MainWindow::loadVertexData()
{
    QFile vertexDataFile("data.txt");
    vertexDataFile.open(QFile::ReadOnly | QFile::Text);

    QTextStream in(&vertexDataFile);
    in >> cube_width >> cube_height >> cube_depth;
    int size = cube_width * cube_height * cube_depth;

    data.resize(size);
    for (int i = 0; i < size; ++i) {
        in >> data[i];
    }

    int mx = qMax(cube_width, cube_height);
    rect_size = 1.0f / mx;
}

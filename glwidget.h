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
#include <QString>
#include <vector>
#include <optional>
#include <netcdf>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void readFile(const QString& file_name);
signals:
    void setMaxDepthSignal(int d);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void resizeEvent(QResizeEvent *event);
private:
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
    int curr_parameter_kind = 0;
    int curr_slice_axis = 0;
    GLuint texBufferID;
    GLuint texCoordID;
    std::optional<netCDF::NcFile> dataFile;
    std::vector<GLfloat> data;
    std::vector<GLfloat> bitmap;
public slots:
    void setParameterKind(int parameterKindIdx);
    void setSliceAxis(int sliceAxisIdx);
    void setDepth(int d);
};

#endif // GLWIDGET_H

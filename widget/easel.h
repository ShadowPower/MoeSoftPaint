#ifndef EASEL_H
#define EASEL_H

#include <QtWidgets>

class Easel : public QOpenGLWidget
{
    Q_OBJECT

private:
    QImage testImg;
    QPoint canvasPos = QPoint(0,0); // 画板和中心点的偏差, (0,0) 表示图像显示在画面中央
    QSize canvasSize; // 画板大小
    qreal canvasScale; // 画板缩放比例
    QPoint lastMousePos = QPoint(0,0); // 上次鼠标坐标
    bool moving = false;

public:
    explicit Easel(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

signals:

public slots:


};

#endif // EASEL_H

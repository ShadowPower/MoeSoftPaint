#include "easel.h"

Easel::Easel(QWidget *parent) : QOpenGLWidget(parent)
{
    QImage img(800, 600, QImage::Format_ARGB32_Premultiplied);

    QPainter painter(&img);
    painter.fillRect(0, 0, 800, 600, QColor(255, 255, 255));

    testImg = img;

    canvasSize = testImg.size();
    // 计算宽高比
    qreal easelRadio = static_cast<double>(this->size().width()) / this->size().height();
    qreal canvasRadio = static_cast<double>(canvasSize.width()) / canvasSize.height();

    if (easelRadio > canvasRadio) {
        // 根据画布高度缩放
        canvasScale = static_cast<double>(this->size().height()) / canvasSize.height();
    } else {
        // 根据画布宽度缩放
        canvasScale = static_cast<double>(this->size().width()) / canvasSize.width();
    }

    canvasScale = 0.218;

    QSurfaceFormat format;
    format.setDepthBufferSize(0);
    format.setStencilBufferSize(0);
    format.setSamples(1);
    setFormat(format);
}

void Easel::initializeGL() {
    glClearColor(0.5, 0.5, 0.5, 1);
}

void Easel::paintGL() {
    // 计算画布的左上角顶点坐标
    // 考虑画布位于画面中央
    // 实际画布尺寸 = 画布尺寸 * 画布缩放
    // 顶点坐标 = 画布尺寸 / 2 - 图像尺寸 / 2
    // 加上画布偏移量来实现画布拖拽功能，更改画布位置只需要改变 canvasPos

    int top = (this->size().height() - canvasSize.height() * canvasScale) / 2 + canvasPos.y();
    int left = (this->size().width() - canvasSize.width() * canvasScale) / 2 + canvasPos.x();

    QPainter painter(this);
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    //painter.fillRect(0, 0, this->size().width(), this->size().height(), QColor(50, 120, 110));
    painter.drawText(left, top - 12, "x:" + QString::number(canvasPos.x()) + ", y:" + QString::number(canvasPos.y()) + " (" + QString::number(static_cast<int>(canvasScale * 100)) + "%)");
    painter.drawImage(QRect(left, top, canvasSize.width() * canvasScale, canvasSize.height() * canvasScale), testImg);

}

void Easel::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void Easel::mouseMoveEvent(QMouseEvent *event) {
    if (moving) {
        canvasPos += event->pos() - lastMousePos;
        update();
    }
    lastMousePos = event->pos();
}

void Easel::mousePressEvent(QMouseEvent *event) {
    moving = true;
}

void Easel::mouseReleaseEvent(QMouseEvent *event) {
    moving = false;
}

void Easel::wheelEvent(QWheelEvent *event) {
    // mouseCenterDelta 是鼠标位置和视图中心点偏移值
    QPoint mouseCenterDelta = event->pos() - QPoint(this->size().width() / 2, this->size().height() / 2);

    qreal nextScale = canvasScale + canvasScale * event->angleDelta().y() / 960.0;
    if (nextScale > 0.01) {
        // 缩放时把图片跟中心点的偏移也缩放，nextScale / canvasScale 是图像缩放比值
        canvasPos *= nextScale / canvasScale;
        // nextScale / canvasScale - 1 得到放大或缩小的比值，例如新图像是旧图像的 150%，则放大了 50%，得 +0.5，又例如 50%，为缩小 50%，得 -0.5。
        // 做放大缩小操作之后，让图像中心点向鼠标坐标移动，缩小时靠近，放大时远离，靠近/远离的比值为图像缩放比值
        // canvasPos 也是视图中心点和画布的中心点偏移值，可以跟 mouseCenterDelta 参照
        // 这样缩小到极限小的时候，无论图片位于何处，canvasPos 会越来越接近 mouseCenterDelta，而放大是相反的过程。接近和远离的比例就是放大和缩小的比例
        // 实现根据鼠标坐标放大缩小
        canvasPos -= mouseCenterDelta * (nextScale / canvasScale - 1);
        canvasScale = nextScale;
    } else {
        canvasScale = 0.01;
    }
    update();
}

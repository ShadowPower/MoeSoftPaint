#ifndef MOESOFTPAINT_H
#define MOESOFTPAINT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MoeSoftPaint; }
QT_END_NAMESPACE

class MoeSoftPaint : public QMainWindow
{
    Q_OBJECT

public:
    MoeSoftPaint(QWidget *parent = nullptr);
    ~MoeSoftPaint();

private slots:
    void on_actionToolBar_triggered(bool checked);

private:
    Ui::MoeSoftPaint *ui;
};
#endif // MOESOFTPAINT_H

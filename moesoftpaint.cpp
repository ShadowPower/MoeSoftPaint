#include "moesoftpaint.h"
#include "ui_moesoftpaint.h"

MoeSoftPaint::MoeSoftPaint(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MoeSoftPaint)
{
    ui->setupUi(this);

    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->addAction(ui->actionPencil);
    toolGroup->addAction(ui->actionBrush);
    toolGroup->addAction(ui->actionEraser);
    toolGroup->addAction(ui->actionPaint);
    toolGroup->addAction(ui->actionSip);
    toolGroup->addAction(ui->actionMagic);
    toolGroup->addAction(ui->actionShape);
    toolGroup->addAction(ui->actionDrag);
    toolGroup->addAction(ui->actionTextBox);
    toolGroup->setExclusive(true);
    ui->toolToolBar->addActions(toolGroup->actions());
}

MoeSoftPaint::~MoeSoftPaint()
{
    delete ui;
}


void MoeSoftPaint::on_actionToolBar_triggered(bool checked)
{
    ui->toolToolBar->setVisible(checked);
}

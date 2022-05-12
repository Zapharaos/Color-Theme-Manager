#include "themewidget.h"
#include "ui_themewidget.h"

ThemeWidget::ThemeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeWidget)
{
    ui->setupUi(this);
}

ThemeWidget::~ThemeWidget()
{
    delete ui;
}

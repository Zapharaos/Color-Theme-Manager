#include "themeitemwidget.h"
#include "ui_themeitemwidget.h"

ThemeItemWidget::ThemeItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeItemWidget)
{
    ui->setupUi(this);
}

ThemeItemWidget::~ThemeItemWidget()
{
    delete ui;
}

void ThemeItemWidget::loadColor(ColorPair *color)
{
    m_color = color;
    ui->colorID->setText(m_color->GetID());
    ui->srcRgb->setText(ColorPair::toRGBA(m_color->GetSource()));
    ui->trgRgb->setText(ColorPair::toRGBA(m_color->GetTarget()));
    // chercher theme dans fichier load
}

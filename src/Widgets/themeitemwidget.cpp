#include "themeitemwidget.h"
#include "ui_themeitemwidget.h"

#include <QColorDialog>
#include <QMessageBox>

ThemeItemWidget::ThemeItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeItemWidget)
{
    ui->setupUi(this);

    m_color = new ColorPair("New Color");

    ui->colorName->setText(m_color->GetName());
    ui->colorName->setAlignment(Qt::AlignCenter);
    ui->srcRgb->setText(ColorPair::toRGBA(m_color->GetSource()));
    ui->srcRgb->setAlignment(Qt::AlignCenter);
    ui->trgRgb->setText(ColorPair::toRGBA(m_color->GetTarget()));
    ui->trgRgb->setAlignment(Qt::AlignCenter);

    connect(this, SIGNAL(sendRemoveColor(ColorPair *)), parent, SLOT(removeColorItem(ColorPair *)));
}

ThemeItemWidget::~ThemeItemWidget()
{
    delete ui;
}

void ThemeItemWidget::setColor(const ColorPair &colorPair)
{
    m_color = new ColorPair(colorPair);
    // TO DO : set color elements
}

ColorPair* ThemeItemWidget::getColor()
{
    return m_color;
}

void ThemeItemWidget::loadColor(ColorPair *color)
{
    m_color = color;
    ui->colorName->setText(m_color->GetName());
    ui->srcRgb->setText(ColorPair::toRGBA(m_color->GetSource()));
    ui->trgRgb->setText(ColorPair::toRGBA(m_color->GetTarget()));
    // chercher theme dans fichier load
}

void ThemeItemWidget::on_deleteButton_clicked()
{
    QMessageBox popup;
    popup.setWindowTitle("Confirm Deletion");
    popup.setIcon(QMessageBox::Question);
    popup.setText(QString("Delete the color \"%1\"?").arg(m_color->GetName()));
    popup.setStandardButtons(QMessageBox::Discard | QMessageBox::Cancel);
    popup.setButtonText(QMessageBox::Discard, "Delete");

    switch(popup.exec())
    {
        case QMessageBox::Discard:
             emit sendRemoveColor(m_color);
             break;
        case QMessageBox::Cancel:
             break;
    }
}


void ThemeItemWidget::on_srcButton_clicked()
{
    // generate issue : item widget layout is too small
    // TODO : signal/slot to parent back and forth to avoid the issue

    QColor color = QColorDialog::getColor(ColorPair::toRGBA(m_color->GetSource()), this, "Pick source color");
    if(color.isValid())
    {
        ui->srcButton->setStyleSheet(QString("background-color: %1; border-style: solid; border-width: 1px; border-color: black; padding: 10px;").arg(color.name()));
        ui->srcRgb->setText(ColorPair::toRGBA(color));
        ui->srcRgb->setAlignment(Qt::AlignCenter);
        m_color->SetSource(color);

    }
}


void ThemeItemWidget::on_trgButton_clicked()
{
    // generate issue : item widget layout is too small
    // TODO : signal/slot to parent back and forth to avoid the issue

    QColor color = QColorDialog::getColor(ColorPair::toRGBA(m_color->GetTarget()), this, "Pick target color");
    if(color.isValid())
    {
        ui->trgButton->setStyleSheet(QString("background-color: %1; border-style: solid; border-width: 1px; border-color: black; padding: 10px;").arg(color.name()));
        ui->trgRgb->setText(ColorPair::toRGBA(color));
        ui->trgRgb->setAlignment(Qt::AlignCenter);
        m_color->SetTarget(color);
    }
}


void ThemeItemWidget::on_srcRgb_textChanged()
{
    auto rgb = ui->srcRgb->toPlainText();
    QColor color = ColorPair::fromRGBA(rgb);
    if(color.isValid())
    {
        ui->srcButton->setStyleSheet(QString("background-color: %1; border-style: solid; border-width: 1px; border-color: black; padding: 10px;").arg(color.name()));
        m_color->SetSource(color);
    }
}


void ThemeItemWidget::on_trgRgb_textChanged()
{
    auto rgb = ui->trgRgb->toPlainText();
    QColor color = ColorPair::fromRGBA(rgb);
    if(color.isValid())
    {
        ui->trgButton->setStyleSheet(QString("background-color: %1; border-style: solid; border-width: 1px; border-color: black; padding: 10px;").arg(color.name()));
        m_color->SetTarget(color);
    }
}


void ThemeItemWidget::on_colorName_textChanged()
{
    auto name = ui->colorName->toPlainText();

    if(name.isEmpty())
        return;

    m_color->SetName(name);
}


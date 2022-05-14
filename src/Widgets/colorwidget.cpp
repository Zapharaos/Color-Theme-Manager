#include "colorwidget.h"
#include "ui_colorwidget.h"

#include <QColorDialog>
#include <QMessageBox>

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorWidget)
{
    ui->setupUi(this);

    connect(this, SIGNAL(sendRemoveColor(ColorPair *)), parent, SLOT(removeColor(ColorPair *)));
}

ColorWidget::~ColorWidget()
{
    delete ui;
}

void ColorWidget::setColor(ColorPair *color)
{
    m_color = color;

    ui->colorName->setText(m_color->GetName());
    ui->colorName->setAlignment(Qt::AlignCenter);
    ui->srcRgb->setText(ColorPair::toRGBA(m_color->GetSource()));
    ui->srcRgb->setAlignment(Qt::AlignCenter);
    ui->trgRgb->setText(ColorPair::toRGBA(m_color->GetTarget()));
    ui->trgRgb->setAlignment(Qt::AlignCenter);
}

ColorPair* ColorWidget::getColor()
{
    return m_color;
}

void ColorWidget::loadColor(ColorPair *color)
{
    setColor(color);
}

void ColorWidget::on_deleteButton_clicked()
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


void ColorWidget::on_srcButton_clicked()
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


void ColorWidget::on_trgButton_clicked()
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


void ColorWidget::on_srcRgb_textChanged()
{
    auto rgb = ui->srcRgb->toPlainText();
    QColor color = ColorPair::fromRGBA(rgb);
    if(color.isValid())
    {
        ui->srcButton->setStyleSheet(QString("background-color: %1; border-style: solid; border-width: 1px; border-color: black; padding: 10px;").arg(color.name()));
        m_color->SetSource(color);
    }
}


void ColorWidget::on_trgRgb_textChanged()
{
    auto rgb = ui->trgRgb->toPlainText();
    QColor color = ColorPair::fromRGBA(rgb);
    if(color.isValid())
    {
        ui->trgButton->setStyleSheet(QString("background-color: %1; border-style: solid; border-width: 1px; border-color: black; padding: 10px;").arg(color.name()));
        m_color->SetTarget(color);
    }
}


void ColorWidget::on_colorName_textChanged()
{
    auto name = ui->colorName->toPlainText();

    if(name.isEmpty())
        return;

    m_color->SetName(name);
}


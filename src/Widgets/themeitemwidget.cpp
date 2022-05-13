#include "themeitemwidget.h"
#include "ui_themeitemwidget.h"

#include <QDialog>
#include <QMessageBox>

ThemeItemWidget::ThemeItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeItemWidget)
{
    ui->setupUi(this);

    m_color = new ColorPair("New Color");
    ui->colorID->setText(m_color->GetID());
    ui->srcRgb->setText(ColorPair::toRGBA(m_color->GetSource()));
    ui->trgRgb->setText(ColorPair::toRGBA(m_color->GetTarget()));

    connect(this, SIGNAL(sendRemoveColor(const QString)), parent, SLOT(removeColorItem(const QString)));
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
    ui->colorID->setText(m_color->GetID());
    ui->srcRgb->setText(ColorPair::toRGBA(m_color->GetSource()));
    ui->trgRgb->setText(ColorPair::toRGBA(m_color->GetTarget()));
    // chercher theme dans fichier load
}

void ThemeItemWidget::on_deleteButton_clicked()
{
    QMessageBox popup;
    popup.setWindowTitle("Confirm Deletion");
    popup.setIcon(QMessageBox::Question);
    popup.setText(QString("Delete the color \"%1\"?").arg(m_color->GetID()));
    popup.setStandardButtons(QMessageBox::Discard | QMessageBox::Cancel);
    popup.setButtonText(QMessageBox::Discard, "Delete");

    switch(popup.exec())
    {
        case QMessageBox::Ok:
             emit sendRemoveColor(m_color->GetID());
             break;
        case QMessageBox::Cancel:
             break;
    }
}


void ThemeItemWidget::on_editButton_clicked()
{
    if(ui->editButton->text() == "Edit")
    {
        ui->editButton->setText("Save");
    }
    else
    {
        ui->editButton->setText("Edit");
    }
}


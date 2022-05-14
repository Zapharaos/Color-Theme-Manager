#include "colorwidget.h"
#include "ui_colorwidget.h"

#include <QColorDialog>
#include <QMessageBox>

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorWidget)
{
    ui->setupUi(this);

    // ThemeWidget Signals :
    connect(this, SIGNAL(sendRemoveColor(ColorPair *)), parent, SLOT(removeColor(ColorPair *)));
    connect(this, SIGNAL(sendUpdateColor(bool)), parent, SLOT(updateColor(bool)));
}

ColorWidget::~ColorWidget()
{
    delete ui;
}

/*****************************************/
/***             Methods               ***/
/*****************************************/

// Inits a new colorpair
void ColorWidget::createColor()
{
    m_color = new ColorPair("New Color");
    updateColorDisplay();
}

// Sets from an already existing colorpair
void ColorWidget::setColor(ColorPair *color)
{
    m_color = color;
    updateColorDisplay();
}

// Returns the colorpair
ColorPair* ColorWidget::getColor()
{
    return m_color;
}

// Update the colorpair display
void ColorWidget::updateColorDisplay()
{
    ui->colorName->setText(m_color->GetName());
    ui->colorName->setAlignment(Qt::AlignCenter);
    ui->srcRgb->setText(ColorPair::toRGBA(m_color->GetSource()));
    ui->srcRgb->setAlignment(Qt::AlignCenter);
    ui->trgRgb->setText(ColorPair::toRGBA(m_color->GetTarget()));
    ui->trgRgb->setAlignment(Qt::AlignCenter);
}

/*****************************************/
/***              Slots                ***/
/*****************************************/

// Sets from an already existing colorpair
void ColorWidget::loadColor(ColorPair *color)
{
    m_color = color;
    updateColorDisplay();
}

/*****************************************/
/***             Events                ***/
/*****************************************/

// Removing the colorpair : asking for the customer's confirmation
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

// Name edited : Text
void ColorWidget::on_colorName_textChanged()
{
    // Get name from widget
    auto name = ui->colorName->text();

    // Name cannot be empty
    if(name.isEmpty())
    {
        ui->colorName->setStyleSheet(inputStyleError);
        return;
    }

    // Updating the colorpair
    ui->colorName->setStyleSheet(inputStyleDefault);
    m_color->SetName(name);
    emit sendUpdateColor(true);
}

// Source color edited : QColorDialog
void ColorWidget::on_srcButton_clicked()
{
    // generate issue : item widget layout is too small
    // TODO : signal/slot to parent back and forth to avoid the issue (maybe)

    // Get a selected color
    QColor color = QColorDialog::getColor(m_color->GetSource(), this, "Pick source color");

    // Valid : Updating the colorpair & display
    if(color.isValid())
    {
        ui->srcButton->setStyleSheet(QString(colorpickerStyleDefault).arg(color.name()));
        ui->srcRgb->setText(ColorPair::toRGBA(color));
        ui->srcRgb->setAlignment(Qt::AlignCenter);
        ui->srcRgb->setStyleSheet(inputStyleDefault);
        m_color->SetSource(color);
        emit sendUpdateColor(true);
    }
}

// Target color edited : QColorDialog
void ColorWidget::on_trgButton_clicked()
{
    // generate issue : item widget layout is too small
    // TODO : signal/slot to parent back and forth to avoid the issue (maybe)

    // Get a selected color
    QColor color = QColorDialog::getColor(m_color->GetTarget(), this, "Pick target color");

    // Valid : Updating the colorpair & display
    if(color.isValid())
    {
        ui->trgButton->setStyleSheet(QString(colorpickerStyleDefault).arg(color.name()));
        ui->trgRgb->setText(ColorPair::toRGBA(color));
        ui->trgRgb->setAlignment(Qt::AlignCenter);
        ui->trgRgb->setStyleSheet(inputStyleDefault);
        m_color->SetTarget(color);
        emit sendUpdateColor(true);
    }
}

// Source color edited : Text
void ColorWidget::on_srcRgb_textChanged()
{
    // Get color from widget
    auto rgb = ui->srcRgb->text();
    QColor color = ColorPair::fromRGBA(rgb);

    // Valid : Updating the colorpair & display
    if(color.isValid())
    {
        ui->srcButton->setStyleSheet(QString(colorpickerStyleDefault).arg(color.name()));
        ui->srcRgb->setStyleSheet(inputStyleDefault);
        m_color->SetSource(color);
        emit sendUpdateColor(true);
        return;
    }

    // Color is not valid : error
    ui->srcRgb->setStyleSheet(inputStyleError);
}

// Target color edited : Text
void ColorWidget::on_trgRgb_textChanged()
{
    // Get color from widget
    auto rgb = ui->trgRgb->text();
    QColor color = ColorPair::fromRGBA(rgb);

    // Valid : Updating the colorpair & display
    if(color.isValid())
    {
        ui->trgButton->setStyleSheet(QString(colorpickerStyleDefault).arg(color.name()));
        ui->trgRgb->setStyleSheet(inputStyleDefault);
        m_color->SetTarget(color);
        emit sendUpdateColor(true);
        return;
    }

    // Color is not valid : error
    ui->trgRgb->setStyleSheet(inputStyleError);
}

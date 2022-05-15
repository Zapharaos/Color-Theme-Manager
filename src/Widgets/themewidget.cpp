#include "themewidget.h"
#include "ui_themewidget.h"

#include "colorwidget.h"

ThemeWidget::ThemeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeWidget)
{
    ui->setupUi(this);

    // Inits style : theme name
    ui->name->setVisible(false);
    ui->name->setStyleSheet(nameStyleDefault);

    // Inits style : theme set of colorpairs
    ui->colorsList->setStyleSheet(colorpairStyleDefault);
    ui->colorsList->setGridSize(QSize());
}

ThemeWidget::~ThemeWidget()
{
    delete ui;
}

/*****************************************/
/***          Theme Methods            ***/
/*****************************************/

// Widget is updated from theme
void ThemeWidget::loadTheme(Theme *theme)
{
    // Init theme
    m_theme = theme;

    ui->name->setVisible(true);
    ui->name->setText(m_theme->getName());
    ui->name->setAlignment(Qt::AlignCenter);

    // Loads each colorpair
    ui->colorsList->clear();
    for(ColorPair *color : *(m_theme->getColorpairs()))
    {
        qDebug() << color->GetName();
        displayColor(color);
    }
}

// Clear every displayed element -> hide
void ThemeWidget::clearTheme()
{
    ui->colorsList->clear();
    ui->name->clear();
    ui->name->setVisible(false);
}

/*****************************************/
/***          Color Methods            ***/
/*****************************************/

void ThemeWidget::createColor()
{
    auto widget = new ColorWidget(this);
    widget->createColor();

    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

    ui->colorsList->addItem(item);
    ui->colorsList->setItemWidget(item, widget);

    m_theme->getColorpairs()->append(widget->getColor());
    m_theme->setEdited(true);
}

// Adding an already existing color to the display
void ThemeWidget::displayColor(ColorPair *color)
{
    // New list item widget
    auto widget = new ColorWidget(this);
    widget->setColor(color);

    // New list item
    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

    // Adding item + widget to list
    ui->colorsList->addItem(item);
    ui->colorsList->setItemWidget(item, widget);
}

// Removing a color from theme
void ThemeWidget::removeColor(ColorPair *color)
{
    // Looking for the color's ID
    for (int i = 0; i < ui->colorsList->count(); i++) {

        // Cast item to colorpair
        QListWidgetItem* item = ui->colorsList->item(i);
        ColorWidget* itemWidget = dynamic_cast<ColorWidget*>(ui->colorsList->itemWidget(item));
        ColorPair *colorPair = itemWidget->getColor();

        // Check if colorpair is corresponding
        if(colorPair->GetID() == color->GetID())
        {
            // Update theme
            m_theme->getColorpairs()->removeOne(color);
            m_theme->setEdited(true);
            delete item;
            break;
        }
    }
}

// Theme was edited
void ThemeWidget::updateColor(bool edited)
{
    m_theme->setEdited(edited);
}

/*****************************************/
/***             Events                ***/
/*****************************************/

// Edit the theme's name
void ThemeWidget::on_name_textChanged()
{
    // Get name from widget
    auto name = ui->name->text();

    // Name cannot be empty
    if(name.isEmpty())
    {
        ui->name->setStyleSheet(nameStyleError);
        return;
    }

    // Updating the theme
    ui->name->setStyleSheet(nameStyleDefault);
    m_theme->setName(name);
    m_theme->setEdited(true);
}


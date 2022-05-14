#include "themewidget.h"
#include "ui_themewidget.h"

#include "colorwidget.h"

ThemeWidget::ThemeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeWidget)
{
    ui->setupUi(this);
    ui->colorsList->setStyleSheet( "QListWidget::item { background: #e5e5e5; border: 1px solid black; border-radius: 3px;}" );

    ui->colorsList->setGridSize(m_qsize);
}

ThemeWidget::~ThemeWidget()
{
    delete ui;
}

void ThemeWidget::loadTheme(Theme *theme)
{
    m_theme = theme;
    ColorWidget* temp = new ColorWidget(this);
    m_qsize = temp->sizeHint() + QSize(20,20);
    ui->name->setText(m_theme->getID().toString());

    ui->colorsList->clear();
    for(ColorPair *color : *(m_theme->getColorpairs()))
        displayColor(color);
}

void ThemeWidget::displayColor(ColorPair *color)
{
    auto widget = new ColorWidget(this);
    widget->setColor(color);
    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

    ui->colorsList->addItem(item);
    ui->colorsList->setItemWidget(item, widget);
}

void ThemeWidget::createColor()
{
    auto color = new ColorPair("New Color");

    auto widget = new ColorWidget(this);
    widget->setColor(color);

    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

    ui->colorsList->addItem(item);
    ui->colorsList->setItemWidget(item, widget);

    m_theme->getColorpairs()->insert(color);
}

void ThemeWidget::removeColor(ColorPair *color)
{
    // Looking for the color's ID
    for (int i = 0; i < ui->colorsList->count(); i++) {
        QListWidgetItem* item = ui->colorsList->item(i);
        ColorWidget* itemWidget = dynamic_cast<ColorWidget*>(ui->colorsList->itemWidget(item));
        ColorPair *colorPair = itemWidget->getColor();
        if(colorPair->GetID() == color->GetID())
        {
            m_theme->getColorpairs()->remove(color);
            delete item;
            break;
        }
    }
}

#include "themewidget.h"
#include "ui_themewidget.h"

#include "themeitemwidget.h"

ThemeWidget::ThemeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeWidget)
{
    ui->setupUi(this);
    ui->colorsList->setStyleSheet( "QListWidget::item { background: #e5e5e5; border: 1px solid black; border-radius: 3px;}" );

    ui->colorsList->setGridSize(m_qsize);
    //bite->sizeHint();
}

ThemeWidget::~ThemeWidget()
{
    delete ui;
}

void ThemeWidget::loadTheme(Theme *theme)
{
    m_theme = theme;
    ThemeItemWidget* bite = new ThemeItemWidget(this);
    m_qsize = bite->sizeHint() + QSize(20,20);
    ui->name->setText(m_theme->getID().toString());
    // chercher theme dans fichier load
}

void ThemeWidget::createColor()
{
    auto widget = new ThemeItemWidget(this);
    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

    ui->colorsList->addItem(item);
    ui->colorsList->setItemWidget(item, widget);
}

void ThemeWidget::removeColorItem(ColorPair *color)
{
    // Looking for the color's ID
    for (int i = 0; i < ui->colorsList->count(); i++) {
        QListWidgetItem* item = ui->colorsList->item(i);
        ThemeItemWidget* itemWidget = dynamic_cast<ThemeItemWidget*>(ui->colorsList->itemWidget(item));
        ColorPair *colorPair = itemWidget->getColor();
        if(colorPair->GetID() == color->GetID())
        {
            delete item;
            break;
        }
    }
}

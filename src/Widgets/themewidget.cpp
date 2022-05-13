#include "themewidget.h"
#include "ui_themewidget.h"

#include "themeitemwidget.h"

ThemeWidget::ThemeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeWidget)
{
    ui->setupUi(this);

    ui->colorsList->setFlow(QListView::LeftToRight);
    ui->colorsList->setResizeMode(QListView::Adjust);
    ui->colorsList->setGridSize((new ThemeItemWidget())->size()*1.1);
    ui->colorsList->setViewMode(QListView::IconMode);

    for(int i=0; i<10;i++)
    {
        auto widget = new ThemeItemWidget();
        auto item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

        ui->colorsList->addItem(item);
        ui->colorsList->setItemWidget(item, widget);
    }
}

ThemeWidget::~ThemeWidget()
{
    delete ui;
}

void ThemeWidget::loadTheme(Theme *theme)
{
    m_theme = theme;
    ui->name->setText(m_theme->getID().toString());
    // chercher theme dans fichier load
}

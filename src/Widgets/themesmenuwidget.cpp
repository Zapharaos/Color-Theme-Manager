#include "themesmenuwidget.h"
#include "ui_themesmenuwidget.h"
#include "ui_mainwindow.h"

#include "customwidget.h"
#include "../OrientablePushButton.h"
#include <iostream>

ThemesMenuWidget::ThemesMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemesMenuWidget)
{
    ui->setupUi(this);

    ui->toggleMenu->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    ui->toggleMenu->setOrientation(OrientablePushButton::VerticalBottomToTop);

    for(int i=0; i<100; i++)
    {
        auto widget = new CustomWidget(this);
        widget->setText(QString("Theme %1").arg(i));

        auto item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());

        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, widget);
    }
}

ThemesMenuWidget::~ThemesMenuWidget()
{
    delete ui;
}

void ThemesMenuWidget::removeItem(const QString &text)
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto item = ui->listWidget->item(i);
        auto itemWidget = dynamic_cast<CustomWidget*>(ui->listWidget->itemWidget(item));
        if (itemWidget->getText() == text){
            delete item;
            break;
        }
    }
}

void ThemesMenuWidget::on_toggleMenu_clicked()
{
    if(ui->toggleMenu->text() == "Collapse")
    {
        ui->toggleMenu->setText("Expand");
        ui->listWidget->setVisible(false);
    }
    else
    {
        ui->toggleMenu->setText("Collapse");
        ui->listWidget->setVisible(true);
    }
}


#include "menuitemwidget.h"
#include "ui_menuitemwidget.h"

MenuItemWidget::MenuItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuItemWidget)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendRemoveItem(const QString &)), parent, SLOT(removeMenuItem(const QString &)));
}

MenuItemWidget::~MenuItemWidget()
{
    delete ui;
}

void MenuItemWidget::setText(const QString &text) {
    ui->label->setText(text);
}

QString MenuItemWidget::getText() {
    return ui->label->text();
}

void MenuItemWidget::on_toolButton_clicked()
{
    emit sendRemoveItem(getText());
}

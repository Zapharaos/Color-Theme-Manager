#include "menuitemwidget.h"
#include "ui_menuitemwidget.h"

MenuItemWidget::MenuItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuItemWidget)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendRemoveItem(const QUuid &)), parent, SLOT(removeMenuItem(const QUuid &)));
}

MenuItemWidget::~MenuItemWidget()
{
    delete ui;
}

void MenuItemWidget::setTheme(const QString &name)
{
    m_theme = new Theme(name);
    ui->label->setText(name);
}

Theme* MenuItemWidget::getTheme()
{
    return m_theme;
}

void MenuItemWidget::on_toolButton_clicked()
{
    emit sendRemoveItem(m_theme->getID());
}

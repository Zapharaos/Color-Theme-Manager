#include "menuitemwidget.h"
#include "ui_menuitemwidget.h"

MenuItemWidget::MenuItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuItemWidget)
{
    ui->setupUi(this);

    // Set close button icon
    ui->toolButton->setIcon(QIcon(":/res/resource/icons/feather/x.svg"));

    // MainWindow Signals :
    connect(this, SIGNAL(sendRemoveItem(Theme *)), parent, SLOT(removeMenuItem(Theme *)));
}

MenuItemWidget::~MenuItemWidget()
{
    delete ui;
}

/*****************************************/
/***        Getters / Setters          ***/
/*****************************************/

// New theme with custom name
void MenuItemWidget::setTheme(const QString &name)
{
    m_theme = new Theme(name);
    ui->label->setText(m_theme->getName());
}

// Updates theme from theme
void MenuItemWidget::setTheme(Theme *theme)
{
    m_theme = theme;
    ui->label->setText(m_theme->getName());
}

// Returns the theme
Theme* MenuItemWidget::getTheme()
{
    return m_theme;
}

void MenuItemWidget::updateLabel()
{
    ui->label->setText(m_theme->getName());
}

/*****************************************/
/***              Events               ***/
/*****************************************/

void MenuItemWidget::on_toolButton_clicked()
{
    emit sendRemoveItem(m_theme);
}

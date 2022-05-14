#include "menuitemwidget.h"
#include "ui_menuitemwidget.h"

MenuItemWidget::MenuItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuItemWidget)
{
    ui->setupUi(this);

    // MainWindow Signals :
    connect(this, SIGNAL(sendRemoveItem(const QUuid &)), parent, SLOT(removeMenuItem(const QUuid &)));
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

/*****************************************/
/***              Events               ***/
/*****************************************/

void MenuItemWidget::on_toolButton_clicked()
{
    emit sendRemoveItem(m_theme->getID());
}

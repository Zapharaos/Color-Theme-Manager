#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "menuitemwidget.h"
#include <QDebug>
#include <QIcon>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Collapse/Expand pushButton : vertical
    ui->toggleMenu->setOrientation(OrientablePushButton::VerticalBottomToTop);

    // Default menu item :
    if(ui->listWidget->count() == 0)
    {
        auto defaultItem = new QListWidgetItem("No themes yet !");
        defaultItem->setFlags(defaultItem->flags() & ~Qt::ItemIsEnabled);
        ui->listWidget->addItem(defaultItem);
    }
    ui->listWidget->setIconSize(QSize(35,35));

    connect(ui->actionCreate_new_theme, SIGNAL(triggered()), this, SLOT(createTheme()));

    connect(ui->actionCollapse_Expand_menu, SIGNAL(triggered()), this, SLOT(toggleMenu()));

    connect(this, SIGNAL(sendTheme(Theme *)), ui->theme, SLOT(loadTheme(Theme *)));

    connect(ui->actionCreate_new_color, SIGNAL(triggered()), this, SLOT(transmitCreateColor()));
    connect(this, SIGNAL(sendCreateColor()), ui->theme, SLOT(createColor()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

// Event : New theme (Ctrl+Maj+N)

void MainWindow::createTheme()
{
    // Check if head is default and removes it
    if(ui->listWidget->count() == 1 && ui->listWidget->item(0)->text() == "No themes yet !")
        ui->listWidget->removeItemWidget(ui->listWidget->takeItem(0));

    auto widget = new MenuItemWidget(this);
    widget->setTheme("New theme");

    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    item->setIcon(QIcon("../color-theme-manager/images/easteregg.png"));

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, widget);
    ui->listWidget->setCurrentItem(item);
}

// Event : Switch current theme

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == nullptr) return;
    auto currentItem = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(current));
    emit sendTheme(currentItem->getTheme());
}

// Event : Create color

void MainWindow::transmitCreateColor()
{
    emit sendCreateColor();
}

// Event : Collapse/Expand Menu (Ctrl+M)

void MainWindow::toggleMenu()
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

void MainWindow::on_toggleMenu_clicked()
{
    emit ui->actionCollapse_Expand_menu->trigger();
}

// Event : Remove item from Menu

void MainWindow::removeMenuItem(const QUuid &id)
{
    // Looking for the item's ID
    for (int i = 0; i < ui->listWidget->count(); i++) {
        QListWidgetItem* item = ui->listWidget->item(i);
        MenuItemWidget* itemWidget = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item));
        Theme *theme = itemWidget->getTheme();
        if (theme->getID() == id){
            delete item;
            break;
        }
    }

    // If empty after removal : insert default item
    if(ui->listWidget->count() == 0)
    {
        auto defaultItem = new QListWidgetItem("No themes yet !");
        defaultItem->setFlags(defaultItem->flags() & ~Qt::ItemIsEnabled);
        ui->listWidget->addItem(defaultItem);
    }
}


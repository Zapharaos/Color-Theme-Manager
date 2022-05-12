#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "menuitemwidget.h"
#include <QDebug>

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

    /*for(int i=0; i<100; i++)
    {
        auto widget = new MenuItemWidget(this);
        widget->setText(QString("Theme %1").arg(i));

        auto item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());

        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, widget);
    }*/

    connect(ui->actionCreate_new_theme, SIGNAL(triggered()), this, SLOT(createTheme()));
    connect(this, SIGNAL(sendCurrentTheme(const QString &)), this, SLOT(currentTheme(const QString &)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::createTheme()
{
    // Check if head is default and removes it
    if(ui->listWidget->count() == 1 && ui->listWidget->item(0)->text() == "No themes yet !")
        ui->listWidget->removeItemWidget(ui->listWidget->takeItem(0));

    auto widget = new MenuItemWidget(this);
    widget->setText("New theme");
    widget->setID(QUuid::createUuid());

    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, widget);

    /*QListWidgetItem* current = ui->listWidget->currentItem();
    MenuItemWidget* wid = dynamic_cast<MenuItemWidget*>( ui->listWidget->itemWidget(item) );
    qDebug() << dynamic_cast<MenuItemWidget*>(wid)->getText();
    emit sendCurrentTheme(widget->getText());*/

    /*qDebug() << ui->listWidget->count();
    QListWidgetItem* current = ui->listWidget->currentItem();
    LblNames* widget = dynamic_cast<LblNames*>( listWidget->itemWidget(item) );*/

    emit sendCurrentTheme(dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item))->getText());
}

// Event : Switch current theme

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == nullptr) return;
    emit sendCurrentTheme(dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(current))->getText());
}

void MainWindow::currentTheme(const QString &text)
{
    ui->pushButton->setText(text);
}

// Event : Collapse/Expand Menu

void MainWindow::on_toggleMenu_clicked()
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

// Event : Remove item from Menu

void MainWindow::removeMenuItem(const QUuid &id)
{
    for (int i = 0; i < ui->listWidget->count(); i++) {
        QListWidgetItem* item = ui->listWidget->item(i);
        MenuItemWidget* itemWidget = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item));
        if (itemWidget->getID() == id){
            delete item;
            break;
        }
    }

    if(ui->listWidget->count() == 0)
    {
        auto defaultItem = new QListWidgetItem("No themes yet !");
        defaultItem->setFlags(defaultItem->flags() & ~Qt::ItemIsEnabled);
        ui->listWidget->addItem(defaultItem);
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "menuitemwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Collapse/Expand pushButton : vertical
    ui->toggleMenu->setOrientation(OrientablePushButton::VerticalBottomToTop);

    // Set item's icon size
    ui->listWidget->setIconSize(QSize(35,35));

    // Load themes
    m_themes = new Themes();
    ui->listWidget->clear();
    for(Theme *theme : m_themes->getThemes())
        displayTheme(theme);

    // Default menu item :
    if(ui->listWidget->count() == 0)
    {
        auto defaultItem = new QListWidgetItem("No themes yet !");
        defaultItem->setFlags(defaultItem->flags() & ~Qt::ItemIsEnabled);
        ui->listWidget->addItem(defaultItem);
    }

    // Drag & Drop
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setAcceptDrops(true);
    ui->listWidget->setDropIndicatorShown(true);
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);

    // Actions & Events

    // Self connections :
    connect(ui->actionCollapse_Expand_menu, SIGNAL(triggered()), this, SLOT(toggleMenu())); // toggle Menu
    connect(ui->actionCreate_new_theme, SIGNAL(triggered()), this, SLOT(createTheme())); // create Theme
    connect(ui->actionCreate_new_color, SIGNAL(triggered()), this, SLOT(transmitCreateColor())); // create Color
    connect(ui->actionSave_all, SIGNAL(triggered()), this, SLOT(saveAll())); // save Themes

    // ThemeWidget Signals :
    connect(this, SIGNAL(sendTheme()), ui->theme, SLOT(clearTheme())); // clear Theme
    connect(this, SIGNAL(sendTheme(Theme*)), ui->theme, SLOT(loadTheme(Theme*))); // load Theme
    connect(this, SIGNAL(sendCreateColor()), ui->theme, SLOT(createColor())); // create Color
    connect(this, SIGNAL(sendDiscardChanges()), ui->theme, SLOT(discardChanges())); // discard changes Theme
}

MainWindow::~MainWindow()
{
	delete ui;
}

/*****************************************/
/***             Methods               ***/
/*****************************************/

// Add an already existing Theme to the list menu
void MainWindow::displayTheme(Theme *theme)
{
    // Check if head is default and removes it
    if(ui->listWidget->count() == 1 && ui->listWidget->item(0)->text() == "No themes yet !")
        ui->listWidget->removeItemWidget(ui->listWidget->takeItem(0));

    // Get list item widget from an already existing theme
    auto widget = new MenuItemWidget(this);
    widget->setTheme(theme);

    // New list item
    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    item->setIcon(QIcon("../color-theme-manager/images/easteregg.png"));

    // Adding item + widget to list
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, widget);
}

// Checks if the selected theme was edited and suggest actions if so
int MainWindow::checkThemeChanges(Theme *theme)
{
    // If the theme has been edited without being saved
    if(theme->getEdited())
    {
        QMessageBox popup;
        popup.setWindowTitle("Saving");
        popup.setIcon(QMessageBox::Question);
        popup.setText(QString("Save the theme \"%1\"?").arg(theme->getName()));
        popup.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        int res = popup.exec();
        switch(res)
        {
            case QMessageBox::Cancel:
                break;
            case QMessageBox::Save:
                // TODO : save theme
                theme->setEdited(false);
                break;
            case QMessageBox::Discard:
                theme->setEdited(false);
                break;
        }
        return res;
    }

    // Nothing happened
    return -1;
}

/*****************************************/
/***         Self connections          ***/
/*****************************************/

// Event : New theme (Ctrl+Maj+N)
void MainWindow::createTheme()
{
    // Check if head is default and removes it
    if(ui->listWidget->count() == 1 && ui->listWidget->item(0)->text() == "No themes yet !")
        ui->listWidget->removeItemWidget(ui->listWidget->takeItem(0));

    // New list item widget
    auto widget = new MenuItemWidget(this);
    widget->setTheme("New theme");

    // New list item
    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    item->setIcon(QIcon("../color-theme-manager/images/easteregg.png"));

    // Adding item + widget to list
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, widget);

    // Sets the current item
    ui->listWidget->setCurrentItem(item);
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

// Calling => MainWindow::toggleMenu()
void MainWindow::on_toggleMenu_clicked()
{
    emit ui->actionCollapse_Expand_menu->trigger();
}

// Calling => ColorWidget::createColor()
void MainWindow::transmitCreateColor()
{
    // If default item is enabled : creating a new theme
    if(ui->listWidget->count() == 1 && ui->listWidget->item(0)->text() == "No themes yet !")
        createTheme();
    emit sendCreateColor();
}

// Event : Save all themes (Ctrl+Shift+S)
void MainWindow::saveAll()
{
    for(Theme *theme : m_themes->getThemes())
    {
        // TODO : save theme
    }
}

/*****************************************/
/***          ThemeWidget Slots        ***/
/*****************************************/

// Event : Switch current theme

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    // Default item is enabled
    if(current == nullptr)
    {
        emit sendTheme();
        return;
    }

    // Updates the ThemeWidget display with the current theme
    auto currentItem = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(current));
    emit sendTheme(currentItem->getTheme());
}

// Event : Remove item from Menu

void MainWindow::removeMenuItem(const QUuid &id)
{
    // Looking for the item's ID
    for (int i = 0; i < ui->listWidget->count(); i++) {

        // Cast item to theme
        QListWidgetItem* item = ui->listWidget->item(i);
        MenuItemWidget* itemWidget = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item));
        Theme *theme = itemWidget->getTheme();

        // Check if theme is corresponding
        if (theme->getID() == id){
            // Check if action is required
            auto res = checkThemeChanges(theme);
            if(res != QMessageBox::Cancel)
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "menuitemwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QIcon>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Collapse/Expand pushButton :
    ui->toggleMenu->setOrientation(OrientablePushButton::VerticalBottomToTop); // vertical
    ui->toggleMenu->setIcon(QIcon("../color-theme-manager/resource/icons/feather/corner-left-up.svg"));

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
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveCurrent())); // save Theme
    connect(ui->actionSave_all, SIGNAL(triggered()), this, SLOT(saveAllThemes())); // save Themes
    connect(ui->actionImport_theme, SIGNAL(triggered()), this, SLOT(importTheme())); // import Themes

    // ThemeWidget Signals :
    connect(this, SIGNAL(sendTheme()), ui->theme, SLOT(clearTheme())); // clear Theme
    connect(this, SIGNAL(sendTheme(Theme*)), ui->theme, SLOT(loadTheme(Theme*))); // load Theme
    connect(this, SIGNAL(sendCreateColor()), ui->theme, SLOT(createColor())); // create Color
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
    item->setIcon(QIcon("../color-theme-manager/resource/images/easteregg.png"));

    // Adding item + widget to list
    m_themes->addTheme(widget->getTheme());
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
        popup.setWindowIcon(QIcon("../color-theme-manager/resource/icons/feather/pen-tool.svg"));
        popup.setWindowTitle("Saving");
        popup.setIcon(QMessageBox::Question);
        popup.setText(QString("Save the theme \"%1\"?").arg(theme->getName()));
        popup.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        popup.setButtonText(QMessageBox::Discard, QString("Don't save"));

        int res = popup.exec();
        switch(res)
        {
            case QMessageBox::Cancel:
                break;
            case QMessageBox::Save:
                saveCurrent();
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
    item->setIcon(QIcon("../color-theme-manager/resource/images/easteregg.png"));

    // Adding item + widget to list
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, widget);

    // Sets the current item
    m_themes->addTheme(widget->getTheme());
    ui->listWidget->setCurrentItem(item);
}

void MainWindow::createTheme(Theme* theme)
{
    // Check if head is default and removes it
    if(ui->listWidget->count() == 1 && ui->listWidget->item(0)->text() == "No themes yet !")
        ui->listWidget->removeItemWidget(ui->listWidget->takeItem(0));

    // New list item widget
    auto widget = new MenuItemWidget(this);
    widget->setTheme(theme);

    // New list item
    auto item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    item->setIcon(QIcon("../color-theme-manager/resource/images/easteregg.png"));

    // Adding item + widget to list
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, widget);

    // Sets the current item
    m_themes->addTheme(widget->getTheme());
    ui->listWidget->setCurrentItem(item);
}

// Event : Collapse/Expand Menu (Ctrl+M)
void MainWindow::toggleMenu()
{
    if(ui->toggleMenu->text() == "Collapse")
    {
        ui->toggleMenu->setIcon(QIcon("../color-theme-manager/resource/icons/feather/corner-left-down.svg"));
        ui->toggleMenu->setText("Expand");
        ui->listWidget->setVisible(false);
    }
    else
    {
        ui->toggleMenu->setIcon(QIcon("../color-theme-manager/resource/icons/feather/corner-left-up.svg"));
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

// Save specified theme
void MainWindow::saveTheme(Theme *theme)
{
    // If path to file doesnt exists
    if(QFileInfo::exists(theme->getPath()) == false)
    {
        // Init dialog
        QFileDialog dialog(this);
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setNameFilter("XML File (*.xml)");
        QStringList fileNames;

        // Launch dialog
        if (dialog.exec())
            fileNames = dialog.selectedFiles();

        // No files selected
        if(fileNames.count() == 0)
            return;

        // Set path
        theme->setPath(fileNames.first());
    }

    // Open file
    QFile file(theme->getPath());
    if(!file.open(QIODevice::WriteOnly)) // default : QIODevice::Text
        return;

    // Generate XML
    QDomDocument doc;
    QDomElement colors = doc.createElement("colors");
    colors.setAttribute("name", theme->getName());
    doc.appendChild(colors);

    for(auto item : *(theme->getColorpairs()))
    {
        QDomElement color = doc.createElement("color");
        color.setAttribute("target", ColorPair::toRGBA(item->GetTarget()));
        color.setAttribute("source", ColorPair::toRGBA(item->GetSource()));
        color.setAttribute("id", item->GetName());
        colors.appendChild(color);
    }

    // Write to file
    QTextStream stream(&file);
    stream << doc.toString();

    // Close file
    file.close();

    theme->setEdited(false);
}

// Event : Save theme (Ctrl+S)
void MainWindow::saveCurrent()
{
    // Cast current item to theme
    QListWidgetItem* item = ui->listWidget->currentItem();
    MenuItemWidget* itemWidget = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item));
    saveTheme(itemWidget->getTheme());
}

// Event : Save all themes (Ctrl+Shift+S)
void MainWindow::saveAllThemes()
{
    for(Theme *theme : m_themes->getThemes())
        if(theme->getEdited())
            saveTheme(theme);
}

// Event : Import theme (Ctrl+I)
void MainWindow::importTheme()
{
    // Init dialog
    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setNameFilter("(*.xml)");
    QStringList fileNames;

    // Launch dialog
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    // No files selected
    if(fileNames.count() == 0)
        return;

    // Loads the first selected file
    auto xml = new XMLReader();
    int res = xml->read(fileNames.first());
    if(res == -1)
        return;

    // Insert loaded colorpairs in theme
    Theme *theme = new Theme(xml->getName());
    theme->setPath(fileNames.first());
    for(auto i : xml->getSet())
    {
        auto color = new ColorPair(i);
        theme->addColorpair(color);
    }

    // Display newly imported theme
    createTheme(theme);
    theme->setEdited(false);
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
    // Looking for the item's ID in menu
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
            {
                delete item;
                // Looking for the item's ID in themes
                for(auto theme : m_themes->getThemes())
                {
                    if(theme->getID() == id)
                        m_themes->removeTheme(theme);
                    break;
                }
            }
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

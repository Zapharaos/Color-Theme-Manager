#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "menuitemwidget.h"
#include <QTimer>
#include <QMovie>
#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>
#include <QIcon>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Loader
    QMovie *movie = new QMovie(":/res/resource/gifs/loader.gif");
    movie->setScaledSize(QSize(20,20));
    ui->loading->setMovie(movie);
    ui->loading->show();
    startLoading();

    // Collapse/Expand pushButton :
    ui->toggleMenu->setOrientation(OrientablePushButton::VerticalBottomToTop); // vertical
    ui->toggleMenu->setIcon(QIcon(":/res/resource/icons/feather/corner-left-up.svg"));

    // Set item's icon size
    ui->listWidget->setIconSize(QSize(35,35));

    ui->loading->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->loading->setContentsMargins(0,0,0,0);

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
    connect(ui->actionApply_theme, SIGNAL(triggered()), this, SLOT(applyTheme())); // apply Theme

    // ThemeWidget Signals :
    connect(this, SIGNAL(sendTheme()), ui->theme, SLOT(clearTheme())); // clear Theme
    connect(this, SIGNAL(sendTheme(Theme*)), ui->theme, SLOT(loadTheme(Theme*))); // load Theme
    connect(this, SIGNAL(sendCreateColor()), ui->theme, SLOT(createColor())); // create Color

    stopLoading();
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
    item->setIcon(QIcon(":/res/resource/images/easteregg.png"));

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
        popup.setWindowIcon(QIcon(":/res/resource/icons/feather/pen-tool.svg"));
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

// Close application : suggest to save the remaining themes
void MainWindow::closeEvent(QCloseEvent *event) {

    // Check if head is default : leave
    if(ui->listWidget->count() == 1 && ui->listWidget->item(0)->text() == "No themes yet !")
        return;

    // Looking for the item's ID in menu
    for (int i = 0; i < ui->listWidget->count(); i++) {

        // Cast item to theme
        QListWidgetItem* item = ui->listWidget->item(i);
        MenuItemWidget* itemWidget = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item));
        Theme *theme = itemWidget->getTheme();

        if(theme->getEdited() == false) continue;

        QMessageBox popup;
        popup.setWindowIcon(QIcon(":/res/resource/icons/feather/pen-tool.svg"));
        popup.setWindowTitle("Leaving");
        popup.setIcon(QMessageBox::Question);
        popup.setText(QString("Leave without saving?"));
        popup.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        int res = popup.exec();
        switch(res)
        {
            case QMessageBox::Yes:
                break;
            case QMessageBox::No:
                event->ignore();
                break;
        }
        return;
    }
}

void MainWindow::startLoading()
{
    ui->loading->movie()->start();
    ui->loading->setVisible(true);
}

void MainWindow::stopLoading()
{
    ui->loading->movie()->stop();
    ui->loading->setVisible(false);
}

void MainWindow::showDialog(QString title, QString text)
{
    popup = new QMessageBox(this);
    popup->setIcon(QMessageBox::NoIcon);
    popup->setWindowIcon(QIcon(":/res/resource/icons/feather/pen-tool.svg"));
    popup->setWindowTitle(title);
    popup->setText(text);

    popup->setStandardButtons(QMessageBox::Ok);
    popup->setAttribute(Qt::WA_DeleteOnClose); // delete pointer after close
    popup->setModal(false);
    popup->show();

    QTimer::singleShot(3000, popup, SLOT(close()));
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
    item->setIcon(QIcon(":/res/resource/images/easteregg.png"));

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
    item->setIcon(QIcon(":/res/resource/images/easteregg.png"));

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
        ui->toggleMenu->setIcon(QIcon(":/res/resource/icons/feather/corner-left-down.svg"));
        ui->toggleMenu->setText("Expand");
        ui->listWidget->setVisible(false);
    }
    else
    {
        ui->toggleMenu->setIcon(QIcon(":/res/resource/icons/feather/corner-left-up.svg"));
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
        {
            stopLoading();
            return;
        }

        // Set path
        theme->setPath(fileNames.first());
    }

    startLoading();

    // Open file
    QFile file(theme->getPath());
    if(!file.open(QIODevice::WriteOnly)) // default : QIODevice::Text
    {
        stopLoading();
        return;
    }

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

    // Looking for the item's ID in menu
    for (int i = 0; i < ui->listWidget->count(); i++) {

        // Cast item to theme
        QListWidgetItem* item = ui->listWidget->item(i);
        MenuItemWidget* itemWidget = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item));
        Theme *itemTheme = itemWidget->getTheme();

        // Check if theme is corresponding
        if (theme == itemTheme)
        {
            itemWidget->updateLabel();
            break;
        }
    }

    theme->setEdited(false);
    stopLoading();
}

// Event : Save theme (Ctrl+S)
void MainWindow::saveCurrent()
{
    // Check if head is default : nothing to save
    if(ui->listWidget->count() == 1 && ui->listWidget->item(0)->text() == "No themes yet !")
        return;

    // Cast current item to theme
    QListWidgetItem* item = ui->listWidget->currentItem();
    MenuItemWidget* itemWidget = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item));
    saveTheme(itemWidget->getTheme());
    showDialog("Popup", QString("The theme \"%1\" has been saved").arg(itemWidget->getTheme()->getName()));
}

// Event : Save all themes (Ctrl+Shift+S)
void MainWindow::saveAllThemes()
{
    for(Theme *theme : m_themes->getThemes())
        if(theme->getEdited())
            saveTheme(theme);
    showDialog("Popup", "All themes were saved");
}

// Event : Import theme (Ctrl+I)
void MainWindow::importTheme()
{
    // Init dialog
    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("(*.xml)");
    QStringList fileNames;

    // Launch dialog
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    // No files selected
    if(fileNames.count() == 0)
        return;

    startLoading();

    // Loads the first selected file
    auto xml = new XMLReader();
    int res = xml->read(fileNames.first());
    if(res == -1)
    {
        stopLoading();
        return;
    }

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
    stopLoading();
}

// Event : Apply theme (Ctrl+E)
void MainWindow::applyTheme()
{
    // Check if head is default : nothing to apply
    if(ui->listWidget->count() == 1 && ui->listWidget->item(0)->text() == "No themes yet !")
        return;

    // Init dialog
    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList fileNames;

    // Launch dialog
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    // No files selected
    if(fileNames.count() == 0)
        return;

    startLoading();

    // Cast current item to theme
    QListWidgetItem* item = ui->listWidget->currentItem();
    MenuItemWidget* itemWidget = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item));
    Theme *theme = itemWidget->getTheme();

    // Read the file
    QFile file(fileNames.first());
    if(!file.open(QIODevice::ReadWrite)) // default : QIODevice::Text
    {
        stopLoading();
        return;
    }
    QString text(file.readAll());

    // Replace each "source" occurrence by "target"
    for(auto color : *(theme->getColorpairs()))
        auto reg = text.replace(ColorPair::toRGBA(color->GetSource()), ColorPair::toRGBA(color->GetTarget())); // replace text in string

    // Update the file data
    file.seek(0);
    file.write(text.toUtf8());

    // Close file
    file.close();
    stopLoading();
    showDialog("Popup", QString("The theme \"%1\" has been applied").arg(theme->getName()));
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
void MainWindow::removeMenuItem(Theme *deleteTheme)
{
    startLoading();

    // Looking for the item's ID in menu
    for (int i = 0; i < ui->listWidget->count(); i++) {

        // Cast item to theme
        QListWidgetItem* item = ui->listWidget->item(i);
        MenuItemWidget* itemWidget = dynamic_cast<MenuItemWidget*>(ui->listWidget->itemWidget(item));
        Theme *theme = itemWidget->getTheme();

        // Check if theme is corresponding
        if (theme == deleteTheme){
            // Check if action is required
            auto res = checkThemeChanges(theme);
            if(res != QMessageBox::Cancel)
            {
                delete item;
                m_themes->removeTheme(theme);
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

    stopLoading();
}

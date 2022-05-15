#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Theme.h"
#include "Themes.h"
#include "XMLReader.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QUuid>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayTheme(Theme *theme);
    int checkThemeChanges(Theme *theme);

private:
    Ui::MainWindow *ui;
    Themes *m_themes;

signals:
    void sendTheme();
    void sendTheme(Theme *theme);
    void sendCreateColor();

private slots:
    // Self
    void createTheme();
    void createTheme(Theme *theme);
    void toggleMenu();
    void on_toggleMenu_clicked();
    void transmitCreateColor();
    void saveTheme();
    void saveAllThemes();
    void importTheme();

    // ThemeWidget
    void removeMenuItem(const QUuid &id);
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};
#endif // MAINWINDOW_H

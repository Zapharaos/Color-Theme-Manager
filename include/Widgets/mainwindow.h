#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Theme.h"
#include "Themes.h"

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

signals:
    void sendTheme();
    void sendTheme(Theme *theme);
    void sendCreateColor();
    void sendUndoChanges();

private:
	Ui::MainWindow *ui;
    Themes *m_themes;

private slots:
    void createTheme();
    int checkThemeChanges(Theme *theme);
    void transmitCreateColor();
    void removeMenuItem(const QUuid &id);
    void toggleMenu();
    void on_toggleMenu_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};
#endif // MAINWINDOW_H

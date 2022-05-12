#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

signals:
    void sendCurrentTheme(const QString &text);

private:
	Ui::MainWindow *ui;

private slots:
    void createTheme();
    void currentTheme(const QString &text);
    void removeMenuItem(const QUuid &id);
    void on_toggleMenu_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};
#endif // MAINWINDOW_H

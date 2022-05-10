#ifndef THEMESMENUWIDGET_H
#define THEMESMENUWIDGET_H

#include <QWidget>

#include <QLabel>
#include <QVBoxLayout>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class ThemesMenuWidget; }
QT_END_NAMESPACE

class ThemesMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThemesMenuWidget(QWidget *parent = nullptr);
    ~ThemesMenuWidget();

private:
    Ui::ThemesMenuWidget *ui;

private slots:
    void removeItem(const QString &text);

public slots:
    void on_toggleMenu_clicked();
};

#endif // THEMESMENUWIDGET_H

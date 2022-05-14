#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include "Theme.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuItemWidget; }
QT_END_NAMESPACE

class MenuItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuItemWidget(QWidget *parent = nullptr);
    ~MenuItemWidget();

    void setTheme(const QString &name);
    void setTheme(Theme *theme);
    Theme* getTheme();

private:
    Ui::MenuItemWidget *ui;
    Theme *m_theme;

signals:
    void sendRemoveItem(const QUuid &id);

private slots:
    void on_toolButton_clicked();
};

#endif // CUSTOMWIDGET_H

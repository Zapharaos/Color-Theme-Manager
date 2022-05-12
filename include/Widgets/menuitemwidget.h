#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

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

    void setText(const QString &text);
    QString getText();

signals:
    void sendRemoveItem(const QString &text);

private slots:
    void on_toolButton_clicked();

private:
    Ui::MenuItemWidget *ui;
};

#endif // CUSTOMWIDGET_H

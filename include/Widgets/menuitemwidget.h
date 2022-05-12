#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QUuid>

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
    void setID(const QUuid &id);
    QUuid getID();


signals:
    void sendRemoveItem(const QUuid &id);

private slots:
    void on_toolButton_clicked();

private:
    Ui::MenuItemWidget *ui;
    QUuid m_id;
};

#endif // CUSTOMWIDGET_H

#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CustomWidget; }
QT_END_NAMESPACE

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomWidget(QWidget *parent = nullptr);
    ~CustomWidget();

    void setText(const QString &text);
    QString getText();

signals:
    void sendRemoveItem(const QString &text);

private slots:
    void on_toolButton_clicked();

private:
    Ui::CustomWidget *ui;
};

#endif // CUSTOMWIDGET_H

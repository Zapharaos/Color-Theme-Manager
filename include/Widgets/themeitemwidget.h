#ifndef THEMEITEMWIDGET_H
#define THEMEITEMWIDGET_H

#include "colorpair.h"
#include <QWidget>

namespace Ui {
class ThemeItemWidget;
}

class ThemeItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeItemWidget(QWidget *parent = nullptr);
    ~ThemeItemWidget();

    void setColor(const ColorPair &colorPair);
    ColorPair* getColor();

signals:
    void sendRemoveColor(const QString colorID);

private:
    Ui::ThemeItemWidget *ui;
    ColorPair *m_color;

private slots:
    void loadColor(ColorPair *color);
    void on_deleteButton_clicked();
    void on_editButton_clicked();
};

#endif // THEMEITEMWIDGET_H

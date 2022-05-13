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

private:
    Ui::ThemeItemWidget *ui;
    ColorPair *m_color;

private slots:
    void loadColor(ColorPair *color);
};

#endif // THEMEITEMWIDGET_H

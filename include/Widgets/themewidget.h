#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include "Theme.h"

#include <QWidget>
#include <QUuid>

namespace Ui {
class ThemeWidget;
}

class ThemeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeWidget(QWidget *parent = nullptr);
    ~ThemeWidget();

private:
    Ui::ThemeWidget *ui;
    Theme* m_theme;
    QSize m_qsize;

private slots:
    void loadTheme(Theme *theme);
    void createColor();
    void removeColorItem(ColorPair *color);
};

#endif // THEMEWIDGET_H

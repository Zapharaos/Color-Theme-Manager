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
    Theme* m_baseTheme;
    QSize m_qsize;

private slots:
    void clearTheme();
    void loadTheme(Theme *theme);
    void undoChanges();
    void displayColor(ColorPair *color);
    void createColor();
    void removeColor(ColorPair *color);
    void updateColor(bool edited);
};

#endif // THEMEWIDGET_H

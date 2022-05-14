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

    // StyleSheet
    const QString nameStyleDefault = "padding: 2px; border-style: solid; border-width: 1px; border-color: black; font-size: 20px;";
    const QString nameStyleError = "background-color: #EBC4C4; border-color: red; padding: 2px; border-style: solid; border-width: 1px; font-size: 20px;";
    const QString colorpairStyleDefault = "QListWidget::item { background: #e5e5e5; border: 1px solid black; border-radius: 3px;}";

private:
    Ui::ThemeWidget *ui;
    Theme* m_theme;

private slots:
    // Theme
    void loadTheme(Theme *theme);
    void clearTheme();
    // Colors
    void displayColor(ColorPair *color);
    void createColor();
    void removeColor(ColorPair *color);
    void updateColor(bool edited);
    // Event
    void on_name_textChanged();
};

#endif // THEMEWIDGET_H

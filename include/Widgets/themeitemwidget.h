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

    static const QSize qsize;

    void setColor(const ColorPair &colorPair);
    ColorPair* getColor();

signals:
    void sendRemoveColor(ColorPair *color);

private:
    Ui::ThemeItemWidget *ui;
    ColorPair *m_color;

private slots:
    void loadColor(ColorPair *color);
    void on_deleteButton_clicked();
    void on_srcButton_clicked();
    void on_trgButton_clicked();
    void on_srcRgb_textChanged();
    void on_trgRgb_textChanged();
    void on_colorName_textChanged();
};

#endif // THEMEITEMWIDGET_H

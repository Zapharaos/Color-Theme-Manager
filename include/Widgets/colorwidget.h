#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include "colorpair.h"
#include <QWidget>

namespace Ui {
class ColorWidget;
}

class ColorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorWidget(QWidget *parent = nullptr);
    ~ColorWidget();

    static const QSize qsize;

    void setColor(ColorPair *colorPair);
    ColorPair* getColor();

signals:
    void sendRemoveColor(ColorPair *color);

private:
    Ui::ColorWidget *ui;
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

#endif // COLORWIDGET_H

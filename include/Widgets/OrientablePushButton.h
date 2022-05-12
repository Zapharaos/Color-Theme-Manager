/*
 * Source : https://stackoverflow.com/questions/53135674/how-to-create-a-vertical-rotated-button-in-qt-with-c
*/

#ifndef ORIENTABLEPUSHBUTTON_H
#define ORIENTABLEPUSHBUTTON_H

#include <QPushButton>

class OrientablePushButton : public QPushButton
{
    Q_OBJECT
public:
    enum Orientation {
        Horizontal,
        VerticalTopToBottom,
        VerticalBottomToTop
    };

    OrientablePushButton(QWidget * parent = nullptr);
    OrientablePushButton(const QString & text, QWidget *parent = nullptr);
    OrientablePushButton(const QIcon & icon, const QString & text, QWidget *parent = nullptr);

    QSize sizeHint() const;

    OrientablePushButton::Orientation orientation() const;
    void setOrientation(const OrientablePushButton::Orientation &orientation);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Orientation mOrientation = Horizontal;
};

#endif // ORIENTABLEPUSHBUTTON_H

//
// Created by matthieu on 10/02/2022.
//

#include "../include/colorpair.h"

ColorPair::ColorPair() {}

ColorPair::ColorPair(const QString &id) {
    this->m_id = id;
}

ColorPair::ColorPair(const ColorPair &color) {
    this->m_id = color.m_id;
    this->color1 = color.color1;
    this->color2 = color.color2;
}

ColorPair::ColorPair(const QString &id, const QColor &color1, const QColor &color2) {
    this->m_id = id;
    this->color1 = color1;
    this->color2 = color2;
}

QString ColorPair::toRGBA(const QColor &color) {
    return color.name() + QString::number(color.alpha(), 16);
}

QColor ColorPair::fromRGBA(const QString &colorStr) {
    bool ok;
    QColor color = QColor(colorStr.mid(0, 7));
    int alpha = colorStr.mid(7,8).toInt(&ok, 16);
    if(ok)
        color.setAlpha(alpha);
    return color;
}

const QString& ColorPair::get_id() const
{
    return m_id;
}


bool CompareColorPair::operator()(const ColorPair &color1, const ColorPair &color2)
{
    return color1.get_id().QString::compare(color2.get_id()) < 0; // Qt::CaseInsensitive
}


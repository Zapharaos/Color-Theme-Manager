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
    return color.name(QColor::HexArgb);
}

QColor ColorPair::fromRGBA(const QString &colorStr) {
    return QColor(colorStr);
}


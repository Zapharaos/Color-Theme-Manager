//
// Created by matthieu on 10/02/2022.
//

#include "../include/colorpair.h"

ColorPair::ColorPair() {}

ColorPair::ColorPair(const QString &id) {
    m_id = id;
}

ColorPair::ColorPair(const ColorPair &color) {
    m_id = color.m_id;
    color1 = color.color1;
    color2 = color.color2;
}

ColorPair::ColorPair(const QString &id, const QColor &color1, const QColor &color2) {
    m_id = id;
    color1 = color1;
    color2 = color2;
}

QString toRGBA(const QColor &color) {
    return color.name();
}

QColor fromRGBA(const QString &colorStr) {
    return QColor(colorStr);
}


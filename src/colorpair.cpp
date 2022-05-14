//
// Created by matthieu on 10/02/2022.
//

#include "../include/colorpair.h"

ColorPair::ColorPair() {}

ColorPair::ColorPair(const QString &name) {
    this->m_id = QUuid::createUuid();
    this->m_name = name;
}

ColorPair::ColorPair(const ColorPair &color) {
    this->m_id = color.m_id;
    this->m_name = color.m_name;
    this->m_source = color.m_source;
    this->m_target = color.m_target;
}

ColorPair::ColorPair(const QString &name, const QColor &source, const QColor &target) {
    this->m_id = QUuid::createUuid();
    this->m_name = name;
    this->m_source = source;
    this->m_target = target;
}

ColorPair::ColorPair(const QUuid &id, const QString &name, const QColor &source, const QColor &target) {
    this->m_id = id;
    this->m_name = name;
    this->m_source = source;
    this->m_target = target;
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

void ColorPair::SetSource(QColor source)
{
    this->m_source = source;
}
QColor ColorPair::GetSource() const
{
    return m_source;
}

void ColorPair::SetTarget(QColor target)
{
    this->m_target = target;
}
QColor ColorPair::GetTarget() const
{
    return m_target;
}

void ColorPair::SetName(QString name)
{
    this->m_name = name;
}
QString ColorPair::GetName() const
{
    return m_name;
}

void ColorPair::SetID(QUuid id)
{
    this->m_id = id;
}
QUuid ColorPair::GetID() const
{
    return m_id;
}


bool CompareColorPair::operator()(const ColorPair &color1, const ColorPair &color2) const
{
    return color1.GetName().QString::compare(color2.GetName()) < 0; // Qt::CaseInsensitive
    // return color1.id() < color2.id();
}


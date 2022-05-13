//
// Created by matthieu on 10/02/2022.
//

#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#define COLOR_THEME_MANAGER_COLORPAIR_H

#include <QUuid>
#include <QString>
#include <QColor>
#include <QDebug>

class ColorPair {

    private:
    QUuid m_id;
    QString m_name;
    QColor m_source;
    QColor m_target;

    public:
    ColorPair(); //constructeur vide
    ColorPair(const ColorPair &color); //con. par copie
    ColorPair(const QString &name, const QColor &source, const QColor &target);
    ColorPair(const QUuid &id, const QString &name, const QColor &source, const QColor &target);
    ColorPair(const QString &name); //con. initialisant uniquement l’identifiant

    void SetSource(QColor source);
    QColor GetSource() const;

    void SetTarget(QColor target);
    QColor GetTarget() const;

    void SetName(QString name);
    QString GetName() const;

    void SetID(QUuid id);
    QUuid GetID() const;

    static QString toRGBA(const QColor &color); // static
    static QColor fromRGBA(const QString &colorStr); // static
};

class CompareColorPair
{
    public:
    CompareColorPair() {}
    bool operator()(const ColorPair &color1, const ColorPair &color2) const;
};


#endif //COLOR_THEME_MANAGER_COLORPAIR_H

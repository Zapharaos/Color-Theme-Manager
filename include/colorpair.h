//
// Created by matthieu on 10/02/2022.
//

#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#define COLOR_THEME_MANAGER_COLORPAIR_H

#include <QString>
#include <QColor>
#include <QDebug>

class ColorPair {

    private:
    QString m_id;
    QColor color1;
    QColor color2;

    public:
    ColorPair(); //constructeur vide
    ColorPair(const ColorPair &color); //con. par copie
    ColorPair(const QString &id, const QColor &color1, const QColor &color2);
    ColorPair(const QString &id); //con. initialisant uniquement l’identifiant

    const QString& get_id() const;

    static QString toRGBA(const QColor &color); // static
    static QColor fromRGBA(const QString &colorStr); // static
};

class CompareColorPair
{
    public:
    CompareColorPair();
    bool operator()(const ColorPair &color1, const ColorPair &color2);
};


#endif //COLOR_THEME_MANAGER_COLORPAIR_H

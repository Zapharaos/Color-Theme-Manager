//
// Created by matthieu on 10/02/2022.
//

#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#define COLOR_THEME_MANAGER_COLORPAIR_H

#include <QString>
#include <QColor>

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

    QString toRGBA(const QColor &color); // static
    QColor fromRGBA(const QString &colorStr); // static
};

#endif //COLOR_THEME_MANAGER_COLORPAIR_H

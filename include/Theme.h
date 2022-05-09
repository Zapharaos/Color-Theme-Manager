#ifndef THEME_H
#define THEME_H

#include <set>
#include <QString>
#include <fstream>
#include <iostream>
using namespace std;

#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#include "colorpair.h"
#endif //COLOR_THEME_MANAGER_COLORPAIR_H

class Theme {

    using Set = std::set<ColorPair>;

    private:
    // id ?
    QString m_name;
    Set m_colorPairs;

    public:
    Theme(); //constructeur vide
    Theme(const Theme &theme); //con. par copie
    Theme(const QString &name, const Set &colorPairs);
    Theme(const QString &name); //con. initialisant uniquement le nom

    int ApplyColorPair(string filename, ColorPair color);
};

#endif // THEME_H

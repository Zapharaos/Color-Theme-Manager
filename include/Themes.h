//
// Created by matthieu on 09/05/2022.
//

#ifndef COLOR_THEME_MANAGER_THEMES_H
#define COLOR_THEME_MANAGER_THEMES_H

#include <QSet>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef THEME_H
#include "Theme.h"
#endif //THEME_H

class Themes {

    std::string const binary_file = "themes.bin";

    private:
    QSet<Theme*> m_themes;

    public:
    Themes(); //constructeur vide
    Themes(const Themes &themes); //con. par copie
    Themes(QSet<Theme*> themes); //con. initialisant uniquement le set

    QSet<Theme*> getThemes();

    int StoreInFile();
    std::pair<Themes,int> ReadFromFile();
};

#endif //COLOR_THEME_MANAGER_THEMES_H

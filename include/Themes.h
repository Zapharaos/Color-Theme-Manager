//
// Created by matthieu on 09/05/2022.
//

#ifndef COLOR_THEME_MANAGER_THEMES_H
#define COLOR_THEME_MANAGER_THEMES_H

#include <QList>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef THEME_H
#include "Theme.h"
#endif //THEME_H

class Themes {

    std::string const binary_file = "themes.bin";

    private:
    QList<Theme*> m_themes;

    public:
    Themes(); //constructeur vide
    Themes(const Themes &themes); //con. par copie
    Themes(QList<Theme*> themes); //con. initialisant uniquement le set

    QList<Theme*> getThemes();
    void addTheme(Theme *theme);
    void removeTheme(Theme *theme);

    int StoreInFile();
    std::pair<Themes,int> ReadFromFile();
};

#endif //COLOR_THEME_MANAGER_THEMES_H

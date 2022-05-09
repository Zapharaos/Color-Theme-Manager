//
// Created by matthieu on 09/05/2022.
//

#ifndef COLOR_THEME_MANAGER_THEMES_H
#define COLOR_THEME_MANAGER_THEMES_H

#include <set>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef THEME_H
#include "Theme.h"
#endif //THEME_H

class Themes {

    using Set = std::set<Theme>;
    std::string const binary_file = "themes.bin";

    private:
    Set m_themes;

    public:
    Themes(); //constructeur vide
    Themes(const Themes &themes); //con. par copie
    Themes(const Set &themes); //con. initialisant uniquement le set

    int StoreInFile();
    std::pair<Themes,int> ReadFromFile();
};

#endif //COLOR_THEME_MANAGER_THEMES_H

//
// Created by matthieu on 09/05/2022.
//

#include "../include/Themes.h"

Themes::Themes() {}

Themes::Themes(const Themes &themes)
{
    this->m_themes = themes.m_themes;
}

Themes::Themes(QList<Theme*> themes)
{
    this->m_themes = themes;
}

QList<Theme*> Themes::getThemes()
{
    return m_themes;
}

void Themes::addTheme(Theme *theme)
{
    m_themes.append(theme);
}

void Themes::removeTheme(Theme *theme)
{
    m_themes.removeOne(theme);
}

int Themes::StoreInFile()
{
    int error = 0;
    fstream themes_file;
    try {
        themes_file.open(binary_file, ios::trunc | ios::binary | ios::in | ios::out);
        themes_file.write(reinterpret_cast<char*>(&this->m_themes), sizeof(this->m_themes));
        themes_file.close();
    } catch (const std::system_error& e) {
        error = -1;
        themes_file.close();
        std::cerr << e.what() << " (" << e.code() << ")" << std::endl;
    }
    return error;
}

std::pair<Themes,int> Themes::ReadFromFile()
{
    int error = 0;
    Themes themes;
    fstream themes_file;
    try {
        themes_file.open(binary_file, ios::binary | ios::in | ios::out);
        themes_file.read(reinterpret_cast<char*>(&themes.m_themes), sizeof(themes.m_themes));
        themes_file.close();
    } catch (const std::system_error& e) {
        error = -1;
        themes_file.close();
        std::cerr << e.what() << " (" << e.code() << ")" << std::endl;
    }
    return make_pair(themes, error);
}


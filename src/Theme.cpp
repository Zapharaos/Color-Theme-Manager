//
// Created by matthieu on 09/05/2022.
//

#include "../include/Theme.h"
using namespace std;

Theme::Theme() {}

Theme::Theme(const QString &name)
{
    this->m_id = QUuid::createUuid();
    this->m_name = name;
}

Theme::Theme(const Theme &theme)
{
    this->m_id = theme.m_id;
    this->m_name = theme.m_name;
    this->m_colorPairs = theme.m_colorPairs;
}

Theme::Theme(const QUuid &id, const QString &name, const Set &colorPairs)
{
    this->m_id = id;
    this->m_name = name;
    this->m_colorPairs = colorPairs;
}

void Theme::setID(const QUuid &id) {
    this->m_id = id;
}

QUuid Theme::getID() {
    return m_id;
}

void Theme::setName(const QString &name) {
    this->m_name = name;
}

QString Theme::getName() {
    return m_name;
}

void ReplaceAll(string &line, string source, string target)
{
    size_t pos = line.find(source);
    while(pos != std::string::npos)
    {
        line.replace(pos, source.size(), target);
        pos = line.find(source, pos + target.size());
    }
}

int Theme::ApplyColorPair(std::string filename, ColorPair color)
{
    int error = 0;
    fstream file;

    string target = ColorPair::toRGBA(color.GetTarget()).toUtf8().constData();
    string source_rgba = ColorPair::toRGBA(color.GetSource()).toUtf8().constData(); // #rrggbbaa
    string source_rgb = source_rgba.substr(0, source_rgba.length()-3); // #rrggbb

    try {
        file.open(filename.c_str(), ios::in|ios::out|ios::binary);

        string line;
        while(getline(file, line))
        {
            // try/catch ReplaceAll ?
            ReplaceAll(line, source_rgba, target);
            ReplaceAll(line, source_rgb, target);
        }

        file.close();
    } catch (const std::system_error& e) {
        error = -1;
        file.close();
        std::cerr << e.what() << " (" << e.code() << ")" << std::endl;
    }

    return error;
}

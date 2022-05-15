#ifndef THEME_H
#define THEME_H

#include <QList>
#include <QUuid>
#include <QString>
#include <fstream>
#include <iostream>
using namespace std;

#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#include "colorpair.h"
#endif //COLOR_THEME_MANAGER_COLORPAIR_H

class Theme {

    private:
    QUuid m_id;
    QString m_name;
    QList<ColorPair*> *m_colorPairs;
    bool m_edited = false;

    public:
    Theme(); //constructeur vide
    Theme(const Theme &theme); //con. par copie
    Theme(const QUuid &id, const QString &name, QList<ColorPair*> *colorPairs);
    Theme(const QString &name, QList<ColorPair*> *colorPairs); //con. initialisant uniquement le nom et le set
    Theme(const QString &name); //con. initialisant uniquement le nom

    void setID(const QUuid &id);
    QUuid getID();

    void setName(const QString &name);
    QString getName();

    QList<ColorPair*> *getColorpairs();
    void addColorpair(ColorPair* colorpair);

    void setEdited(const bool &edited);
    bool getEdited();

    int ApplyColorPair(string filename, ColorPair color);
};

#endif // THEME_H

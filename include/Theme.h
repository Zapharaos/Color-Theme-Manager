#ifndef THEME_H
#define THEME_H

#include <set>
#include <QSet>
#include <QUuid>
#include <QString>
#include <fstream>
#include <iostream>
using namespace std;

#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#include "colorpair.h"
#endif //COLOR_THEME_MANAGER_COLORPAIR_H

QT_BEGIN_NAMESPACE
namespace Ui { class MenuItemWidget; }
QT_END_NAMESPACE

class Theme {

    using Set = std::set<ColorPair*>;

    private:
    QUuid m_id;
    QString m_name;
    QSet<ColorPair*> *m_colorPairs;

    public:
    Theme(); //constructeur vide
    Theme(const Theme &theme); //con. par copie
    Theme(const QUuid &id, const QString &name, QSet<ColorPair*> *colorPairs);
    Theme(const QString &name); //con. initialisant uniquement le nom

    void setID(const QUuid &id);
    QUuid getID();

    void setName(const QString &name);
    QString getName();

    QSet<ColorPair*> *getColorpairs();

    int ApplyColorPair(string filename, ColorPair color);
};

#endif // THEME_H

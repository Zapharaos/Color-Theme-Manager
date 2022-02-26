#ifndef XMLREADER_H
#define XMLREADER_H

#include <set>
#include <QFile>
#include <QDomDocument>

#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#include "colorpair.h"
#endif //COLOR_THEME_MANAGER_COLORPAIR_H

class XMLReader {
    public:
    using Set = std::set<ColorPair, CompareColorPair>;
    XMLReader();
    XMLReader(XMLReader::Set &set);
    int read(const QString &path);

    private:
    Set m_set;
};

#endif // XMLREADER_H

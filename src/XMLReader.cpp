#include "../include/XMLReader.h"

XMLReader::XMLReader() {}

XMLReader::XMLReader(XMLReader::Set &set) {
    this->m_set = set;
}

XMLReader::Set XMLReader::getSet()
{
    return m_set;
}

QString XMLReader::getName()
{
    return m_name;
}

int XMLReader::read(const QString &path) {

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) // default : QIODevice::Text
        return -1;

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return -1;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();

    // Get theme name
    m_name = docElem.toElement().attribute("name");
    if(m_name.isEmpty())
        m_name = "New theme";

    // Get theme colorpairs
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            auto color = ColorPair(e.attribute("id"), e.attribute("source"), e.attribute("target"));
            m_set.insert(color);
        }
        n = n.nextSibling();
    }

    return 0;
}

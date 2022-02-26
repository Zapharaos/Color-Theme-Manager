#include "../include/XMLReader.h"

XMLReader::XMLReader() {}

XMLReader::XMLReader(XMLReader::Set &set) {
    this->m_set = set;
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

    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            m_set.insert(ColorPair(e.attribute("id"), e.attribute("source"), e.attribute("target")));
        }
        n = n.nextSibling();
    }

    return 0;
}

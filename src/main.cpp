#include "mainwindow.h"
#include <QApplication>

#include <QDebug>

#include "include/colorpair.h"
#include "include/XMLReader.h"

int main(int argc, char *argv[])
{
    QString path = QString("../color-theme-manager/themes/darkTheme.xml");
    if(XMLReader::read(path) == -1)
        qDebug() << "error: open"; // insert error handle

    QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

#include "mainwindow.h"
#include <QApplication>

#include <QDebug>

#include "include/colorpair.h"
#include "include/XMLReader.h"

int main(int argc, char *argv[])
{
    /*QString path = QString("../color-theme-manager/themes/darkTheme.xml");
    XMLReader reader;
    if(reader.read(path) == -1)
        qDebug() << "error XMLReader::read()";
        // TODO : insert some error handle*/

    QApplication a(argc, argv);
	MainWindow w;
    w.setWindowTitle("Themes Manager");
    w.setMinimumSize(800, 600);
    w.setWindowState(Qt::WindowMaximized);
	w.show();
	return a.exec();
}

#include "mainwindow.h"
#include <QApplication>

#include "include/colorpair.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QString color = "#11e0117f";
    qDebug() << color;

    QColor test = ColorPair::fromRGBA(color);
    color = ColorPair::toRGBA(test);

    qDebug() << test;
    qDebug() << color;

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

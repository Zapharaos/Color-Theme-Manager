#include "mainwindow.h"
#include <QApplication>

#include <QDebug>

#include "include/colorpair.h"
#include "include/XMLReader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	MainWindow w;
    w.setWindowTitle("Themes Manager");
    w.setMinimumSize(800, 600);
    w.setWindowState(Qt::WindowMaximized);
    w.setWindowIcon(QIcon("../color-theme-manager/resource/icons/feather/pen-tool.svg"));
	w.show();
	return a.exec();
}

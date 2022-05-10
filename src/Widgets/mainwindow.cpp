#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "themesmenuwidget.h"

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->SideMenu->addWidget(new ThemesMenuWidget());
}

MainWindow::~MainWindow()
{
	delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <libwinapi/lib.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    auto openWindows = libwinapi::get_open_windows();
    auto text = QString("There are currentyl %1 windows open!").arg(openWindows.at(0).title);
    QMessageBox msg;

    msg.setText(text);
    msg.setInformativeText("Magic number from libwinapi :D!");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setDefaultButton(QMessageBox::Ok);
    msg.exec();
}

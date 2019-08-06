#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <optional>

using Win32Error = libwinapi::errors::Win32Error;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	Win32Error  err;
	QString     message;
	QMessageBox msg;
    auto        result = libwinapi::get_open_windows(err);

	if (err) {
		msg.setText(err.message());
        msg.setInformativeText("Error!");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        return;
	} else if (!result) {
		msg.setText("No windows open!");
		msg.setInformativeText("Magic number from libwinapi :D!");
		msg.setStandardButtons(QMessageBox::Ok);
		msg.setDefaultButton(QMessageBox::Ok);
		msg.exec();
		return;
	}

	auto windows = result.value();
    ui->listWindows->clear();

    for(auto& item: windows) {
        auto value = QString::fromWCharArray(item.title.data(), item.title.size());
        ui->listWindows->addItem(value);
    }
}

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
	setupMenuBar();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setupMenuBar()
{
	fileMenu       = menuBar()->addMenu(tr("&File"));
	settingsAction = new QAction(tr("Settings"), this);
	exitAction     = new QAction(tr("E&xit"), this);

	connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettingsClick);
	connect(exitAction, &QAction::triggered, this, &MainWindow::onExitClick);

	fileMenu->addAction(settingsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

void MainWindow::on_pushButton_clicked()
{
	Win32Error  err;
	QString     message;
	QMessageBox msg;
	auto        result = winService.get_open_windows(err);

	if (err) {
		msg.setText(err.message());
		msg.setInformativeText("Error!");
		msg.setStandardButtons(QMessageBox::Ok);
		msg.setDefaultButton(QMessageBox::Ok);
		msg.exec();
		return;
	} else if (!result) {
		msg.setText("No windows open!");
		msg.setInformativeText("Error!");
		msg.setStandardButtons(QMessageBox::Ok);
		msg.setDefaultButton(QMessageBox::Ok);
		msg.exec();
		return;
	}

	auto titles = result.value();
	ui->listWindows->clear();

	for (const auto& title : titles) {
		const auto value = QString::fromWCharArray(title.text.data(), title.length);
		ui->listWindows->addItem(value);
	}
}

void MainWindow::onSettingsClick()
{
}

void MainWindow::onExitClick()
{
	close();
}

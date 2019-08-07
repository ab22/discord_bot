#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <libwinapi/lib.hpp>
#include <vector>

using libwinapi::models::WindowTitle;
using libwinapi::services::WinService;

namespace Ui {
	class MainWindow;
}

class MainWindow: public QMainWindow {
	Q_OBJECT

  public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

  private slots:
	void on_pushButton_clicked();

  private:
	Ui::MainWindow*          ui;
	WinService               winService;
	QMenu*                   fileMenu;
	QAction*                 settingsAction;
	QAction*                 exitAction;
	std::vector<WindowTitle> openWindows;

	void setupMenuBar();

	// Menu Events
	void onSettingsClick();
	void onExitClick();
};

#endif // MAINWINDOW_H

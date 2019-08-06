#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <libwinapi/lib.hpp>
#include <vector>

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
    Ui::MainWindow*                            ui;
    QMenu*                                     fileMenu;
    QAction*                                   settingsAction;
    QAction*                                   exitAction;
    std::vector<libwinapi::models::WindowInfo> openWindows;

    void setupMenuBar();

    // Menu Events
    void onSettingsClick();
    void onExitClick();
};

#endif // MAINWINDOW_H

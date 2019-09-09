#include "mainwindow.h"
#include <QApplication>
#include <QDirIterator>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QtDebug>

bool loadTheme(QApplication& app, const char* themeName)
{
	QFile f(themeName);

	if (!f.exists())
		return false;

	f.open(QFile::ReadOnly | QFile::Text);
	QTextStream stream(&f);

	app.setStyleSheet(stream.readAll());
	return true;
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
    MainWindow   w;

    if (!loadTheme(app, ":qdarkstyle/style.qss"))
        qDebug() << "Could not open theme file!";

	w.show();

	return app.exec();
}

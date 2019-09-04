#include "mainwindow.h"
#include <QApplication>
#include <QDirIterator>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QtDebug>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow   w;
	QFile        f(":qdarkstyle/style.qss");

	if (!f.exists()) {
		qDebug() << "Could not open theme file!";
	} else {
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		app.setStyleSheet(ts.readAll());
    }

	w.show();

	return app.exec();
}

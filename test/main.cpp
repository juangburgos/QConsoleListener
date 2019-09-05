#include <QCoreApplication>
#include <QDebug>

#include <QConsoleListener>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	// listen to console input
	QConsoleListener console;
	QObject::connect(&console, &QConsoleListener::newLine, 
	[&a](const QString &strNewLine) {
		qDebug() << "Echo :" << strNewLine;
		// quit
		if (strNewLine.compare("q", Qt::CaseInsensitive) == 0)
		{
			qDebug() << "Goodbye";
			a.quit();
		}
	});

	qDebug() << "Listening to console input:";
    return a.exec();
}

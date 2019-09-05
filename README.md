# QConsoleListener

Small Qt library to handle console input asynchronously using signals and slots. Based on [gjorquera's snippet](https://gist.github.com/gjorquera/2576569).

## Usage

Add to project in `*.pro` file

```qmake
include($$PWD/src/qconsolelistener.pri)
```

Include the header `#include <QConsoleListener>` and connect to the `QConsoleListener::newLine` signal. For example:

```c++
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
```

# References

* <https://gist.github.com/gjorquera/2576569>


#include <iostream>
#include "qconsolelistener.h"

QConsoleListener::QConsoleListener()
{
	QObject::connect(
		this, &QConsoleListener::finishedGetLine,
		this, &QConsoleListener::on_finishedGetLine, 
		Qt::QueuedConnection
	);
#ifdef Q_OS_WIN
	m_notifier = new QWinEventNotifier(GetStdHandle(STD_INPUT_HANDLE));
#else
    m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read);
#endif 
	// NOTE : move to thread because std::getline blocks, 
	//        then we sync with main thread using a QueuedConnection with finishedGetLine
	m_notifier->moveToThread(&m_thread);
	QObject::connect(
		&m_thread , &QThread::finished,
		m_notifier, &QObject::deleteLater
	);
#ifdef Q_OS_WIN
	QObject::connect(m_notifier, &QWinEventNotifier::activated,
#else
	QObject::connect(m_notifier, &QSocketNotifier::activated,
#endif 
	[this]() {
		std::string line;
		std::getline(std::cin, line);
		QString strLine = QString::fromStdString(line);
		Q_EMIT this->finishedGetLine(strLine);
	});
	m_thread.start();
}

void QConsoleListener::on_finishedGetLine(const QString &strNewLine)
{
	Q_EMIT this->newLine(strNewLine);
}

QConsoleListener::~QConsoleListener()
{
	m_thread.quit();
	m_thread.wait();
}

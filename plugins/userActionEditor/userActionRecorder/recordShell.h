#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

#include "recordSign.h"

namespace userAction {


class RecordShell : public QWidget
{
	Q_OBJECT

public:
	explicit RecordShell(QWidget *parent = 0);

signals:
	void hintAdded(QString const &message);

private slots:
	void addHintEvent();

private:
	QHBoxLayout *mLayout;
	QPushButton *mAddHint;
	QTextEdit *mHint;
	RecordSign *mRecordSign;

};
}

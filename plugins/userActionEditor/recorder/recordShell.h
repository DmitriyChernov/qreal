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

private:
	RecordSign *mRecordSign;

};
}

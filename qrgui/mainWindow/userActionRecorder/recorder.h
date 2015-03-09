#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QWidget>

#include "recordSign.h"

namespace qReal {

namespace gui {

class MainWindow;

/// Represents recorder of user actions.
class Recorder : public QObject
{
	Q_OBJECT

public:
	Recorder();

	void init (MainWindow *mainWindow);
	void start ();

private:
	MainWindow *mMainWindow;
	RecordSign *mRecordSign;
};

}
}

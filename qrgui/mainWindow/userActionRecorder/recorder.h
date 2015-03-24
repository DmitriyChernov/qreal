#pragma once

#include <QtWidgets/QWidget>
#include <QtXml/QDomDocument>

#include "recordSign.h"

namespace qReal {

namespace gui {

/// Represents recorder of user actions.
class Recorder : public QObject
{
	Q_OBJECT

public:
	Recorder();

	void init(MainWindow *mainWindow);
	void start();
	void stop();

public slots:
	void lowLevelEvent(QObject *obj, QEvent *e);

private:
	void addParentChain(QDomElement &event, QWidget *widget);

	MainWindow *mMainWindow;
	RecordSign *mRecordSign;
	QDomDocument mUserActioDomDocument;
	QDomElement mRootElement;
};

}
}

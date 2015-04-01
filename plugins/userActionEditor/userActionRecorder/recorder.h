#pragma once

#include <qrgui/plugins/toolPluginInterface/toolPluginInterface.h>
#include <qrgui/plugins/toolPluginInterface/pluginConfigurator.h>
#include <qrgui/plugins/toolPluginInterface/hotKeyActionInfo.h>
#include <QtWidgets/QWidget>
#include <QtXml/QDomDocument>

#include "recordSign.h"

namespace userAction {

class RecorderSign;

class UserActionRecorderPlugin : public QObject, public qReal::ToolPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(qReal::ToolPluginInterface)
	Q_PLUGIN_METADATA(IID "qRealRobots.UserActionRecorderPlugin")

public:
	/// Constructor. Creates plugin in uninitialized state, "init" shall be called before plugin can do anything useful.
	UserActionRecorderPlugin();
	~UserActionRecorderPlugin();

	void init(qReal::PluginConfigurator const &configurator) override;
	QList<qReal::ActionInfo> actions() override;  // Does not transfer ownership of QAction objects.
	QList<qReal::HotKeyActionInfo> hotKeyActions() override;  // Does not transfer ownership of QAction objects.

	void start();
	void stop();

public slots:
	void lowLevelEvent(QObject *obj, QEvent *e);

private:
	void addParentChain(QDomElement *event, QWidget *widget);

	QAction *mStartAction;  // Transfers ownership to QObject parent-child system
	QAction *mStopAction;  // Transfers ownership to QObject parent-child system

	QWidget *mMainWindow;
	RecordSign *mRecordSign;
	QDomDocument mUserActioDomDocument;
	QDomElement mRootElement;

	bool mIsRecording;
};

}

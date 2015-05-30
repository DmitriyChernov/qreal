#pragma once

#include <generatorBase/robotsGeneratorPluginBase.h>

namespace userAction {

/// Generation of QtScript program for TRIK, uploading and execution of a program.
/// Uses setting "tcpServer" from RobotsInterpreter.
class UserActionGeneratorPlugin : public generatorBase::RobotsGeneratorPluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "userActionGeneratorPlugin")

public:
	UserActionGeneratorPluginPlugin();
	~UserActionGeneratorPlugin() override;

	void init(const kitBase::KitPluginConfigurator &configurator) override;

	QList<qReal::ActionInfo> customActions() override;
	QList<qReal::HotKeyActionInfo> hotKeyActions() override;
	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

protected:
	generatorBase::MasterGeneratorBase *masterGenerator() override;
	QString defaultFilePath(const QString &projectName) const override;
	qReal::text::LanguageInfo language() const override;
	QString generatorName() const override;

private:
	QAction *mGenerateCodeAction;
	QAction *mStartRecordAction;
	QAction *mStopRecordAction;
};

}

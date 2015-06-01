#pragma once

#include <generatorBase/robotsGeneratorPluginBase.h>

#include "userActionBlockFactory.h"
#include "noRobotModel.h"

namespace userAction {

/// Generation of QtScript program for TRIK, uploading and execution of a program.
/// Uses setting "tcpServer" from RobotsInterpreter.
class UserActionGeneratorPlugin : public generatorBase::RobotsGeneratorPluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "userActionGeneratorPlugin")

public:
	UserActionGeneratorPlugin();
	~UserActionGeneratorPlugin() override;

	void init(const kitBase::KitPluginConfigurator &configurator) override;

	QList<qReal::ActionInfo> customActions() override;
	QList<qReal::HotKeyActionInfo> hotKeyActions() override;
	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

	QString kitId() const override;

	QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;
	kitBase::blocksBase::BlocksFactoryInterface *blocksFactoryFor(
			const kitBase::robotModel::RobotModelInterface *model) override;

	QList<kitBase::AdditionalPreferences *> settingsWidgets() override;

protected:
	generatorBase::MasterGeneratorBase *masterGenerator() override;
	QString defaultFilePath(const QString &projectName) const override;
	qReal::text::LanguageInfo language() const override;
	QString generatorName() const override;

	void regenerateExtraFiles(const QFileInfo &newFileInfo) override;

private:
	UserActionBlockFactory *mBlocksFactory;
	QScopedPointer<NoRobotModel> mRobotModel;
	QAction *mGenerateCodeAction;
	QAction *mStartRecordAction;
	QAction *mStopRecordAction;
};

}

#include "ev3KitInterpreterPlugin.h"

#include <QtWidgets/QApplication>

using namespace ev3;
using namespace qReal;

const Id robotDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "RobotsDiagramNode");
const Id subprogramDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "SubprogramDiagram");

Ev3KitInterpreterPlugin::Ev3KitInterpreterPlugin()
		: mRealRobotModel(kitId(), "ev3robot") // todo: somewhere generate robotId for each robot
		, mBlocksFactory(new blocks::Ev3BlocksFactory)
{
	mAdditionalPreferences = new Ev3AdditionalPreferences(mRealRobotModel.name());

	connect(mAdditionalPreferences, &Ev3AdditionalPreferences::settingsChanged
		, &mRealRobotModel, &robotModel::real::RealRobotModel::rereadSettings);

}

QString Ev3KitInterpreterPlugin::kitId() const
{
	return "ev3Kit";
}

QString Ev3KitInterpreterPlugin::friendlyKitName() const
{
	return tr("Lego EV3");
}

QList<kitBase::robotModel::RobotModelInterface *> Ev3KitInterpreterPlugin::robotModels()
{
	return  {&mRealRobotModel};
}

kitBase::blocksBase::BlocksFactoryInterface *Ev3KitInterpreterPlugin::blocksFactoryFor(
		const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model)
	return mBlocksFactory;
}

QList<kitBase::AdditionalPreferences *> Ev3KitInterpreterPlugin::settingsWidgets()
{
	return { mAdditionalPreferences };
}

QList<qReal::ActionInfo> Ev3KitInterpreterPlugin::customActions()
{
	return {};
}

QList<qReal::HotKeyActionInfo> Ev3KitInterpreterPlugin::hotKeyActions()
{
	return {};
}

QIcon Ev3KitInterpreterPlugin::iconForFastSelector(
		const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)
	return QIcon();
}

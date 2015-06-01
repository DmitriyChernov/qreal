#include "noRobotModel.h"

using namespace userAction;

NoRobotModel::NoRobotModel(const QString &kitId, const QString &robotId)
	: CommonRobotModel(kitId, "")
{
	Q_UNUSED(robotId);
}

QString NoRobotModel::name() const
{
	return "NoRobotModel";
}

QString NoRobotModel::friendlyName() const
{
	return tr("No robot model");
}

bool NoRobotModel::needsConnection() const
{
	return false;
}

int NoRobotModel::priority() const
{
	return 5;
}

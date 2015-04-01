#include "nxtGeneratorRobotModel.h"

using namespace nxt::robotModel;

NxtGeneratorRobotModel::NxtGeneratorRobotModel(const QString &kitId
		, const QString &robotId
		, const QString &name
		, const QString &friendlyName
		, int priority)
	: NxtRobotModelBase(kitId, robotId)
	, mName(name)
	, mFriendlyName(friendlyName)
	, mPriority(priority)
{
}

QString NxtGeneratorRobotModel::name() const
{
	return mName;
}

QString NxtGeneratorRobotModel::friendlyName() const
{
	return mFriendlyName;
}

bool NxtGeneratorRobotModel::needsConnection() const
{
	return false;
}

bool NxtGeneratorRobotModel::interpretedModel() const
{
	return false;
}

int NxtGeneratorRobotModel::priority() const
{
	return mPriority;
}

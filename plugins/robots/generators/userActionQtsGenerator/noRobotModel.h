#pragma once

#include <kitBase/robotModel/commonRobotModel.h>

namespace userAction {

class NoRobotModel : public kitBase::robotModel::CommonRobotModel
{
	Q_OBJECT

public:
	explicit NoRobotModel(const QString &kitId, const QString &robotId);

	QString name() const override;
	QString friendlyName() const override;
	bool needsConnection() const override;
	int priority() const override;

};

}

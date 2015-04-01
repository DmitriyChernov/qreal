#pragma once

#include <trikKit/robotModel/parts/trikObjectSensor.h>
#include <utils/tcpRobotCommunicator.h>

namespace trik {
namespace robotModel {
namespace real {
namespace parts {

/// Stub for TRIK color sensor for interpreter.
class ObjectSensor : public robotModel::parts::TrikObjectSensor
{
	Q_OBJECT

public:
	ObjectSensor(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, utils::TcpRobotCommunicator &robotCommunicator);

	void init() override;
	void detect() override;
	void read() override;

private:
	utils::TcpRobotCommunicator &mRobotCommunicator;
};

}
}
}
}

#pragma once

#include "scalarSensor.h"
#include "kitBase/kitBaseDeclSpec.h"

namespace kitBase {
namespace robotModel {
namespace robotParts {

/// Button on a control block of a robot.
class ROBOTS_KIT_BASE_EXPORT Button : public ScalarSensor
{
	Q_OBJECT
	Q_CLASSINFO("name", "button")
	Q_CLASSINFO("friendlyName", tr("Button"))

public:
	/// Constructor, takes device type info and predefined port on which this button is configured.
	Button(const DeviceInfo &info, const PortInfo &port);
};

}
}
}

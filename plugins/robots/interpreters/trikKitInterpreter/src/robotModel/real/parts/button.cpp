#include "button.h"

using namespace trikKitInterpreter::robotModel::real::parts;
using namespace interpreterBase::robotModel;

Button::Button(DeviceInfo const &info, PortInfo const &port)
	: robotParts::Button(info, port)
{
}

void Button::read()
{
	emit newData(1);
}

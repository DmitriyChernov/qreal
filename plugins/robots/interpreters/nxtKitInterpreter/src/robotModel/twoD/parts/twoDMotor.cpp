#include "twoDMotor.h"

using namespace nxt::robotModel::twoD::parts;

TwoDMotor::TwoDMotor(const kitBase::robotModel::DeviceInfo &info
		, const kitBase::robotModel::PortInfo &port
		, twoDModel::engine::TwoDModelEngineInterface &engine)
	: NxtMotor(info, port)
	, mEngine(engine)
{
}

void TwoDMotor::on(int speed, unsigned long degrees, bool breakMode)
{
	NxtMotor::on(speed, degrees, breakMode);
	mEngine.setNewMotor(speed, degrees, port(), breakMode);
}

void TwoDMotor::stop(bool breakMode)
{
	on(0, 0, breakMode);
}

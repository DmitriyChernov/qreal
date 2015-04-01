#pragma once

#include <QtGui/QColor>

#include <twoDModel/engine/twoDModelEngineInterface.h>
#include <trikKit/robotModel/parts/trikLineSensor.h>

namespace trik {
namespace robotModel {
namespace twoD {
namespace parts {

/// Stub for TRIK color sensor for interpreter.
/// Does nothing until line sensor emulation will be requested for 2D model.
class LineSensor : public robotModel::parts::TrikLineSensor
{
	Q_OBJECT

public:
	LineSensor(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port, twoDModel::engine::TwoDModelEngineInterface &engine);

	void init() override;
	void detectLine() override;
	void read() override;

private:
	bool closeEnough(const QColor &color) const;

	twoDModel::engine::TwoDModelEngineInterface &mEngine;
	QColor mLineColor;
};

}
}
}
}

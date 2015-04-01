#include "interpreterCore/managers/graphicsWatcherManager.h"

using namespace interpreterCore;
using namespace utils;
using namespace kitBase::robotModel;

GraphicsWatcherManager::GraphicsWatcherManager(const qrtext::DebuggerInterface &parser, QObject *parent)
	: QObject(parent)
	, mWatcher(new sensorsGraph::SensorsGraph(parser))
{
	mWatcher->setStartStopButtonsVisible(false);
}

QWidget *GraphicsWatcherManager::widget()
{
	return mWatcher;
}

void GraphicsWatcherManager::forceStart()
{
	mWatcher->startJob();
}

void GraphicsWatcherManager::forceStop()
{
	mWatcher->stopJob();
}

void GraphicsWatcherManager::onDeviceConfigurationChanged(const QString &robotModel
		, const PortInfo &port, const DeviceInfo &sensor, Reason reason)
{
	Q_UNUSED(port)
	Q_UNUSED(sensor)
	Q_UNUSED(reason)

	updateSensorsList(robotModel);
}

void GraphicsWatcherManager::updateSensorsList(const QString &currentRobotModel)
{
	mWatcher->clearTrackingObjects();
	int index = 0;
	for (const PortInfo &port : configuredPorts(currentRobotModel)) {
		const DeviceInfo device = currentConfiguration(currentRobotModel, port);
		/// @todo It must depend on port, port must return its variable
		const QString variableName = port.reservedVariable();
		if (!device.isNull() && !variableName.isEmpty()) {
			mWatcher->addTrackingObject(index, variableName, QString("%1: %2").arg(port.name(), device.friendlyName()));
			++index;
		}
	}
}

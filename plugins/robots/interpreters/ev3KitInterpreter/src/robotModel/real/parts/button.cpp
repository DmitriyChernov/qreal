#include "button.h"

#include "src/commandConstants.h"

const unsigned buttonResponseSize = 6;

using namespace ev3::robotModel::real::parts;
using namespace kitBase::robotModel;

Button::Button(const DeviceInfo &info, const PortInfo &port
		, utils::robotCommunication::RobotCommunicator &robotCommunicator)
	: robotParts::Button(info, port)
	, mRobotCommunicator(robotCommunicator)
{
}

void Button::read()
{
	const int size = 13;
	QByteArray command(size, 0);
	command[0] = size - 2;
	command[1] = size >> 8;
	command[2] = 4;
	command[3] = 0;
	command[4] = DIRECT_COMMAND_REPLY;
	const int globalVariablesCount = 1;
	const int localVariablesCount = 0;
	command[5] = globalVariablesCount & 0xFF;
	command[6] = ((localVariablesCount << 2) | (globalVariablesCount >> 8));
	command[7] = opUI_BUTTON;
	command[8] = PRESSED;
	command[9] = (PRIMPAR_LONG | PRIMPAR_CONST | PRIMPAR_1_BYTE);
	command[10] = parsePort(port().name()) & 0xFF;
	command[11] = 225;
	command[12] = 0;
	QByteArray outputBuf;
	mRobotCommunicator.send(command, buttonResponseSize, outputBuf);
	if (outputBuf.length() == 6 && outputBuf.data()[5] == 0x01) {
		emit newData(1);
	} else {
		emit newData(0);
	}
}

char Button::parsePort(const QString &portName)
{
	if (portName == "Up") {
		return 0x01;
	} else if (portName == "Enter") {
		return 0x02;
	} else if (portName == "Down") {
		return 0x03;
	} else if (portName == "Right") {
		return 0x04;
	} else if (portName == "Left") {
		return 0x05;
	} else if (portName == "Back") {
		return 0x06;
	}

	return 0x00;
}

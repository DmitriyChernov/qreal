#include "userActionBlockFactory.h"

#include <kitBase/blocksBase/common/enginesStopBlock.h>
#include <kitBase/blocksBase/common/clearEncoderBlock.h>

#include <kitBase/blocksBase/common/waitForColorBlock.h>
#include <kitBase/blocksBase/common/waitForColorIntensityBlock.h>
#include <kitBase/blocksBase/common/waitForEncoderBlock.h>
#include <kitBase/blocksBase/common/waitForLightSensorBlock.h>
#include <kitBase/blocksBase/common/waitForSonarDistanceBlock.h>
#include <kitBase/blocksBase/common/waitForSoundSensorBlock.h>
#include <kitBase/blocksBase/common/waitForTouchSensorBlock.h>
#include <kitBase/blocksBase/common/waitForButtonBlock.h>

#include <kitBase/robotModel/robotParts/rangeSensor.h>

using namespace userAction;
using namespace kitBase::blocksBase::common;

qReal::interpretation::Block *UserActionBlockFactory::produceBlock(const qReal::Id &element)
{
	return new ClearEncoderBlock(mRobotModelManager->model());
}

qReal::IdList UserActionBlockFactory::providedBlocks() const
{
	return {
		id("HintMessage")
		, id("ArrowWidget")
		, id("DragPaletteElement")
		, id("DrawLink")
		, id("Wait")
		, id("ChangeWindow")
		, id("PickComboBox")
		, id("Scroll")
		, id("CursorMoveTo")
		, id("MouseButtonAction")
		, id("Type")
		, id("Record")
		, id("Widget")
		, id("Property")
		, id("PropertyRectangle")
	};
}

qReal::IdList UserActionBlockFactory::blocksToDisable() const
{
	return {};
}

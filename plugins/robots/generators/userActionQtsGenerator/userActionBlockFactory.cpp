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
	Q_UNUSED(element)
	return nullptr;
}

qReal::IdList UserActionBlockFactory::providedBlocks() const
{
	return {
		id("Hint")
		, id("Arrow")
		, id("DragPaletteElement")
		, id("DrawLink")
		, id("Wait")
		, id("ChangeWindow")
		, id("PickComboBoxItem")
		, id("Scroll")
		, id("CursorMoveTo")
		, id("MouseButtonAction")
		, id("Type")
		, id("Record")
		, id("GetWidget")
		, id("GetProperty")
		, id("GetPropertyRectangle")
		, id("GetDraggableElement")
	};
}

qReal::IdList UserActionBlockFactory::blocksToDisable() const
{
	return {};
}

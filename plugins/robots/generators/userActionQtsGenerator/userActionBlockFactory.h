#pragma once

#include <kitBase/blocksBase/commonBlocksFactory.h>

namespace userAction {

class UserActionBlockFactory : public kitBase::blocksBase::CommonBlocksFactory
{
public:
	qReal::interpretation::Block *produceBlock(const qReal::Id &element) override;
	qReal::IdList providedBlocks() const override;
	qReal::IdList blocksToDisable() const override;
};

}

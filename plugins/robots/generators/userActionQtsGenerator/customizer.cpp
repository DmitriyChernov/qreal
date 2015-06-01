#include "customizer.h"

using namespace userAction;

Customizer::Customizer(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, generatorBase::lua::LuaProcessor &luaProcessor
		, const QString &generatorName)
	: mFactory(repo, errorReporter, robotModelManager, luaProcessor, generatorName)
	, mInitialBlockType("UserActionEditor", "UserActionDiagram", "InitialNode")
	, mFinalBlockType("UserActionEditor", "UserActionDiagram", "FinalNode")
	, mConditionalBlockType("UserActionEditor", "UserActionDiagram", "IfBlock")
	, mLoopBlockType("UserActionEditor", "UserActionDiagram", "Loop")
	, mSwitchBlockType("UserActionEditor", "UserActionDiagram", "SwitchBlock")
	, mForkBlockType("UserActionEditor", "UserActionDiagram", "Fork")
	, mJoinBlockType("UserActionEditor", "UserActionDiagram", "Join")
	, mSubprogramCallBlockType("UserActionEditor", "UserActionDiagram", "Subprogram")
{
}

generatorBase::GeneratorFactoryBase *Customizer::factory()
{
	return &mFactory;
}

bool Customizer::isInitialNode(const qReal::Id &block) const
{
	return block.type() == mInitialBlockType;
}

bool Customizer::isFinalNode(const qReal::Id &block) const
{
	return block.type() == mFinalBlockType;
}

bool Customizer::isSubprogramCall(const qReal::Id &block) const
{
	return block.type() == mSubprogramCallBlockType;
}

bool Customizer::isConditional(const qReal::Id &block) const
{
	return block.type() == mConditionalBlockType;
}

bool Customizer::isLoop(const qReal::Id &block) const
{
	return block.type() == mLoopBlockType;
}

bool Customizer::isSwitch(const qReal::Id &block) const
{
	return block.type() == mSwitchBlockType;
}

bool Customizer::isFork(const qReal::Id &block) const
{
	return block.type() == mForkBlockType;
}

bool Customizer::isJoin(const qReal::Id &block) const
{
	return block.type() == mJoinBlockType;
}

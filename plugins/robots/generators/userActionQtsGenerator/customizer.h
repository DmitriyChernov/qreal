#pragma once

#include <generatorBase/generatorCustomizer.h>

#include "factory.h"

namespace userAction {

class Customizer : public generatorBase::GeneratorCustomizer
{
public:
	Customizer(const qrRepo::RepoApi &repo
			, qReal::ErrorReporterInterface &errorReporter
			, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
			, generatorBase::lua::LuaProcessor &luaProcessor
			, const QString &generatorName);

	generatorBase::GeneratorFactoryBase *factory() override;

	/// Implementation must tell if block with given id has initial node semantics
	virtual bool isInitialNode(const qReal::Id &block) const;

	/// Implementation must tell if block with given id has final node semantics
	virtual bool isFinalNode(const qReal::Id &block) const;

	/// Implementation must tell if block with given id calls some new routine
	virtual bool isSubprogramCall(const qReal::Id &block) const;

protected:
	/// Implementation must tell if block with given id has if-block semantics
	virtual bool isConditional(const qReal::Id &block) const;

	/// Implementation must tell if block with given id has loop semantics
	virtual bool isLoop(const qReal::Id &block) const;

	/// Implementation must tell if block with given id has switch semantics
	virtual bool isSwitch(const qReal::Id &block) const;

	/// Implementation must tell if block with given id has fork semantics
	virtual bool isFork(const qReal::Id &block) const;

	/// Implementation must tell if block with given id has join semantics
	virtual bool isJoin(const qReal::Id &block) const;

private:
	Factory mFactory;

	const qReal::Id mInitialBlockType;
	const qReal::Id mFinalBlockType;
	const qReal::Id mConditionalBlockType;
	const qReal::Id mLoopBlockType;
	const qReal::Id mSwitchBlockType;
	const qReal::Id mForkBlockType;
	const qReal::Id mJoinBlockType;
	const qReal::Id mSubprogramCallBlockType;
};

}

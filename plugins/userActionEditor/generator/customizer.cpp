#include "customizer.h"

using namespace userAction;

Customizer::Customizer(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, generatorBase::lua::LuaProcessor &luaProcessor
		, const QString &generatorName)
	: mFactory(repo, errorReporter, robotModelManager, luaProcessor, generatorName)
{
}

generatorBase::GeneratorFactoryBase *Customizer::factory()
{
	return &mFactory;
}

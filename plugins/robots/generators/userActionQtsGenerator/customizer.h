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

private:
	Factory mFactory;
};

}

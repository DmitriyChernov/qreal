#pragma once

#include <generatorBase/generatorFactoryBase.h>

namespace userAction {

/// Generator factory implemtation for TRIK platform
class Factory : public generatorBase::GeneratorFactoryBase
{
public:
	Factory(const qrRepo::RepoApi &repo
			, qReal::ErrorReporterInterface &errorReporter
			, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
			, generatorBase::lua::LuaProcessor &luaProcessor
			, const QString &generatorName);

	~Factory() override;

	generatorBase::simple::AbstractSimpleGenerator *simpleGenerator(const qReal::Id &id
			, generatorBase::GeneratorCustomizer &customizer) override;

	QString pathToTemplates() const override;

private:
	const QString mGeneratorName;
};

}

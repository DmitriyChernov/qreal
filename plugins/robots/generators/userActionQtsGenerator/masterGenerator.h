#pragma once

#include <generatorBase/masterGeneratorBase.h>

namespace userAction {

/// Master generator implementation for generator into QtScript user action plugin
class MasterGenerator : public generatorBase::MasterGeneratorBase
{
public:
	MasterGenerator(const qrRepo::RepoApi &repo
			, qReal::ErrorReporterInterface &errorReporter
			, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
			, qrtext::LanguageToolboxInterface &textLanguage
			, const utils::ParserErrorReporter &parserErrorReporter
			, const qReal::Id &diagramId
			, const QString &generatorName);

protected:
	QString targetPath() override;
	bool supportsGotoGeneration() const override;
	generatorBase::GeneratorCustomizer *createCustomizer() override;


	const QString mGeneratorName;
};

}

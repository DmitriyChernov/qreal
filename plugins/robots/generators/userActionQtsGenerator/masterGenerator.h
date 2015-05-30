#pragma once

#include <generatorBase/masterGeneratorBase.h>

namespace userAction {

/// Master generator implementation for generator into QtScript user action plugin
class MasterGenerator : public generatorBase::MasterGeneratorBase
{
public:
	MasterGenerator(const qrRepo::RepoApi &repo
			, qReal::ErrorReporterInterface &errorReporter
			, const utils::ParserErrorReporter &parserErrorReporter
			, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
			, qrtext::LanguageToolboxInterface &textLanguage
			, const qReal::Id &diagramId
			, const QString &generatorName);

protected:
	QString targetPath() override;
	bool supportsGotoGeneration() const override;
};

}

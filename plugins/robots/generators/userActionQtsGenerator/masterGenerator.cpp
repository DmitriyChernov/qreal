#include "masterGenerator.h"

#include "customizer.h"

using namespace userAction;

MasterGenerator::MasterGenerator(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, qrtext::LanguageToolboxInterface &textLanguage
		, const utils::ParserErrorReporter &parserErrorReporter
		, const qReal::Id &diagramId
		, const QString &generatorName)
	: MasterGeneratorBase(repo, errorReporter, robotModelManager, textLanguage, parserErrorReporter
			, diagramId)
	, mGeneratorName(generatorName)
{
}

QString MasterGenerator::targetPath()
{
	return QString("%1/%2.qts").arg(mProjectDir, mProjectName);
}

bool MasterGenerator::supportsGotoGeneration() const
{
	return false;
}

generatorBase::GeneratorCustomizer *MasterGenerator::createCustomizer()
{
	return new Customizer(mRepo, mErrorReporter
			, mRobotModelManager, *createLuaProcessor(), mGeneratorName);
}



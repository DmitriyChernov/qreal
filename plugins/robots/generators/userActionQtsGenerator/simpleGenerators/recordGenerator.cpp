#include "recordGenerator.h"

#include <QtCore/QCoreApplication>

#include <generatorBase/simpleGenerators/bindingGenerator.h>
#include <qrutils/inFile.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;
using namespace utils;

RecordGenerator::RecordGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "userAction/record.t"
			, { Binding::createStatic("@@SCRIPT@@", InFile::readAll(qApp->applicationDirPath() +"/userActions.js")) }
			, parent)
{
}

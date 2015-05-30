#include "recordGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

RecordGenerator::RecordGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: AbstractSimpleGenerator(repo, customizer, id
			, parent)
{
}

QString RecordGenerator::generate()
{

}

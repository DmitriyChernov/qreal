#include "arrowGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

ArrowGenerator::ArrowGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/arrow.t"
			, { Binding::createDirect("@@TARGET@@", "Target")
					 , Binding::createDirect("@@ANGLE@@", "Angle")
					 , Binding::createDirect("@@PARENT@@", "Parent")
					 , Binding::createDirect("@@DURATION@@", "Duration") }
			, parent)
{
}

#include "changeWindowGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

ChangeWindowGenerator::ChangeWindowGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/changeWindow.t"
			, { Binding::createDirect("@@WINDOW@@", "Window") }
			, parent)
{
}

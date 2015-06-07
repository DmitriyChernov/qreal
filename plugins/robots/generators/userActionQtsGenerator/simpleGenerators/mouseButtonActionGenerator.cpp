#include "mouseButtonActionGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

MouseButtonActionGenerator::MouseButtonActionGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/mouseButtonAction.t"
			, { Binding::createDirect("@@BUTTON@@", "Button")
					, Binding::createDirect("@@ACTION@@", "Action")
					, Binding::createDirect("@@TARGET@@", "Target")
					, Binding::createDirect("@@DELAY@@", "Delay") }
			, parent)
{
}

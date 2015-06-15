#include "mouseButtonActionGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

MouseButtonActionGenerator::MouseButtonActionGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, bool haveDelay
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, haveDelay ? "userAction/mouseButtonAction.t" : "userAction/mouseButtonActionWithoutDelay.t"
			, { Binding::createDirect("@@BUTTON@@", "Button")
					, Binding::createDirect("@@ACTION@@", "Action")
					, Binding::createDirect("@@TARGET@@", "Target")
					, Binding::createDirect("@@DELAY@@", "Delay")}
			, parent)
{
}

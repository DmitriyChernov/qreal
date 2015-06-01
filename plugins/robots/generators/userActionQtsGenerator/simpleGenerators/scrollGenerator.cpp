#include "scrollGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

ScrollGenerator::ScrollGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/scroll.t"
			, { Binding::createDirect("@@SCROLLAREA@@", "ScrollArea")
					, Binding::createDirect("@@ITEMNAME@@", "ItemName")
					, Binding::createDirect("@@DURATION@@", "Duration") }
			, parent)
{
}

#include "getMainWindowGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

GetMainWindowGenerator::GetMainWindowGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/getMainWindow.t"
			, { Binding::createStatic("@@STOREVAR@@", "StoreVar") }
			, parent)
{
}

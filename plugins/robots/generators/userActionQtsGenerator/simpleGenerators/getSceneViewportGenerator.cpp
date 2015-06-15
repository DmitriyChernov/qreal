#include "getSceneViewportGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

GetSceneViewportGenerator::GetSceneViewportGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/getSceneViewport.t"
			, { Binding::createDirect("@@STOREVAR@@", "StoreVar") }
			, parent)
{
}

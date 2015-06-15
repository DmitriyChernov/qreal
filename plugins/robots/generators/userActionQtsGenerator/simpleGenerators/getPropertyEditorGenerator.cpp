#include "getPropertyEditorGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

GetPropertyEditorGenerator::GetPropertyEditorGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/getPropertyEditor.t"
			, { Binding::createStatic("@@STOREVAR@@", "StoreVar") }
			, parent)
{
}

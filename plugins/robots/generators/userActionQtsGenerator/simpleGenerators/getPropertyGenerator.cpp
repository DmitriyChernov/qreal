#include "getPropertyGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

GetPropertyGenerator::GetPropertyGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/getProperty.t"
			, { Binding::createDirect("@@STOREVAR@@", "StoreVar")
					, Binding::createDirect("@@NAME@@", "Name") }
			, parent)
{
}

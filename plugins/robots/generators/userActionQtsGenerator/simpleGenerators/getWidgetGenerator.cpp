#include "getWidgetGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

GetWidgetGenerator::GetWidgetGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, bool haveParent
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, haveParent ? "userAction/getWidget.t" : "userAction/getWidgetWithoutParent.t"
			, { Binding::createDirect("@@STOREVAR@@", "StoreVar")
					, Binding::createDirect("@@NAME@@", "Name")
					, Binding::createDirect("@@TYPE@@", "Type")
					, Binding::createDirect("@@PARENT@@", "Parent") }
			, parent)
{
}

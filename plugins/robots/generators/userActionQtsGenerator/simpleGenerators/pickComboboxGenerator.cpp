#include "pickComboboxGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

PickComboboxGenerator::PickComboboxGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/pickCombobox.t"
			, { Binding::createDirect("@@COMBOBOX@@", "ComboBox")
					, Binding::createDirect("@@ITEMNAME@@", "ItemName")
					, Binding::createDirect("@@DURATION@@", "Duration") }
			, parent)
{
}

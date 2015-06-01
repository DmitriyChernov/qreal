#include "hintMessageGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

HintMessageGenerator::HintMessageGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/hint.t"
			, { Binding::createDirect("@@MESSAGE@@", "Message")
					, Binding::createDirect("@@DURATION@@", "Duration")
					, Binding::createDirect("@@PARENT@@", "Parent") }
			, parent)
{
}

#include "hintMessageGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

HintMessageGenerator::HintMessageGenerator(const qrRepo::RepoApi &repo
		, Customizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "hint.t"
			, QList<Binding *>(), parent)
{
}

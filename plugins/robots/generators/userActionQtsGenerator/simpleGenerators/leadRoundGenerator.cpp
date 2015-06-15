#include "leadRoundGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

LeadRoundGenerator::LeadRoundGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/leadRound.t"
			, { Binding::createDirect("@@TARGET@@", "Target")
					, Binding::createDirect("@@DURATION@@", "Duration") }
			, parent)
{
}

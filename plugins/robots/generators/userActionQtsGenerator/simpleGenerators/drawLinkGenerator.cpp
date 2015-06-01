#include "drawLinkGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

DrawLinkGenerator::DrawLinkGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/drawLink.t"
			, { Binding::createDirect("@@FROMELEMENTID@@", "FromElementId")
					, Binding::createDirect("@@TOELEMENTID@@", "ToElementId")
					, Binding::createDirect("@@DURATION@@", "Duration") }
			, parent)
{
}

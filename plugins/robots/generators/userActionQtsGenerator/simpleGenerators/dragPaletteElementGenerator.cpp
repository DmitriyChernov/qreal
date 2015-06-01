#include "dragPaletteElementGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

DragPaletteElementGenerator::DragPaletteElementGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/dragPaletteElement.t"
			, { Binding::createDirect("@@PALETTEELEMENTID@@", "PaletteElementId")
					, Binding::createDirect("@@XCOORD@@", "XCoord")
					, Binding::createDirect("@@YCOORD@@", "YCoord")
					, Binding::createDirect("@@DURATION@@", "Duration") }
			, parent)
{
}

#include "cursorMoveToGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

CursorMoveToGenerator::CursorMoveToGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, bool hasCoords
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, hasCoords ? "userAction/cursorMoveToPoint.t" : "userAction/cursorMoveTo.t"
			, { Binding::createDirect("@@TARGET@@", "Target")
					, Binding::createDirect("@@DURATION@@", "Duration")
					, Binding::createDirect("@@XCOORD@@", "XCoord")
					, Binding::createDirect("@@YCOORD@@", "YCoord")}
			, parent)
{
}

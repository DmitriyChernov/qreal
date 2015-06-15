#include "cursorMoveToRectGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

CursorMoveToRectGenerator::CursorMoveToRectGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "userAction/cursorMoveToRect.t"
			, { Binding::createDirect("@@TARGET@@", "Target")
					, Binding::createDirect("@@DURATION@@", "Duration") }
			, parent)
{
}

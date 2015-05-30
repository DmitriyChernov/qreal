#include "factory.h"

#include <generatorBase/converters/regexpMultiConverter.h>
#include <generatorBase/lua/luaProcessor.h>

#include "simpleGenerators/arrowGenerator.h"
#include "simpleGenerators/changeWindowGenerator.h"
#include "simpleGenerators/cursorMoveToGenerator.h"
#include "simpleGenerators/dragPaletteElementGenerator.h"
#include "simpleGenerators/drawLinkGenerator.h"
#include "simpleGenerators/getDraggableElementGenerator.h"
#include "simpleGenerators/getPropertyGenerator.h"
#include "simpleGenerators/getPropertyRectangleGenerator.h"
#include "simpleGenerators/getWidgetGenerator.h"
#include "simpleGenerators/hintMessageGenerator.h"
#include "simpleGenerators/mouseButtonActionGenerator.h"
#include "simpleGenerators/pickComboboxGenerator.h"
#include "simpleGenerators/recordGenerator.h"
#include "simpleGenerators/scrollGenerator.h"
#include "simpleGenerators/typeGenerator.h"
#include "simpleGenerators/waitGenerator.h"

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase;
using namespace generatorBase::simple;

Factory::Factory(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, lua::LuaProcessor &luaProcessor
		, const QString &generatorName)
	: GeneratorFactoryBase(repo, errorReporter, robotModelManager, luaProcessor)
	, mGeneratorName(generatorName)
{
}

Factory::~Factory()
{
}

AbstractSimpleGenerator *Factory::simpleGenerator(const qReal::Id &id
		, GeneratorCustomizer &customizer)
{
	const QString elementType = id.element();
	if (elementType == "HintMessage") {
		return new HintMessageGenerator(mRepo, customizer, id, this);
	} else if (elementType == "ArrowWidget") {
		return new ArrowGenerator(mRepo, customizer, id, this);
	} else if (elementType == "DragPaletteElement") {
		return new DragPaletteElementGenerator(mRepo, customizer, id, this);
	} else if (elementType == "DrawLink") {
		return new DrawLinkGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Wait") {
		return new WaitGenerator(mRepo, customizer, id, this);
	} else if (elementType == "ChangeWindow") {
		return new ChangeWindowGenerator(mRepo, customizer, id, this);
	} else if (elementType == "PickComboBox") {
		return new PickComboboxGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Scroll") {
		return new ScrollGenerator(mRepo, customizer, id, this);
	} else if (elementType == "CursorMoveTo") {
		return new CursorMoveToGenerator(mRepo, customizer, id, this);
	} else if (elementType == "MouseButtonAction") {
		return new MouseButtonActionGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Type") {
		return new TypeGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Record") {
		return new RecordGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Widget") {
		return new GetWidgetGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Property") {
		return new GetPropertyGenerator(mRepo, customizer, id, this);
	} else if (elementType == "PropertyRectangle") {
		return new GetPropertyRectangleGenerator(mRepo, customizer, id, this);
	} else if (elementType == "DraggableElement") {
		return new GetDraggableElementGenerator(mRepo, customizer, id, this);
	}


	return GeneratorFactoryBase::simpleGenerator(id, customizer);
}

QString Factory::pathToTemplates() const
{
	return ":/" + mGeneratorName + "/templates";
}

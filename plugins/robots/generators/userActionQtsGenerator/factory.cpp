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
#include "simpleGenerators/leadRoundGenerator.h"
#include "simpleGenerators/getMainWindowGenerator.h"
#include "simpleGenerators/getPropertyEditorGenerator.h"
#include "simpleGenerators/getSceneViewportGenerator.h"
#include "simpleGenerators/cursorMoveToRectGenerator.h"

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
	} else if (elementType == "LeadRound") {
		return new LeadRoundGenerator(mRepo, customizer, id, this);
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
		bool const haveCoords = mRepo.property(id, "XCoord").toInt() != -1
				&& mRepo.property(id, "YCoord").toInt() != -1;
		return new CursorMoveToGenerator(mRepo, customizer, id, haveCoords, this);
	} else if (elementType == "CursorMoveToRect") {
		return new CursorMoveToRectGenerator(mRepo, customizer, id, this);
	} else if (elementType == "MouseButtonAction") {
		bool const haveDelay = mRepo.property(id, "Delay").toInt() != 0;
		return new MouseButtonActionGenerator(mRepo, customizer, id, haveDelay, this);
	} else if (elementType == "Type") {
		return new TypeGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Record") {
		return new RecordGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Widget") {
		bool const haveParent = mRepo.property(id, "Parent").toString() != "";
		return new GetWidgetGenerator(mRepo, customizer, id, haveParent, this);
	} else if (elementType == "Property") {
		return new GetPropertyGenerator(mRepo, customizer, id, this);
	} else if (elementType == "PropertyRectangle") {
		return new GetPropertyRectangleGenerator(mRepo, customizer, id, this);
	} else if (elementType == "PropertyEditor") {
		return new GetPropertyEditorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "MainWindow") {
		return new GetMainWindowGenerator(mRepo, customizer, id, this);
	} else if (elementType == "SceneViewport") {
		return new GetSceneViewportGenerator(mRepo, customizer, id, this);
	}

	return GeneratorFactoryBase::simpleGenerator(id, customizer);
}

QString Factory::pathToTemplates() const
{
	return ":/" + mGeneratorName + "/templates";
}

#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'DragPaletteElement' block
class DragPaletteElementGenerator : public generatorBase::simple::BindingGenerator
{
public:
	DragPaletteElementGenerator(const qrRepo::RepoApi &repo
			, generatorBase::GeneratorCustomizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);
};

}
}

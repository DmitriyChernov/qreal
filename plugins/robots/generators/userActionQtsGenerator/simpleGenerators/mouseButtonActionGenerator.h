#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'MouseButtonAction' block
class MouseButtonActionGenerator : public generatorBase::simple::BindingGenerator
{
public:
	MouseButtonActionGenerator(const qrRepo::RepoApi &repo
			, generatorBase::GeneratorCustomizer &customizer
			, const qReal::Id &id
			, bool haveDelay
			, QObject *parent = 0);
};

}
}

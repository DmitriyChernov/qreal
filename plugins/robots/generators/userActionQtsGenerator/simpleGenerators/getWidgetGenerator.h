#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'GetWidget' block
class GetWidgetGenerator : public generatorBase::simple::BindingGenerator
{
public:
	GetWidgetGenerator(const qrRepo::RepoApi &repo
			, generatorBase::GeneratorCustomizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);
};

}
}

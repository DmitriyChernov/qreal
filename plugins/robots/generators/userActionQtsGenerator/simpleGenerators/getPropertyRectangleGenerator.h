#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'GetPropertyRectangle' block
class GetPropertyRectangleGenerator : public generatorBase::simple::BindingGenerator
{
public:
	GetPropertyRectangleGenerator(const qrRepo::RepoApi &repo
			, Customizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);
};

}
}

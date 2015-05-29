#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'GetProperty' block
class GetPropertyGenerator : public generatorBase::simple::BindingGenerator
{
public:
	GetPropertyGenerator(const qrRepo::RepoApi &repo
			, Customizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);
};

}
}

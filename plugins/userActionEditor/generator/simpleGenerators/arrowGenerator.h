#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'Arrow' block
class ArrowGenerator : public generatorBase::simple::BindingGenerator
{
public:
	ArrowGenerator(const qrRepo::RepoApi &repo
			, Customizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);
};

}
}

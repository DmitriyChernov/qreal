#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'Wait' block
class WaitGenerator : public generatorBase::simple::BindingGenerator
{
public:
	WaitGenerator(const qrRepo::RepoApi &repo
			, Customizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);
};

}
}

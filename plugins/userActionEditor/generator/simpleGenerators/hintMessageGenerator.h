#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'HintMessage' block
class HintMessageGenerator : public generatorBase::simple::BindingGenerator
{
public:
	HintMessageGenerator(const qrRepo::RepoApi &repo
			, Customizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);
};

}
}

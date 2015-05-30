#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'Type' block
class TypeGenerator : public generatorBase::simple::BindingGenerator
{
public:
	TypeGenerator(const qrRepo::RepoApi &repo
			, generatorBase::GeneratorCustomizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);
};

}
}

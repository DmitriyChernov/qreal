#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'Record' block
class RecordGenerator : public generatorBase::simple::AbstractSimpleGenerator
{
public:
	RecordGenerator(const qrRepo::RepoApi &repo
			, Customizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);

	/// Generates and returns code using parameters specified in constructor
	virtual QString generate();
};

}
}

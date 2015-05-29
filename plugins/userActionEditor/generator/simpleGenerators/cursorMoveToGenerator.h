#pragma once

#include "generatorBase/simpleGenerators/bindingGenerator.h"

#include "customizer.h"

namespace userAction {
namespace simpleGenerators {

/// Generator for 'CursorMoveTo' block
class CursorMoveToGenerator : public generatorBase::simple::BindingGenerator
{
public:
	CursorMoveToGenerator(const qrRepo::RepoApi &repo
			, Customizer &customizer
			, const qReal::Id &id
			, QObject *parent = 0);
};

}
}

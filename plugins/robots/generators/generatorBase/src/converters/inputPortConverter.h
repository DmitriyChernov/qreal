#pragma once

#include "generatorBase/converters/enumConverterBase.h"

namespace generatorBase {
namespace converters {

/// Converts an input port with given number into generator-dependent port representation.
/// Resulting code must be specified in "sensors/port*.t" templates.
class InputPortConverter : public EnumConverterBase
{
public:
	explicit InputPortConverter(QString const &pathToTemplates);
};

}
}

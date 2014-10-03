#include "enginesGenerator.h"

#include "generatorBase/generatorCustomizer.h"
#include "generatorBase/parts/engines.h"

using namespace generatorBase::simple;
using namespace qReal;

EnginesGenerator::EnginesGenerator(qrRepo::RepoApi const &repo
		, GeneratorCustomizer &customizer
		, Id const &id
		, QString const &engineType
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, engineType.contains("EnginesBackward")
					? "engines/enginesBackward.t"
					: "engines/enginesForward.t"
			, QList<Binding *>()
					<< Binding::createMultiTarget("@@PORT@@", "Ports", customizer.factory()->enginesConverter())
					<< Binding::createConverting("@@POWER@@", "Power", customizer.factory()->intPropertyConverter())
					<< Binding::createConverting("@@BREAK_MODE@@", "Mode", customizer.factory()->breakModeConverter())
			, parent)
{
	mCustomizer.factory()->engines()->registerUsageOnPorts(repo.property(id, "Ports").toString());
}

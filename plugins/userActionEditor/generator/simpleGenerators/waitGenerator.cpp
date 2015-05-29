#include "waitGenerator.h"

#include <generatorBase/simpleGenerators/bindingGenerator.h>

using namespace userAction;
using namespace userAction::simpleGenerators;
using namespace generatorBase::simple;
using namespace qReal;

WaitGenerator::WaitGenerator(const qrRepo::RepoApi &repo
		, Customizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, "wait.t"
			, QList<Binding *>(), parent)
{
}

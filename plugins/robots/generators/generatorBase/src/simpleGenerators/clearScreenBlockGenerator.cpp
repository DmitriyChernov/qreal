#include "clearScreenBlockGenerator.h"

#include "generatorBase/generatorCustomizer.h"
#include "generatorBase/parts/images.h"

using namespace generatorBase::simple;
using namespace qReal;

ClearScreenBlockGenerator::ClearScreenBlockGenerator(qrRepo::RepoApi const &repo
		, GeneratorCustomizer &customizer
		, Id const &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id
			, customizer.factory()->images()->bmpFilesCount()
					// WARNING: this may not work when we traverse here earlier than
					// into drawing block but it will be executed before this block
					? "drawing/clearUsedScreen.t"
					: "drawing/clearUnusedScreen.t"
			, QList<Binding *>(), parent)
{
}

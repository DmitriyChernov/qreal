#include "generatorPlugin.h"

#include "masterGenerator.h"

using namespace generatorBase;
using namespace userAction;
using namespace qReal;

UserActionGeneratorPlugin::UserActionGeneratorPlugin()
	: RobotsGeneratorPluginBase()
	, mRobotModel(new NoRobotModel(kitId(), ""))
	, mGenerateCodeAction(new QAction(nullptr))
	, mBlocksFactory(new UserActionBlockFactory)
{
}

UserActionGeneratorPlugin::~UserActionGeneratorPlugin()
{
}

void UserActionGeneratorPlugin::init(const kitBase::KitPluginConfigurator &configurator)
{
	RobotsGeneratorPluginBase::init(configurator);
}

QList<ActionInfo> UserActionGeneratorPlugin::customActions()
{
	mGenerateCodeAction->setText(tr("Generate userAcion QtScript code"));
	ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);
	mGenerateCodeAction->setObjectName("generateUserAcionQtScriptCode");

//	mStartRecordAction->setText(tr("Start record user actions"));
//	ActionInfo startRecordActionInfo(mStartRecordAction, "generators", "tools");
//	//connect(mStartRecordAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);
//	mStartRecordAction->setObjectName("startRecord");

//	mStopRecordAction->setText(tr("Stop record user actions"));
//	ActionInfo stopRecordActionInfo(mStartRecordAction, "generators", "tools");
//	//connect(mStartRecordAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);
//	mStopRecordAction->setObjectName("stopRecord");

	return {generateCodeActionInfo };
}

QList<HotKeyActionInfo> UserActionGeneratorPlugin::hotKeyActions()
{
	//mGenerateCodeAction->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F8));
//	mStartRecordAction>setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F9));
//	mStopRecordAction>setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F10));

	//HotKeyActionInfo generateCodeInfo("Generator.GenerateUserAcionQtScript", tr("Generate userAcion QtScript code"), mGenerateCodeAction);
//	HotKeyActionInfo startCodeInfo("Generator.StartRecord", tr("Start recording user actions"), mStartRecordAction);
//	HotKeyActionInfo stopCodeInfo("Generator.StopRecord", tr("Stop recording user actions"), mStopRecordAction);

	return { };
}

QIcon UserActionGeneratorPlugin::iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)
	return QIcon(":/icons/images/unknownSomething.png");
}

generatorBase::MasterGeneratorBase *UserActionGeneratorPlugin::masterGenerator()
{
	return new MasterGenerator(*mRepo
			, *mMainWindowInterface->errorReporter()
			, *mRobotModelManager
			, *mTextLanguage
			, *mParserErrorReporter
			, mMainWindowInterface->activeDiagram()
			, generatorName());
}

QString UserActionGeneratorPlugin::defaultFilePath(const QString &projectName) const
{
	return QString("userAction/%1/%1.qts").arg(projectName);
}

text::LanguageInfo UserActionGeneratorPlugin::language() const
{
	return qReal::text::Languages::qtScript();
}

QString UserActionGeneratorPlugin::generatorName() const
{
	return "userAction";
}

QString UserActionGeneratorPlugin::kitId() const
{
	return "trikKit";
}

QList<kitBase::robotModel::RobotModelInterface *> UserActionGeneratorPlugin::robotModels()
{
	return { mRobotModel.data() };
}

kitBase::blocksBase::BlocksFactoryInterface *UserActionGeneratorPlugin::blocksFactoryFor(
		const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model)
	return mBlocksFactory;
}

QList<kitBase::AdditionalPreferences *> UserActionGeneratorPlugin::settingsWidgets()
{
	return {};
}

void UserActionGeneratorPlugin::regenerateExtraFiles(const QFileInfo &newFileInfo)
{
	Q_UNUSED(newFileInfo);
}

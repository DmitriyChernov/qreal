#include "generatorPlugin.h"

#include "masterGenerator.h"

using namespace generatorBase;
using namespace userAction;
using namespace qReal;

UserActionGeneratorPlugin::UserActionGeneratorPlugin()
	: RobotsGeneratorPluginBase()
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
//	mGenerateCodeAction->setText(tr("Generate QtScript code"));
//	ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
//	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);
//	mGenerateCodeAction->setObjectName("generateQtScriptCode");

//	mStartRecordAction->setText(tr("Start record user actions"));
//	ActionInfo startRecordActionInfo(mStartRecordAction, "generators", "tools");
//	//connect(mStartRecordAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);
//	mStartRecordAction->setObjectName("startRecord");

//	mStopRecordAction->setText(tr("Stop record user actions"));
//	ActionInfo stopRecordActionInfo(mStartRecordAction, "generators", "tools");
//	//connect(mStartRecordAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);
//	mStopRecordAction->setObjectName("stopRecord");

//	return {generateCodeActionInfo, startRecordActionInfo, stopRecordActionInfo };
}

QList<HotKeyActionInfo> UserActionGeneratorPlugin::hotKeyActions()
{
//	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
//	mStartRecordAction>setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F9));
//	mStopRecordAction>setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F10));

//	HotKeyActionInfo generateCodeInfo("Generator.GenerateQtScript", tr("Generate QtScript code"), mGenerateCodeAction);
//	HotKeyActionInfo startCodeInfo("Generator.StartRecord", tr("Start recording user actions"), mStartRecordAction);
//	HotKeyActionInfo stopCodeInfo("Generator.StopRecord", tr("Stop recording user actions"), mStopRecordAction);

//	return { generateCodeInfo, startCodeInfo, stopCodeInfo };
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
			, *mParserErrorReporter
			, *mRobotModelManager
			, *mTextLanguage
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

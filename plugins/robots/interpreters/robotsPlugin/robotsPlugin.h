#pragma once

#include <qrgui/plugins/toolPluginInterface/toolPluginInterface.h>

#include <interpreterCore/robotsPluginFacade.h>

namespace robotsPlugin {

/// Provides entry points to robots plugin. Responsible for implementation of ToolPluginInterface and for
/// interaction with QReal, including ActionInfo objects and other stuff that has nothing to do with plugin logic,
/// but is required by QReal. It also does some basic reaction to actions like "open robot settings page".
class RobotsPlugin : public QObject, public qReal::ToolPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(qReal::ToolPluginInterface)
	Q_PLUGIN_METADATA(IID "qRealRobots.RobotsPlugin")

public:
	/// Constructor. Creates plugin in uninitialized state, "init" shall be called before plugin can do anything useful.
	RobotsPlugin();

	void init(const qReal::PluginConfigurator &configurator) override;
	qReal::Customizer *customizationInterface() override;  // Does not transfer ownership.
	QPair<QString, qReal::gui::PreferencesPage *> preferencesPage() override;  // Transfers ownership.
	QList<qReal::ActionInfo> actions() override;  // Does not transfer ownership of QAction objects.
	QList<qReal::HotKeyActionInfo> hotKeyActions() override;  // Does not transfer ownership of QAction objects.
	QList<qReal::ProjectConverter> projectConverters() override;
	QStringList defaultSettingsFiles() override;
	QObject *guiScriptFacade() override;

private:
	/// Main window interface object, used to call GUI functionality.
	qReal::gui::MainWindowInterpretersInterface *mMainWindowInterpretersInterface;  // Does not have ownership

	QScopedPointer<interpreterCore::RobotsPluginFacade> mRobotsPluginFacade;
};

}

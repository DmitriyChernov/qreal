var mainWindow = api.ui().mainWindow();
api.changeWindow(mainWindow);
var Index = [63, 5, -1, 0];
var Type = ["qReal::MainWindow", "QDockWidget", "kitBase::DevicesConfigurationWidget", "QWidget", "QScrollBar"];
var ObjectName = ["MainWindowUi", "", "", "qt_scrollarea_vcontainer", ""];
var widget = api.ui().widget("qReal::MainWindow", "MainWindowUi");
for (var i = 1; i <= 4; i ++) 
{
	if (Index[i - 1] == -1) {
		widget = api.ui().widget(Type[i], ObjectName[i], widget);
	} else {
		widget = api.ui().widgetByIndex(Index[i - 1], widget);
	}
}
api.scroll(widget, 184, 500);
var PortD1DeviceConfig = api.ui().widget("QComboBox", "Port D1 DeviceConfig");
api.cursor().moveTo(PortD1DeviceConfig, 500)
api.cursor().leftButtonPress(PortD1DeviceConfig);
var QComboBoxPrivateContainerClassWindow = api.ui().widget("QWidgetWindow", "QComboBoxPrivateContainerClassWindow");
api.cursor().moveTo(QComboBoxPrivateContainerClassWindow, 500);
api.cursor().leftButtonRelease(QComboBoxPrivateContainerClassWindow);
var qt_scrollarea_viewport = api.ui().widget("QWidget", "qt_scrollarea_viewport");
api.cursor().moveTo(qt_scrollarea_viewport, 500);
api.cursor().leftButtonRelease(qt_scrollarea_viewport);

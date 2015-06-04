var mainWindow = api.ui().mainWindow();
api.changeWindow(mainWindow);
var Index = [-1, 5, -1, 0];
var Type = ["qReal::MainWindow", "QDockWidget", "kitBase::DevicesConfigurationWidget", "QWidget", "QScrollBar"];
var ObjectName = ["MainWindowUi", "devicesConfigurationDock", "", "qt_scrollarea_vcontainer", ""];
var widget = api.ui().widget("qReal::MainWindow", "MainWindowUi");
for (var i = 1; i <= 4; i ++) 
{
	if (Index[i - 1] == -1) {
		widget = api.ui().widget(Type[i], ObjectName[i], widget);
	} else {
		widget = api.ui().widgetByIndex(Index[i - 1], widget);
	}
}
api.scroll(widget, 152, 500);
var PortD1DeviceConfig = api.ui().widget("QComboBox", "Port D1 DeviceConfig");
api.cursor().moveTo(PortD1DeviceConfig, 500);
api.cursor().leftButtonPress(PortD1DeviceConfig);
api.wait(100);
api.pickComboBoxItem(PortD1DeviceConfig, 1, 1000);
var Index = [-1, -1, 1];
var Type = ["qReal::MainWindow", "QDockWidget", "qReal::gui::PaletteTree", "QComboBox"];
var ObjectName = ["MainWindowUi", "paletteDock", "paletteTree", ""];
var widget = api.ui().widget("qReal::MainWindow", "MainWindowUi");
for (var i = 1; i <= 3; i ++) 
{
	if (Index[i - 1] == -1) {
		widget = api.ui().widget(Type[i], ObjectName[i], widget);
	} else {
		widget = api.ui().widgetByIndex(Index[i - 1], widget);
	}
}
api.cursor().moveTo(widget, 500);
api.cursor().leftButtonPress(widget);
api.wait(100);
api.pickComboBoxItem(widget, 1, 1000);
var Начало = api.palette().dragPaletteElement("qrm:/RobotsMetamodel/RobotsDiagram/InitialNode", 500, 6, 118);
var Моторывперёд = api.palette().dragPaletteElement("qrm:/RobotsMetamodel/RobotsDiagram/TrikV6EnginesForward", 500, 128, 146);

var mainWindow = api.ui().mainWindow();
api.changeWindow(mainWindow);
var Index = [-1, 12];
var Type = ["qReal::MainWindow", "QToolBar", "QToolButton"];
var ObjectName = ["MainWindowUi", "interpretersToolbar", ""];
var widget = api.ui().widget("qReal::MainWindow", "MainWindowUi");
for (var i = 1; i <= 2; i ++) 
{
	if (Index[i - 1] == -1) {
		widget = api.ui().widget(Type[i], ObjectName[i], widget);
	} else {
		widget = api.ui().widgetByIndex(Index[i - 1], widget);
	}
}
api.cursor().moveTo(widget, 500);
api.cursor().leftButtonPress(widget);
var Index = [-1, 12];
var Type = ["qReal::MainWindow", "QToolBar", "QToolButton"];
var ObjectName = ["MainWindowUi", "interpretersToolbar", ""];
var widget = api.ui().widget("qReal::MainWindow", "MainWindowUi");
for (var i = 1; i <= 2; i ++) 
{
	if (Index[i - 1] == -1) {
		widget = api.ui().widget(Type[i], ObjectName[i], widget);
	} else {
		widget = api.ui().widgetByIndex(Index[i - 1], widget);
	}
}
api.cursor().leftButtonRelease(widget);

var mainWindow = api.ui().mainWindow();
api.changeWindow(mainWindow);
var Index = [-1, 10];
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
var Index = [-1, 10];
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
api.wait(500);
var Index = [-1, -1, -1, -1, -1, 1, 4];
var Type = ["qReal::MainWindow", "utils::SmartDock", "twoDModel::view::TwoDModelWidget", "QWidget", "QWidget", "twoDModel::view::Palette", "QToolBar", "QToolButton"];
var ObjectName = ["MainWindowUi", "2dModelDock", "TwoDModelWidget", "toolbarWidget", "mainTabBarWidget", "palette", "", ""];
var widget = api.ui().widget("qReal::MainWindow", "MainWindowUi");
for (var i = 1; i <= 7; i ++) 
{
	if (Index[i - 1] == -1) {
		widget = api.ui().widget(Type[i], ObjectName[i], widget);
	} else {
		widget = api.ui().widgetByIndex(Index[i - 1], widget);
	}
}
api.cursor().moveTo(widget, 500);
api.cursor().leftButtonPress(widget);
var Index = [-1, -1, -1, -1, -1, 1, 4];
var Type = ["qReal::MainWindow", "utils::SmartDock", "twoDModel::view::TwoDModelWidget", "QWidget", "QWidget", "twoDModel::view::Palette", "QToolBar", "QToolButton"];
var ObjectName = ["MainWindowUi", "2dModelDock", "TwoDModelWidget", "toolbarWidget", "mainTabBarWidget", "palette", "", ""];
var widget = api.ui().widget("qReal::MainWindow", "MainWindowUi");
for (var i = 1; i <= 7; i ++) 
{
	if (Index[i - 1] == -1) {
		widget = api.ui().widget(Type[i], ObjectName[i], widget);
	} else {
		widget = api.ui().widgetByIndex(Index[i - 1], widget);
	}
}
api.cursor().leftButtonRelease(widget);
var Index = [-1, -1, -1, -1, 0];
var Type = ["qReal::MainWindow", "utils::SmartDock", "twoDModel::view::TwoDModelWidget", "QWidget", "graphicsUtils::AbstractView", "QWidget"];
var ObjectName = ["MainWindowUi", "2dModelDock", "TwoDModelWidget", "sceneWidget", "graphicsView", ""];
var widget = api.ui().widget("qReal::MainWindow", "MainWindowUi");
for (var i = 1; i <= 5; i ++) 
{
	if (Index[i - 1] == -1) {
		widget = api.ui().widget(Type[i], ObjectName[i], widget);
	} else {
		widget = api.ui().widgetByIndex(Index[i - 1], widget);
	}
}
api.cursor().moveTo(widget, 500);
api.cursor().leftButtonPress(widget);
var Index = [-1, -1, -1, -1, 0];
var Type = ["qReal::MainWindow", "utils::SmartDock", "twoDModel::view::TwoDModelWidget", "QWidget", "graphicsUtils::AbstractView", "QWidget"];
var ObjectName = ["MainWindowUi", "2dModelDock", "TwoDModelWidget", "sceneWidget", "graphicsView", ""];
var widget = api.ui().widget("qReal::MainWindow", "MainWindowUi");
for (var i = 1; i <= 5; i ++) 
{
	if (Index[i - 1] == -1) {
		widget = api.ui().widget(Type[i], ObjectName[i], widget);
	} else {
		widget = api.ui().widgetByIndex(Index[i - 1], widget);
	}
}
api.cursor().leftButtonRelease(widget);

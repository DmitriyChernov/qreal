var mainWindow = api.ui().mainWindow();
api.changeWindow(mainWindow);
var Таймер = api.palette().dragPaletteElement("qrm:/RobotsMetamodel/RobotsDiagram/Timer", 500, 358, 308);
var prop = api.ui().propertyRect("Задержка (мс)");
var propertyEditor = api.ui().propertyEditor();
api.cursor().moveToRect(prop, 500);
api.cursor().leftButtonPress(propertyEditor);
var prop = api.ui().propertyRect("Задержка (мс)");
var propertyEditor = api.ui().propertyEditor();
api.wait(100);
api.cursor().leftButtonRelease(propertyEditor, 100);
api.keyboard().type("100", 500);
var Таймер = api.palette().dragPaletteElement("qrm:/RobotsMetamodel/RobotsDiagram/TrikWaitForSonarDistance", 500, 588, 299);
var sceneViewport = api.ui().sceneViewport();
api.cursor().sceneMoveTo(sceneViewport, 1000, 444, 323);
api.cursor().rightButtonPress(sceneViewport);
var sceneViewport = api.ui().sceneViewport();
api.cursor().sceneMoveTo(sceneViewport, 1000, 687, 320);
api.cursor().rightButtonRelease(sceneViewport, 100);
var sceneViewport = api.ui().sceneViewport();
api.cursor().sceneMoveTo(sceneViewport, 1000, 687, 320);
api.cursor().leftButtonPress(sceneViewport);
var sceneViewport = api.ui().sceneViewport();
api.cursor().sceneMoveTo(sceneViewport, 1000, 687, 320);
api.cursor().leftButtonRelease(sceneViewport, 100);
var prop = api.ui().propertyRect("Расстояние");
var propertyEditor = api.ui().propertyEditor();
api.cursor().moveToRect(prop, 500);
api.cursor().leftButtonPress(propertyEditor);
var prop = api.ui().propertyRect("Расстояние");
var propertyEditor = api.ui().propertyEditor();
api.wait(100);
api.cursor().leftButtonRelease(propertyEditor, 100);
api.keyboard().type("10", 500);
var prop = api.ui().propertyRect("Считанное значение");
var propertyEditor = api.ui().propertyEditor();
api.wait(100);
api.cursor().leftButtonRelease(propertyEditor, 100);
var Index = [-1, -1, -1, 0, 1, -1, 0];
var Type = ["qReal::MainWindow", "QDockWidget", "QWidget", "PropertyEditorView", "QtTreePropertyBrowser", "QtPropertyEditorView", "QWidget", "QComboBox"];
var ObjectName = ["MainWindowUi", "propertyDock", "propertyEditorDockWidgetContents", "propertyEditor", "", "", "qt_scrollarea_viewport", ""];
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
api.wait(100);
api.pickComboBoxItem(widget, 0, 1000);
api.wait(100);
api.pickComboBoxItem(widget, 1, 1000);
api.wait(100);
api.pickComboBoxItem(widget, 1, 1000);

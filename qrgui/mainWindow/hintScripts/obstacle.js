var mainWindow = api.ui().mainWindow();
api.changeWindow(mainWindow);
var PortA1DeviceConfig = api.ui().widget("QComboBox", "Port A1 DeviceConfig");
api.cursor().moveTo(PortA1DeviceConfig, 500)
api.cursor().leftButtonPress(PortA1DeviceConfig);
api.wait(100)
api.pickComboBoxItem(PortA1DeviceConfig, 2, 1000);

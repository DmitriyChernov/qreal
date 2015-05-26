#pragma once

#include <QtWidgets/QWidget>

namespace twoDModel {

namespace view {
class TwoDModelWidget;
}

namespace engine {

/// Implemented facade pattern. This clas  allows to search and get objects of plugin`s user interface
/// from scripting language  by their object names, parents and types.
class TwoDModelGuiFacade : public QObject
{
	Q_OBJECT

public:
	explicit TwoDModelGuiFacade(view::TwoDModelWidget &d2RobotWidget);

	/// Returns widget, which defined by type and object name.
	Q_INVOKABLE QWidget *widget(QString const &type, QString const &name);

	/// Returns 2d model widget.
	Q_INVOKABLE QWidget *d2ModelWidget();

	/// Returns scene of d2 model widget.
	Q_INVOKABLE QWidget *d2ModelSceneViewport();

private:
	view::TwoDModelWidget &mD2ModelWidget;
};

}
}

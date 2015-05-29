#pragma once

#include <QtWidgets/QLabel>
#include <QtCore/QString>
#include <QtWidgets/QComboBox>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEvent>

namespace qReal {

class MainWindow;

namespace gui {

class ScriptAPI;

/// This class provides tool for emulate mouse actions. Represented as QLabel with some logic same as real
/// mouse. Virtual Mouse post some QMouseEvents to system, when working.
/// Can work in "hard" and "light" modes, whos
/// difference is in posted move events. Hard mode needed in some methods in API. mRightButtonPressed
/// is true in this case.
class VirtualCursor : public QLabel
{
	Q_OBJECT

public:
	explicit VirtualCursor(ScriptAPI *scriptAPI, QWidget *parent);

	/// Moves virtual cursor to target with type for duration ms.
	Q_INVOKABLE void moveTo(QWidget const *target, int duration);

	/// Moves virtual cursor to target point in parent coordinate system for duration ms.
	Q_INVOKABLE void moveToPoint(int const x, int const y, int const duration);

	/// Moves virtual cursor to center of target rectangle for duration ms.
	Q_INVOKABLE void moveToRect(QRect const &target, int duration);

	/// Moves virtual cursor to pos on scene with type for duration ms.
	Q_INVOKABLE void sceneMoveTo(QWidget *target, int duration, int xSceneCoord, int ySceneCoord);

	/// Posts left mouse button press to widget.
	Q_INVOKABLE void leftButtonPress(QWidget *target, int delay = -1);

	/// Posts left mouse button release to widget.
	Q_INVOKABLE void leftButtonRelease(QWidget *target, int delay = -1);

	/// Posts left mouse button release to widget.
	Q_INVOKABLE void rightButtonPress(QWidget *target, int delay = -1);

	/// Posts right mouse button release to widget.
	Q_INVOKABLE void rightButtonRelease(QWidget *target, int delay = -1);

	/// Posts mouse move event to widget.
	Q_INVOKABLE void moved(QWidget *target);

	/// Draws palette element icon near virtual cursor by name.
	void startDrag(QIcon const &iconName);

	/// Redraws virtual cursor without ant icon.
	void endDrag();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	void simulateMouse(QObject *reciever, QEvent::Type event, QPointF const &pos, Qt::MouseButton buttons);
	void edgeFinished();

	QIcon mPaletteElementIcon;
	ScriptAPI *mScriptAPI;
	QPropertyAnimation *mCursorMoveAnimation;

	bool mRightButtonPressed;
	bool mLeftButtonPressed;
	bool mDragStarted;
};

}
}

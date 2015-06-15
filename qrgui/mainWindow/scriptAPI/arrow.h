#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QLabel>

namespace qReal {

namespace gui {

/// Represents graphical arrow. Allows draw navigated arrows with opacity animation (for a lifeTime).
/// Class HintAPI provides interface to draw those arrows, directed on any object in GUI of a system.
class Arrow : public QLabel
{
	Q_OBJECT

public:
	Arrow(QWidget const *target, int const angle, int const lifeTime, QWidget *parent);

protected:
	void paintEvent(QPaintEvent *);

private slots:
	void disappear();

private:
	QWidget const *mTarget;
	int const mAngle;
	int const mDuration;
};

}
}

#pragma once

#include <QWidget>
#include <QtCore/QEventLoop>
#include <QtCore/QPropertyAnimation>
#include <QtWidgets/QGraphicsOpacityEffect>

namespace userAction {

class RecordSign : public QWidget
{
	Q_OBJECT

public:
	RecordSign(QWidget *parent);

public slots:
	void animate();
	void stop();

protected:
	void paintEvent(QPaintEvent *);

private:
	void appear(int duration);
	void disappear(int duration);

	QTimer *mTimer;
	int mState;
};

}

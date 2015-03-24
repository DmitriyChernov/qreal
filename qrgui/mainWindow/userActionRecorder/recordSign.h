#pragma once

#include <QWidget>
#include <QtCore/QEventLoop>
#include <QtCore/QPropertyAnimation>
#include <QtWidgets/QGraphicsOpacityEffect>

namespace qReal {

class MainWindow;

namespace gui {

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

	int mState;
	QTimer *mTimer;
};

}
}

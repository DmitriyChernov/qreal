#pragma once

#include <QWidget>
#include <QtCore/QEventLoop>

namespace qReal {

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
	QEventLoop mEventLoop;
};

}
}

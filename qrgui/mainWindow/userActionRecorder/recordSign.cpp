#include "recordSign.h"

#include <QtCore/QTimer>
#include <QtGui/QPainter>

#include <qrutils/graphicsUtils/animatedEffects.h>

using namespace qReal;
using namespace gui;
using namespace mathUtils;
using namespace graphicsUtils;

RecordSign::RecordSign(QWidget *parent) :
	QWidget(parent)
{
	setAttribute(Qt::WA_TransparentForMouseEvents, true);
	setWindowFlags(Qt::WindowStaysOnTopHint);
	activateWindow();
}

void Arrow::paintEvent(QPaintEvent *)
{
	QPixmap pm(100,100);
	pm.fill();

	QPainter p(&pm);
	p.setRenderHint(QPainter::Antialiasing, true);
	QPen pen(Qt::black, 3);
	p.setPen(pen);
	QBrush brush(Qt::red);
	p.setBrush(brush);
	p.drawEllipse(0, 0, 200, 200);
	QLabel l;
	l.setPixmap(pm);
	l.show();
}

void RecordSign::animate()
{
	while (!isHidden())
	{
		AnimatedEffects::disappear(this, 200);
		AnimatedEffects::appear(this, 200);

		if (duration != -1) {
			QTimer::singleShot(duration, &mEventLoop, SLOT(quit()));
		}

		mEventLoop.exec();
	}
}

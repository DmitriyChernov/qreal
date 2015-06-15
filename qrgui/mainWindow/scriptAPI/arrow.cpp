#include "arrow.h"

#include <QtCore/QtMath>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOptionGraphicsItem>

#include <qrutils/mathUtils/math.h>
#include <qrutils/graphicsUtils/animatedEffects.h>

#include <QDebug>

qreal const arrowSize = 15;

using namespace qReal;
using namespace gui;
using namespace mathUtils;
using namespace graphicsUtils;

Arrow::Arrow(QWidget const *target, const int angle, int const lifeTime, QWidget *parent)
	: QLabel(parent)
	, mTarget(target)
	, mAngle(angle)
	, mDuration(lifeTime / 2)
{
	setAttribute(Qt::WA_TransparentForMouseEvents, true);
	setWindowFlags(Qt::WindowStaysOnTopHint);
	show();
	setFixedSize(target->width(), target->height());
	QTimer::singleShot(mDuration, this, SLOT(disappear()));
	QTimer::singleShot(lifeTime, this, SLOT(deleteLater()));
}

void Arrow::paintEvent(QPaintEvent *)
{

	qreal const angleInRads = mAngle * pi / 180;
	int const sourcePointDeviation =  qMax(qMax(mTarget->width(), mTarget->height()) / 3, 80);
	int const indent = qMin(qMin(mTarget->width(), mTarget->height()) / 6, 20);
	QPoint const sourcePoint = QPoint(mTarget->width()/2 + abs(sourcePointDeviation * qCos(angleInRads))
			, mTarget->height()/2 + abs(sourcePointDeviation * qSin(angleInRads)));
	QPoint const destPoint = QPoint(mTarget->width()/2 + abs(indent * qCos(angleInRads))
			, mTarget->height()/2  + abs (indent * qSin(angleInRads)));

	QPainter painter(this);
	QLineF line(sourcePoint, destPoint);

	painter.setPen(QPen(Qt::black, arrowSize / 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	// Draw rectangle to highlight
	painter.drawRect(rect());
	qreal angle = acos(line.dx() / line.length());
	if (line.dy() >= 0) {
		angle = 2 * pi - angle;
	}
	QPointF const destArrowFirst =  destPoint + QPoint(sin(angle - pi / 3) * arrowSize
			, cos(angle - pi / 3) * arrowSize);
	QPointF const destArrowSecond = destPoint + QPoint(sin(angle - 2 * pi / 3) * arrowSize
			, cos(angle - 2 * pi / 3) * arrowSize);
	painter.setBrush(Qt::red);
	painter.drawLine(line);
	painter.drawPolygon(QPolygonF() << line.p2() << destArrowFirst << destArrowSecond);
}

void Arrow::disappear()
{
	AnimatedEffects::disappear(this, mDuration);
}

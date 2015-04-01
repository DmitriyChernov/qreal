#include "recordSign.h"

#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtWidgets/QLabel>

#include <qrutils/graphicsUtils/animatedEffects.h>

using namespace userAction;

RecordSign::RecordSign(QWidget *parent) :
	QWidget(parent)
	, mTimer(new QTimer)
	, mState(0)
{
	setWindowFlags(Qt::WindowStaysOnTopHint);
	raise();
	show();
	setFixedSize(200, 200);
	move(QPoint(50,50));

	QPainter *painter = new QPainter(this);
	QPen pen = painter->pen();
	pen.setCosmetic(true);
	pen.setWidth(3);
	pen.setColor(QColor(Qt::black));
	painter->setPen(pen);
	QBrush brush = painter->brush();
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);
	painter->setBrush(brush);
	painter->drawEllipse(QPointF(50, 50), 40, 40);
}

void RecordSign::paintEvent(QPaintEvent *)
{
	QPainter *painter = new QPainter(this);
	QPen pen = painter->pen();
	pen.setCosmetic(true);
	pen.setWidth(3);
	pen.setColor(QColor(Qt::black));
	painter->setPen(pen);
	QBrush brush = painter->brush();
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);
	painter->setBrush(brush);
	painter->drawEllipse(QPointF(50, 50), 40, 40);
}

void RecordSign::animate()
{
	if (mState == 0)
	{
		disappear(300);
		mState++;
		mTimer->setInterval(600);
	} else if (mState == 1) {
		appear(300);
		mState++;
		mTimer->setInterval(200);
	} else {
		mState = 0;
		mTimer->setInterval(1200);
	}
	connect(mTimer, &QTimer::timeout, this, &RecordSign::animate);
	mTimer->start();
}

void RecordSign::stop()
{
	mTimer->stop();
}

void RecordSign::appear(int duration)
{
	QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
	opacityEffect->setOpacity(1);
	setGraphicsEffect(opacityEffect);
	QPropertyAnimation *opacityAnim = new QPropertyAnimation(this);
	opacityAnim->setTargetObject(opacityEffect);
	opacityAnim->setPropertyName("opacity");
	opacityAnim->setDuration(duration);
	opacityAnim->setStartValue(opacityEffect->opacity());
	opacityAnim->setEndValue(1);
	opacityAnim->setEasingCurve(QEasingCurve::OutQuad);
	connect(opacityAnim, &QPropertyAnimation::finished, this, &RecordSign::animate);
	opacityAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

void RecordSign::disappear(int duration)
{
	QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
	opacityEffect->setOpacity(1);
	setGraphicsEffect(opacityEffect);
	QPropertyAnimation *opacityAnim = new QPropertyAnimation(this);
	opacityAnim->setTargetObject(opacityEffect);
	opacityAnim->setPropertyName("opacity");
	opacityAnim->setDuration(duration);
	opacityAnim->setStartValue(opacityEffect->opacity());
	opacityAnim->setEndValue(0);
	opacityAnim->setEasingCurve(QEasingCurve::OutQuad);
	connect(opacityAnim, &QPropertyAnimation::finished, this, &RecordSign::animate);
	opacityAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

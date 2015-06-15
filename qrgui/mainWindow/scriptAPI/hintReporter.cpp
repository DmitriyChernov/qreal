#include "hintReporter.h"

#include <QtCore/QTimer>
#include <QtCore/QPropertyAnimation>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtGui/QMouseEvent>

#include <qrutils/graphicsUtils/animatedEffects.h>

#include <QDebug>

using namespace qReal;
using namespace gui;
using namespace graphicsUtils;

HintReporter::HintReporter(QWidget *parent, QString const &message, int const lifeTime)
	: QLabel(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setStyleSheet("background-color: #ffffff; border: 1px solid; border-radius: 7px; border-color: #303030;");
	setWordWrap(true);

	addHint(message);
	setMinimumSize(300, 50);
	setFixedSize(sizeHint());
	move(parent->width() - this->width(), 0);
	show();
	raise();

	mDuration = lifeTime / 2;

	QTimer::singleShot(mDuration, this, SLOT(disappear()));
	QTimer::singleShot(lifeTime, this, SLOT(deleteLater()));
}

void HintReporter::addHint(QString const &hint)
{
	QString const message = "<b>Подсказка :\n</b>" + hint;
	setText(message);
}

void HintReporter::disappear()
{
	AnimatedEffects::disappear(this, mDuration);
}

void HintReporter::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event)
	deleteLater();
}

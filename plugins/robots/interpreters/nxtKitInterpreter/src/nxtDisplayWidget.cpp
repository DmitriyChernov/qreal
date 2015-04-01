#include "nxtDisplayWidget.h"

#include "ui_nxtDisplayWidget.h"

#include <qrutils/graphicsUtils/painterInterface.h>
#include <qrkernel/exception/exception.h>
#include <qrkernel/logging.h>

using namespace nxt;
using namespace graphicsUtils;

NxtDisplayWidget::NxtDisplayWidget(QWidget *parent)
	: twoDModel::engine::TwoDModelDisplayWidget(parent)
	, mUi(new Ui::NxtDisplayWidget)
	, mBackground(":/icons/background.png", "PNG")
{
	mUi->setupUi(this);
}

NxtDisplayWidget::~NxtDisplayWidget()
{
	delete mUi;
}

bool NxtDisplayWidget::buttonIsDown(const QString &buttonPort) const
{
	if (buttonPort == "Left") {
		return mUi->leftButton->isDown();
	} else if (buttonPort == "Right") {
		return mUi->rightButton->isDown();
	} else if (buttonPort == "Enter") {
		return mUi->centralButton->isDown();
	} else if (buttonPort == "Escape") {
		return mUi->bottomButton->isDown();
	}

	QLOG_WARN() << "Button on port" << buttonPort << "is not supported by 2d model";

	return false;
}

void NxtDisplayWidget::setPainter(graphicsUtils::PainterInterface *painter)
{
	TwoDModelDisplayWidget::setPainter(painter);
	mUi->display->appendPainter(painter);
}

void NxtDisplayWidget::repaintDisplay()
{
	mUi->display->repaint();
}

int NxtDisplayWidget::displayWidth() const
{
	return mUi->display->width();
}

int NxtDisplayWidget::displayHeight() const
{
	return mUi->display->height();
}

void NxtDisplayWidget::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawImage(QRect(0, 0, width(), height()), mBackground);
}

#pragma once

#include <QtGui/QImage>

#include <qrutils/graphicsUtils/painterInterface.h>
#include <qrutils/graphicsUtils/paintWidget.h>

#include "twoDModel/engine/twoDModelDisplayWidget.h"

namespace Ui {
class TrikDisplayWidget;
}

namespace trik {

class TrikDisplayWidget : public twoDModel::engine::TwoDModelDisplayWidget
{
	Q_OBJECT

public:
	explicit TrikDisplayWidget(QWidget *parent = nullptr);
	~TrikDisplayWidget();

	void setPainter(graphicsUtils::PainterInterface *painter) override;

	void repaintDisplay() override;
	int displayWidth() const override;
	int displayHeight() const override;

	bool buttonIsDown(const QString &buttonId) const override;
	/// sets LED widget's color on 2D model display.
	void setLedColor(const QColor &color);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	Ui::TrikDisplayWidget *mUi;
	QImage mBackground;
};

}

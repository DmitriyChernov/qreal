#include "twoDModel/engine/twoDModelGuiFacade.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>

#include <qrutils/widgetFinder.h>

#include <twoDModel/engine/view/twoDModelWidget.h>

#include "src/engine/view/scene/twoDModelScene.h"

using namespace twoDModel::engine;

TwoDModelGuiFacade::TwoDModelGuiFacade(twoDModel::view::TwoDModelWidget &view)
	: mD2ModelWidget(view)
{
}

QWidget *TwoDModelGuiFacade::widget(QString const &type, QString const &name)
{
	return utils::WidgetFinder::widget(&mD2ModelWidget, type, name);
}

QWidget *TwoDModelGuiFacade::d2ModelSceneViewport()
{
	return mD2ModelWidget.scene()->views()[0]->viewport();
}

QWidget *TwoDModelGuiFacade::d2ModelWidget()
{
	return &mD2ModelWidget;
}

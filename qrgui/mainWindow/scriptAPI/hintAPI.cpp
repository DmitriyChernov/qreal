#include "hintAPI.h"

#include "scriptAPI.h"
#include "arrow.h"
#include "hintReporter.h"

using namespace qReal;
using namespace gui;

HintAPI::HintAPI(ScriptAPI *scriptAPI)
	: mScriptAPI(scriptAPI)
	, mHintReporter(nullptr)
	, mArrow(nullptr)
{
}

void HintAPI::addHint(QString const &message, int const lifeTime, QWidget *parent)
{
	mHintReporter = new HintReporter(parent, message, lifeTime);
}

void HintAPI::arrowToWidget(QWidget *target, qreal const angle, int const lifeTime, QWidget *parent)
{
	int const xcoord = mScriptAPI->guiFacade()->mainWindow()->mapFromGlobal(
			target->mapToGlobal(target->rect().topLeft())).x();
	int const ycoord = mScriptAPI->guiFacade()->mainWindow()->mapFromGlobal(
			target->mapToGlobal(target->rect().topLeft())).y();

	mArrow = new Arrow(target, angle, lifeTime, parent);
	mArrow->move(xcoord, ycoord);
}

void HintAPI::leadRound(QWidget *target, int const duration)
{
	QPoint topLeft = target->mapToGlobal(QPoint(0, 0));
	QPoint topRight = target->mapToGlobal(QPoint(target->width(), 0));
	QPoint botLeft = target->mapToGlobal(QPoint(0, target->height()));
	QPoint botRight = target->mapToGlobal(QPoint(target->width(), target->height()));

	mScriptAPI->virtualCursor()->move(topLeft);

	mScriptAPI->virtualCursor()->moveToPoint(topRight.x() - target->width()/6
			, topRight.y() + target->height()/6, duration/4);
	mScriptAPI->virtualCursor()->moveToPoint(botRight.x() - target->width()/6
			, botRight.y() - target->height()/6, duration/4);
	mScriptAPI->virtualCursor()->moveToPoint(botLeft.x() + target->width()/6
			, botLeft.y() - target->height()/6, duration/4);
	mScriptAPI->virtualCursor()->moveToPoint(topLeft.x() + target->width()/6
			, topLeft.y() + target->height()/6, duration/4);
}

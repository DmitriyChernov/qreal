#include "miniMapButton.h"


using namespace qReal;

MiniMapButton::MiniMapButton(EditorView *editorView)
{
	//setFixedSize(20, 20);
	this->raise();
	connect(this, SIGNAL(moveMiniMap(QPoint)), editorView, SLOT(moveMiniMap(QPoint)));
	//connect(this, SIGNAL(mouseReleaseEvent(QMouseEvent)), this, SLOT(moveMiniMap()));
}

void MiniMapButton::mouseMoveEvent(QMouseEvent *event)
{
	emit moveMiniMap(event->globalPos());
}

//void MiniMapButton::moveMiniMap()
//{
//	emit
//}


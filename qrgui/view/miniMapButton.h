#pragma once

#include <QtWidgets/QWidgetAction>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidgetAction>
#include <QtWidgets/QMouseEventTransition>
#include <QMouseEvent>

#include "editorView.h"

namespace qReal {

	class EditorViewMViface;
	class MainWindow;

	class MiniMapButton : public QPushButton
	{
		Q_OBJECT

	signals:
		void moveMiniMap(QPoint miniMapPos);

	public:
		explicit MiniMapButton(EditorView *parent = 0);

	private slots:
		void mouseMoveEvent (QMouseEvent *event);
//		void moveMiniMap();
	};
}

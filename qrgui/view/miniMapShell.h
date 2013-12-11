#pragma once

#include <QWidget>
#include "../mainwindow/miniMap.h"

namespace qReal {

	class MainWindow;
	class EditorViewScene;
	class EditorView;

	class MiniMapShell : public QWidget
	{
		Q_OBJECT
	public:
		explicit MiniMapShell(EditorView *parent, MiniMap *miniMap);

		void changeSize();
		void currentTabChanged();

	private:
		QVBoxLayout *mMainLayout;
		QHBoxLayout *mAuxiliaryLayout;
		QPushButton *mShowMiniMapButton;
		MiniMap *mMiniMap;
		int size;
		bool isMiniMapVisible;
	};
}

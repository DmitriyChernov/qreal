#include "miniMapShell.h"
#include "editorView.h"
#include "miniMapButton.h"

using namespace qReal;

MiniMapShell::MiniMapShell(EditorView *parent, MiniMap *miniMap) :
	QWidget()
	, mMainLayout(new QVBoxLayout())
	, mAuxiliaryLayout(new QHBoxLayout())
	, mMiniMap(miniMap)
	, size (SettingsManager::value("miniMapSize").toInt())
	, isMiniMapVisible(true)
	, mShowMiniMapButton(new MiniMapButton(parent))

{
	size = SettingsManager::value("MiniMapSize").toInt();

	mMiniMap->setParent(this);
	mShowMiniMapButton->setParent(this);

	setFixedSize(size+20, size+20);

	mMiniMap->setGeometry(0, 0, size, size);
	mShowMiniMapButton->setGeometry(0, 0, 20, 20);
	mShowMiniMapButton->raise();

	this->setLayout(mMainLayout);

	connect(this->mShowMiniMapButton, SIGNAL(released()), this, SLOT(turnMiniMap()));
}

void MiniMapShell::changeSize()
{
	size = SettingsManager::value("MiniMapSize").toInt();
	this->setFixedSize(size, size);
	mMiniMap->setGeometry(0, 0, size, size);
	setFixedSize(size+20, size+20);
}

void MiniMapShell::currentTabChanged()
{
}

void MiniMapShell::turnMiniMap()
{
	size = SettingsManager::value("MiniMapSize").toInt();
	setFixedSize(size+20, size+20);
	if (isMiniMapVisible){
		mShowMiniMapButton->setGeometry(0, 0, 20, 20);
		mMiniMap->show();
	} else {
		mShowMiniMapButton->setGeometry(size-20, size-20, 30, 30);
		mMiniMap->hide();
	}
	isMiniMapVisible= !isMiniMapVisible;
}

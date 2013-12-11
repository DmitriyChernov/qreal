#include "miniMapShell.h"
#include <QtWidgets/QVBoxLayout>
#include "editorView.h"
#include "../mainwindow/miniMap.h"
#include "../../qrkernel/settingsManager.h"

using namespace qReal;

MiniMapShell::MiniMapShell(EditorView *parent, MiniMap *miniMap) :
	QWidget()
	, mMainLayout(new QVBoxLayout())
	, mAuxiliaryLayout(new QHBoxLayout())
	, mMiniMap(miniMap)
	, size (SettingsManager::value("miniMapSize").toInt())
	, isMiniMapVisible(true)
	, mShowMiniMapButton(new QPushButton())

{
	mMiniMap->setParent(this);
	setFixedSize(size+10, size+10);
	mMiniMap->setFixedSize(size - 10, size - 10);
	mAuxiliaryLayout->addStretch();
	mAuxiliaryLayout->addWidget(mMiniMap);
	mAuxiliaryLayout->addSpacing(10);
	mMainLayout->addStretch();
	mMainLayout->addLayout(mAuxiliaryLayout);
	mMainLayout->addSpacing(10);

	mShowMiniMapButton->setGeometry(20, 0, 30, size);
	mShowMiniMapButton->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

	this->setLayout(mMainLayout);

	connect(this->mShowMiniMapButton, SIGNAL(pressed()), mMiniMap, SLOT(turnMiniMap()));
}

void MiniMapShell::changeSize()
{
	int size = SettingsManager::value("MiniMapSize").toInt();
	this->setFixedSize(size, size);
}

void MiniMapShell::currentTabChanged()
{
}

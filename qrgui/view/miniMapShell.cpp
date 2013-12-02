#include "miniMapShell.h"
#include <QtWidgets/QVBoxLayout>
#include "editorView.h"
#include "../mainwindow/miniMap.h"
#include "../../qrkernel/settingsManager.h"

using namespace qReal;

MiniMapShell::MiniMapShell(EditorView *parent, MiniMap *miniMap) :
    QWidget()
    , mMainLayout(new QVBoxLayout())
    , mMiniMap(miniMap)
{
    mMiniMap->setParent(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    //miniMap->changeSource(0);
    mMainLayout->addWidget(mMiniMap);
    mMainLayout->addWidget(new QLineEdit());
    this->setLayout(mMainLayout);
}

void MiniMapShell::changeSize()
{
//    int size = SettingsManager::value("MiniMapSize").toInt();
//    this->setFixedSize(size, size);
}

void MiniMapShell::currentTabChanged()
{
//    mMiniMap->changeSource(0);
}

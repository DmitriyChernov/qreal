#include "miniMap.h"
#include "mainWindow.h"
#include "../view/editorView.h"
#include "../view/editorViewScene.h"
#include "../../qrkernel/settingsManager.h"

using namespace qReal;

MiniMap::MiniMap(QWidget *parent)
		: QGraphicsView(parent)
		, mEditorView(NULL)
		, mMode(None)
        , showMiniMap(TRUE)
{}

void MiniMap::init(qReal::MainWindow *window)
{
	mWindow = window;

	setRenderHint(QPainter::Antialiasing, true);

    int size = SettingsManager::value("MiniMapSize").toInt();

	setInteractive(false);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(size,size);
}

void MiniMap::changeSource(int index)
{
	clear();
	if (index != -1) {
		setCurrentScene();
	} else {
		setScene(NULL);
	}
}

void MiniMap::setCurrentScene()
{
	mEditorView = mWindow->getCurrentTab();
	if (mEditorView == NULL) {
		return;
	}

	EditorViewScene *editorViewScene = static_cast<EditorViewScene *>(mEditorView->scene());
	if (editorViewScene->mainWindow() != NULL) {
		setScene(editorViewScene);
		// can affect zoom - need to change it if we make another desision about it
		connect(editorViewScene, SIGNAL(sceneRectChanged(QRectF)), this, SLOT(showScene()));
	}
}

void MiniMap::setScene(QGraphicsScene *scene)
{
	QGraphicsView::setScene(scene);
	showScene();
}

void MiniMap::showScene()
{
	if (scene() != NULL) {
		setSceneRect(scene()->sceneRect());
		fitInView(sceneRect(), Qt::KeepAspectRatio);
	}
}

void MiniMap::ensureVisible(QList<QRectF> region)
{
	foreach (QRectF rect, region) {
		fitInView(rect, Qt::KeepAspectRatio);
	}
}

void MiniMap::clear()
{
	mEditorViewRect = QRectF();
	mEditorView = NULL;
}

QRectF MiniMap::getNewRect()
{
	QRect visibleRect = mEditorView->viewport()->rect();
	QRectF newRect = mEditorView->mapToScene(visibleRect).boundingRect();

	newRect.setTopLeft(newRect.topLeft() - QPointF(2, 2));
	newRect.setBottomRight(newRect.bottomRight() + QPointF(2, 2));

	return newRect;
}

void MiniMap::wheelEvent(QWheelEvent *event)
{
	setInteractive(true);
	QGraphicsView::wheelEvent(event);
	setInteractive(false);
}

void MiniMap::mousePressEvent(QMouseEvent *event)
{
	if (mEditorView != NULL) {
		mMode = Drag;
		mEditorView->centerOn(mapToScene(event->pos()));
	}
	QGraphicsView::mousePressEvent(event);
}

void MiniMap::mouseMoveEvent(QMouseEvent *event)
{
	if (mEditorView != NULL && mMode == Drag) {
		mEditorView->centerOn(mapToScene(event->pos()));
	}
	QGraphicsView::mouseMoveEvent(event);
}

void MiniMap::mouseReleaseEvent(QMouseEvent *event)
{
	mMode = None;
	QGraphicsView::mouseReleaseEvent(event);
}

void MiniMap::resizeEvent(QResizeEvent *event)
{
	showScene();
	QGraphicsView::resizeEvent(event);
}

void MiniMap::drawForeground(QPainter *painter, QRectF const &rect)
{
	QGraphicsView::drawForeground(painter, rect);
	painter->setPen(Qt::yellow);

	if (mEditorView != NULL) {
		mEditorViewRect = getNewRect();
	}
	drawNonExistentAreas(painter, rect);
	painter->drawRect(mEditorViewRect);
}

void MiniMap::drawNonExistentAreas(QPainter *painter, QRectF const &rect)
{
	QList<QRectF> areas = getNonExistentAreas(rect);
	foreach (QRectF area, areas) {
		painter->fillRect(area, Qt::lightGray);
	}
}

QList<QRectF> MiniMap::getNonExistentAreas(QRectF const &rect)
{
	QRectF existent = rect.intersected(sceneRect());

	QList<QRectF> areas;
	areas << QRectF(rect.topLeft(), existent.bottomLeft())
			<< QRectF(rect.topLeft(), QPointF(rect.right(), existent.top()))
			<< QRectF(existent.topRight(), rect.bottomRight())
			<< QRectF(QPointF(rect.left(), existent.bottom()), rect.bottomRight());

	return areas;
}

void MiniMap::turnMiniMap()
{
    if (showMiniMap){
        this->show();
    } else {
        this->hide();
    }
    showMiniMap = !showMiniMap;
}

void MiniMap::changeSize()
{
    int size = SettingsManager::value("MiniMapSize").toInt();
    this->setFixedSize(size, size);
}

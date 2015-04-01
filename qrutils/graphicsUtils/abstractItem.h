#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsView>
#include <QtXml/QDomDocument>

#include "qrutils/utilsDeclSpec.h"

const int drift = 15;
const int resizeDrift = 10;
const int scalingDrift = 10;
const int scalingRect = 6;

namespace graphicsUtils {

class QRUTILS_EXPORT AbstractItem : public QGraphicsObject
{
public:
	enum DragState {
		None
		, TopLeft
		, TopRight
		, BottomLeft
		, BottomRight
		, Ctrl
	};

	explicit AbstractItem(QGraphicsItem *parent = 0);

	virtual QRectF boundingRect() const = 0;
	virtual QRectF realBoundingRect() const;
	virtual QRectF calcNecessaryBoundingRect() const;
	virtual QPainterPath realShape() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	virtual void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) = 0;
	virtual void drawExtractionForItem(QPainter *painter);
	virtual void drawFieldForResizeItem(QPainter *painter);
	virtual void setPenBrushForExtraction(QPainter *painter, const QStyleOptionGraphicsItem *option);
	virtual void setPenBrushDriftRect(QPainter *painter);

	static QStringList getPenStyleList();
	static QStringList getBrushStyleList();

	QPen pen() const;
	QBrush brush() const;
	void setBrush(const QBrush &brush);
	void setPen(const QPen &pen);

	virtual void setPenStyle(const QString &text);
	virtual void setPenWidth(int width);
	virtual void setPenColor(const QString &text);
	virtual void setBrushStyle(const QString &text);
	virtual void setBrushColor(const QString &text);
	virtual void setBrush(const QString &brushStyle, const QString &brushColor);
	virtual void setPen(const QString &penStyle, int width, const QString &penColor);
	virtual void setPenBrush(const QString &penStyle, int width, const QString &penColor, const QString &brushStyle
			, const QString &brushColor);

	QPointF getX1andY1(void);
	QPointF getX2andY2(void);

	void setX1andY1(qreal x, qreal y);
	void setX1andY2(qreal x, qreal y);
	void setX2andY1(qreal x, qreal y);
	void setX2andY2(qreal x, qreal y);
	void setCoordinates(const QRectF &pos);

	virtual void reshapeRectWithShift();
	virtual void changeDragState(qreal x, qreal y);
	DragState getDragState() const;

	virtual void calcResizeItem(QGraphicsSceneMouseEvent *event);
	virtual void resizeItem(QGraphicsSceneMouseEvent *event);
	void reverseOldResizingItem(QPointF begin, QPointF end);

	//for save to xml
	virtual void setXandY(QDomElement& dom, const QRectF &rect);
	QDomElement setPenBrushToDoc(QDomDocument &document, const QString &domName);
	virtual QRectF sceneBoundingRectCoord(const QPoint &topLeftPicture);
	void readPenBrush(const QDomElement &docItem);

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

	/// Returns a unique identifier of an item if it was assigned in the model.
	QString id() const;

	/// Sets a unique identifier of an item.
	void setId(const QString &id);

	void setEditable(bool editable);
	bool editable() const;

protected:
	virtual void serialize(QDomElement &element);
	virtual void deserialize(const QDomElement &element);

	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

	DragState mDragState;
	QRectF mBoundingRect;
	QPen mPen;
	QBrush mBrush;
	qreal mX1;
	qreal mY1;
	qreal mX2;
	qreal mY2;
	QGraphicsView *mView;
	QString mId;
	bool mEditable;
};

}

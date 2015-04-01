#include "rectangularRegion.h"

using namespace twoDModel::items;

RectangularRegion::RectangularRegion(QGraphicsItem *parent)
	: RegionItem(parent)
{
}

QPainterPath RectangularRegion::shape() const
{
	QPainterPath result;
	result.addRect(boundingRect());
	return result;
}

QString RectangularRegion::regionType() const
{
	return "rectangle";
}

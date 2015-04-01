#pragma once

#include "rotater.h"

namespace graphicsUtils {

class Rotater;

class QRUTILS_EXPORT RotateItem : public AbstractItem
{
public:
	explicit RotateItem(QGraphicsItem *parent = 0);

	/// Can be overrided to determine rotater`s position: it will be placed to the center of rect`s right side.
	virtual QRectF rect() const;

	/// Returns a reference to a rotater graphics item.
	Rotater &rotater();

protected:
	/// Must be called in subclass to initialize rotater position and so on.
	/// Can`t be called here in constructor because it uses virtual methods.
	void init();

	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
	bool theOnlySelectedRotateItem(bool thisSelected) const;


private:
	Rotater mRotater;
};

}

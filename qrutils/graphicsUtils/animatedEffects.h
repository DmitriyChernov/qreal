#pragma once

#include <QtWidgets/QGraphicsItem>

#include "qrutils/utilsDeclSpec.h"

namespace graphicsUtils {

/// Highlights the given item animating its opacity.
class QRUTILS_EXPORT AnimatedEffects
{
public:
	/// Highlights the given item animating its opacity.
	static void highlight(QGraphicsItem * const item);

	/// The given widget disappear with opacity animation for duration.
	static void disappear(QWidget *widget, int duration);

	/// The given widget appear with opacity animation for duration.
	static void appear(QWidget *widget, int duration);
};

}

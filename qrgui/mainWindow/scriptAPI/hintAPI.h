#pragma once

#include "hintReporter.h"
#include "arrow.h"

#include <toolPluginInterface/usedInterfaces/hintInterface.h>

namespace qReal {

namespace gui {

class ScriptAPI;

/// This class provides API to class HintReporter. HintAPI allows to make hint widgets, defined by message,
/// parent widget, which will show hint, and duration of opacity effect.
class HintAPI  : public QObject, public HintInterface
{
	Q_OBJECT

public:
	HintAPI(ScriptAPI *ScriptAPI);

	/// Sends message as HintReporter in parent widget. Exists for lifeTime.
	Q_INVOKABLE void addHint(QString const &message, int const lifeTime, QWidget *parent);

	/// Draws arrow near target with parent widget with angle. Exists for lifeTime.
	Q_INVOKABLE void arrowToWidget(QWidget *target, qreal const angle, int const lifeTime, QWidget *parent);

	/// Lead virtual cursor round the widget.
	Q_INVOKABLE void leadRound(QWidget *target, int const duration);

private:
	ScriptAPI *mScriptAPI;
	HintReporter *mHintReporter;
	Arrow *mArrow;
};

}
}

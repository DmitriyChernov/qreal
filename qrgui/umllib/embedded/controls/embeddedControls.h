#pragma once

#include <QSet>
#include <QPair>
#include <QMultiMap>

#include <QFontMetrics>
#include <QGraphicsProxyWidget>

#include "embeddedControl.h"
#include "controlsDisposer.h"
#include "../../element.h"

#include "../../kernel/ids.h"

class Item;
class ControlsDisposer;
class EmbeddedControls : public QObject, public QGraphicsItem {
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
	public:
		QRectF boundingRect() const;
		void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

		static bool existsInstance(Element *element);
		static void deleteInstance(Element *element);
		static void createInstance(Element *element, const qReal::EditorManager &editorManager);

	public slots:
		void switchFolding(const bool request);
	signals:
		void foldingSwitched(bool);

	private:
		EmbeddedControls(
			Element *element,
			const qReal::EditorManager &editorManager
		);

		void registerControls(Element *element);
		void initializeItems(Element *element, const qReal::EditorManager &editorManager);

		/* Data */
		Element *element;
		QList<Item> items;
		ControlsDisposer *disposer;
		QRectF computedBoundingRect;

		/* Static */	//todo: следует сделать отдельным объектом
		static QSet<qReal::Id> forbiddenTypes;
		static QMultiMap<qReal::Id, QString> forbiddenProperties;
		static QMap<Element*, EmbeddedControls*> elementsToControls;

		static void loadSettings();
		static bool checkPermission(Element *element);

		/* Assist */	//todo: следует перенести куда-нибудь
		static qReal::Id extractElementId(const qReal::Id &id);
};

/* Measurable pair of embeddedControl* and ProxyWidget* */

class Item : public QPair<EmbeddedControl*, QGraphicsProxyWidget*> {
	public:
		Item(EmbeddedControl* first, QGraphicsProxyWidget* second) :
			QPair<EmbeddedControl*, QGraphicsProxyWidget*>(first, second) {}

		qreal length() const {
			return textLength() + boundingLength();
		}
		qreal textLength() const {
			const EmbeddedControl* control = first;
			const QGraphicsProxyWidget* widget = second;
			QFontMetrics metrics(widget->font());
			return metrics.width(control->getPropertyName());
		}
		qreal boundingLength() const {
			const QGraphicsProxyWidget* widget = second;
			const QRectF bounding= widget->boundingRect();
			return bounding.right() - bounding.left();
		}
		bool operator<(const Item that) {
			return this->boundingLength() < that.boundingLength();
			//todo: когда будет текст, нужно будет вызывать length()
		}
};

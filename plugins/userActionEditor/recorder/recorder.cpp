#include "recorder.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLayout>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QTreeWidget>
#include <QtCore/QMimeData>
#include <QtCore/QFile>

#include <qrutils/outFile.h>

using namespace qReal;
using namespace userAction;
using namespace utils;

Id const startingElementType = Id("userActionEditor", "userActionDiagram", "InitialNode");

UserActionRecorderPlugin::UserActionRecorderPlugin()
	: QObject()
	, mStartAction(new QAction(this))
	, mStopAction(new QAction(this))
	, mRecordShell(nullptr)
	, mScriptGenerator(nullptr)
	, mIsRecording(false)
{
	mStartAction->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F9));
	mStopAction->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F10));
}

void UserActionRecorderPlugin::init(PluginConfigurator const &configurator)
{
	mEventsFileName = "events.xml";

	connect(mStartAction, &QAction::triggered, this, &UserActionRecorderPlugin::start);
	connect(mStopAction, &QAction::triggered, this, &UserActionRecorderPlugin::stop);

	connect(mStartAction, &QAction::triggered
			, [configurator, this]() {
		connect(&configurator.systemEvents(), &SystemEvents::lowLevelEvent
				, this, &UserActionRecorderPlugin::lowLevelEvent);
		this->start();
	});

	connect(mStopAction, &QAction::triggered
			, [configurator, this]() {
		disconnect(&configurator.systemEvents(), &SystemEvents::lowLevelEvent
				, this, &UserActionRecorderPlugin::lowLevelEvent);
		if (mRecordElementId.toString() != "qrm:/") {
			configurator.logicalModelApi().setPropertyByRoleName(mRecordElementId
					, mUserActioDomDocument.toString()
					, "UserActions");
		}
	});

	connect(&configurator.systemEvents(), &qReal::SystemEvents::logicalElementAdded
			, [this](qReal::Id const &id) {
		if (id.diagram() == "UserActionDiagram"
				&& id.editor() == "UserActionEditor"
				&& id.element() == "Record") {
			mRecordElementId = id;
		}
	});

	mRecordShell = new RecordShell(configurator.mainWindowInterpretersInterface().windowWidget());

	mScriptGenerator = new FromXmlToScript();
}

UserActionRecorderPlugin::~UserActionRecorderPlugin()
{
}

void UserActionRecorderPlugin::start()
{
	mUserActioDomDocument.clear();

	mRecordShell->show();
	//mRecordSign->animate();
	mRootElement = mUserActioDomDocument.createElement("UserActions");
}

void UserActionRecorderPlugin::stop()
{
	mRecordShell->hide();
	//mRecordSign->stop();
	mUserActioDomDocument.appendChild(mRootElement);

	OutFile events(mEventsFileName);

	events() << mUserActioDomDocument.toString();
	events.flush();

	mScriptGenerator->generateScript(mEventsFileName);
}

void UserActionRecorderPlugin::lowLevelEvent(QObject *obj, QEvent *e)
{
	QDomElement eventTag = mUserActioDomDocument.createElement("Event");

	if (!QString::compare(obj->metaObject()->className(), "QWidgetWindow")) {
		if (obj->objectName() == mActiveWindow) {
			mActiveWindow = obj->objectName();
			eventTag.setAttribute("Type", "ActiveWindowChange");
			eventTag.setAttribute("Reciever", obj->objectName());
		} else {
			return;
		}
	} else if (!QString::compare(obj->metaObject()->className(), "qReal::EditorViewScene")
				&& e->type() == QEvent::GraphicsSceneDrop) {
		QGraphicsSceneDragDropEvent* event = dynamic_cast<QGraphicsSceneDragDropEvent*>(e);
		eventTag.setAttribute("Type", "Drop");
		eventTag.setAttribute("RecieverType", "EditorViewScene");
		eventTag.setAttribute("Xcoord", static_cast<int>(event->scenePos().x()));
		eventTag.setAttribute("Ycoord", static_cast<int>(event->scenePos().y()));

		QByteArray itemData = event->mimeData()->data("application/x-real-uml-data");
		QDataStream inStream(&itemData, QIODevice::ReadOnly);
		QString uuid;
		inStream >> uuid;
		const Id id = Id::loadFromString(uuid);
		eventTag.setAttribute("Id","qrm:/"
							  + id.editor() + "/"
							  + id.diagram() + "/"
							  + id.element());
		mRootElement.appendChild(eventTag);
		return;
	}

	if (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease) {
		QMouseEvent* event = dynamic_cast<QMouseEvent*>(e);

		eventTag.setAttribute("Type", "Mouse");
		eventTag.setAttribute("RecieverType", obj->metaObject()->className());
		eventTag.setAttribute("RecieverName", obj->objectName());

		QString button;
		switch(event->button()){
			case Qt::LeftButton:
				button = "left";
				break;
			case Qt::RightButton:
				button = "right";
				break;
			case Qt::MidButton:
				button = "mid";
				break;
			default:
				return;
		}

		eventTag.setAttribute("Button", button);

		QString action;
		switch(e->type()){
			case QEvent::MouseButtonPress:
				action = "Press";
				break;
			case QEvent::MouseButtonRelease:
				action = "Release";
				if (!QString::compare(obj->metaObject()->className(), "QScrollBar")) {
					QScrollBar *scrollBar = dynamic_cast<QScrollBar *>(obj);
					eventTag.setAttribute("Value", scrollBar->value());
				}

				break;
			default:
				return;
		}
		if (action == ""){
			return;
		}
		eventTag.setAttribute("Action", action);
		if (dynamic_cast<QWidget *>(obj)) {
			QWidget *widget = dynamic_cast<QWidget *>(obj);
			eventTag.setAttribute("Index",  widget->parentWidget()->children().indexOf(widget));
			addParentChain(&eventTag, widget, event);
		}

	} else if (e->type() == QEvent::KeyRelease) {
		QKeyEvent* event = static_cast<QKeyEvent *>(e);
		if (event->key() == QKeyEvent::Enter || event->key() == Qt::Key_Return) {
			return;
		}

		eventTag.setAttribute("Type", "Key");
		eventTag.setAttribute("KeyName", event->text());
		eventTag.setAttribute("Modifiers", event->modifiers());
		if (event->text() == ""){
			return;
		}

	} else if (e->type() == QEvent::Wheel) {
		QWheelEvent* event = static_cast<QWheelEvent *>(e);

		eventTag.setAttribute("Type", "Wheel");
		eventTag.setAttribute("Delta", event->delta());
	} else {
		return;
	}

	mRootElement.appendChild(eventTag);
}

void UserActionRecorderPlugin::addHintEvent(QString const &hint)
{
	QDomElement hintEvent = mUserActioDomDocument.createElement("Event");

	hintEvent.setAttribute("Type", "Hint");
	hintEvent.setAttribute("Message", hint);

	mRootElement.appendChild(hintEvent);
}

void UserActionRecorderPlugin::addParentChain(QDomElement *eventTag, QWidget *widget, QEvent *event)
{
	QWidget *parentWidget = widget->parentWidget();
	while (parentWidget) {
		QDomElement domParent = mUserActioDomDocument.createElement("Parent");
		domParent.setAttribute("Type", parentWidget->metaObject()->className());
		domParent.setAttribute("ObjectName", parentWidget->objectName());
		domParent.setAttribute("Index", parentWidget->children().indexOf(widget));

		if (static_cast<QMouseEvent *>(event)) {
			QMouseEvent* mouseEvent = static_cast<QMouseEvent *>(event);
			if (!QString::compare(parentWidget->metaObject()->className(), "qReal::EditorView")) {
				domParent.setAttribute("Xcoord", parentWidget->mapFromGlobal(mouseEvent->globalPos()).x());
				domParent.setAttribute("Ycoord", parentWidget->mapFromGlobal(mouseEvent->globalPos()).y());
			} else if (!QString::compare(parentWidget->metaObject()->className(), "QComboBox")) {
				QComboBox *comboBox = dynamic_cast<QComboBox *>(parentWidget);
				QPoint targetPoint = QPoint(comboBox->view()->mapFromGlobal(mouseEvent->globalPos()));
				domParent.setAttribute("ItemSelected", comboBox->view()->indexAt(targetPoint).row());
			} else if (!QString::compare(parentWidget->metaObject()->className(), "QtTreePropertyBrowser")) {
				QTreeWidget * const editorTree = parentWidget->findChild<QTreeWidget *>();
				QString const propertyName = editorTree->itemAt(mouseEvent->pos())->text(0);
				domParent.setAttribute("PropertyName", propertyName);
			} else if (!QString::compare(parentWidget->metaObject()->className(), "graphicsUtils::AbstractView")) {
				domParent.setAttribute("Xcoord", parentWidget->mapFromGlobal(mouseEvent->globalPos()).x());
				domParent.setAttribute("Ycoord", parentWidget->mapFromGlobal(mouseEvent->globalPos()).y());
			}
		}

		eventTag->appendChild(domParent);
		widget = parentWidget;
		parentWidget = parentWidget->parentWidget();
	}
}

QList<ActionInfo> UserActionRecorderPlugin::actions()
{
	return { qReal::ActionInfo(mStartAction, "interpreters", "tools")
			, qReal::ActionInfo(mStopAction, "interpreters", "tools")
	};
}

QList<HotKeyActionInfo> UserActionRecorderPlugin::hotKeyActions()
{
	return { qReal::HotKeyActionInfo("UserActionRecorder.Start", QObject::tr("Start recording"), mStartAction)
		, qReal::HotKeyActionInfo("UserActionRecorder.Stop", QObject::tr("Stop deployment"), mStopAction)
	};
}

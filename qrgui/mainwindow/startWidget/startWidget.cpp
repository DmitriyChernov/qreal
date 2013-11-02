#include <QtWidgets/QTabWidget>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtCore>

#include "../../../qrkernel/settingsManager.h"
#include "../../dialogs/suggestToCreateDiagramDialog.h"
#include "../mainwindow/mainWindow.h"
#include "startWidget.h"
#include "suggestToCreateDiagramWidget.h"
#include "recentProjectsListWidget.h"
#include "recentProjectItem.h"

using namespace qReal;

StartWidget::StartWidget(MainWindow *mainWindow, ProjectManager *projectManager)
	: QWidget()
	, mMainWindow(mainWindow)
	, mProjectManager(projectManager)
	, mProjectListSize(5)
	, mProjectsLayout(new QVBoxLayout())
	, mSessionsLayout(new QHBoxLayout())
{

    Id const theOnlyDiagram = mMainWindow->editorManager().theOnlyDiagram();

	QString openLinkText = QString("<a href='Open project...'>%1</a>").arg(tr("<font color='black'>Open project...</font>"));
	QLabel *openLink = new QLabel(openLinkText, this);

	QString creatLinkText = QString("<a href='Create new project'>%1</a>").arg(tr("<font color='black'>Create new project</font>"));
	QLabel *createLink = new QLabel(creatLinkText, this);

	QLabel *sessions = new QLabel(tr("<font size = 14>Sessions</font>"));
	QLabel *recentProjects = new QLabel(tr("<font size = 14>Recent projects</font>"));

	initRecentProjects();

	QVBoxLayout *sessionsLayout = new QVBoxLayout();

	QVBoxLayout *recentProjectsLayout = new QVBoxLayout();

	QHBoxLayout *mainLayout = new QHBoxLayout();

	sessionsLayout->addWidget(sessions);
	sessionsLayout->addLayout(mSessionsLayout);
	sessionsLayout->addWidget(openLink);
	sessionsLayout->addWidget(createLink);
	sessionsLayout->addStretch(0);

	recentProjectsLayout->addWidget(recentProjects);
	recentProjectsLayout->addLayout(mProjectsLayout);
	recentProjectsLayout->addStretch(0);

	mainLayout->addLayout(sessionsLayout);
	QWidget *horizontalLineWidget = new QWidget;
	horizontalLineWidget->setFixedWidth(1);
	horizontalLineWidget->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Expanding);
	horizontalLineWidget->setStyleSheet(QString("background-color: #c0c0c0;"));
	mainLayout->addWidget(horizontalLineWidget);
	mainLayout->addLayout(recentProjectsLayout);

	setLayout(mainLayout);
	QPalette Pal(palette());
	QColor color = QColor::fromHsl (180, 50, 240, 255);
	Pal.setColor(QPalette::Background, color);
	this->setAutoFillBackground(true);
	this->setPalette(Pal);

	connect(createLink, SIGNAL(linkActivated(QString)), this, SLOT(createProjectWithDiagram()));
	connect(openLink, SIGNAL(linkActivated(QString)), this, SLOT(openExistingProject()));

}

void StartWidget::openRecentProject(QString const &fileName)
{
    if(mProjectManager->open(fileName)){
		emit closeStartTab(0);
	}
}

void StartWidget::openExistingProject()
{
    if(mProjectManager->suggestToOpenExisting()){
		emit closeStartTab(0);
	}
}

void StartWidget::createProjectWithDiagram()
{
    SuggestToCreateDiagramWidget *diagrams = new SuggestToCreateDiagramWidget(mMainWindow, this);
	if (diagrams->count()==1){
        mMainWindow->createProject(diagrams->itemAt(0));
	} else {
        mProjectManager->suggestToCreateDiagram();
	}
	emit closeStartTab(0);
}

void StartWidget::initRecentProjects()
{
	int i=0;
	QString recentProjects = SettingsManager::value("recentProjects").toString();
	foreach (QString const &project, recentProjects.split(";", QString::SkipEmptyParts)) {
		QString const name = project.split("/").last().split("\\").last();
		if("autosave.qrs"== name){
			QString currentProject = QString("<a href='%2'>%1</a>").arg(tr("<font color='black'>•  default (current session)</font>"), project);
			QLabel *currentProjectLabel = new QLabel(currentProject, this);
			mSessionsLayout->addSpacing(25);
			mSessionsLayout->addWidget(currentProjectLabel);
		} else {
			RecentProjectItem *projectWidget = new RecentProjectItem(this, name, project);
			mProjectsLayout->addWidget(projectWidget);
			i++;
			if (i == mProjectListSize)
				break;
		}
	}
}

void StartWidget::openInterpretedDiagram()
{
        hide();
        QString const fileName = mProjectManager->openFileName(tr("Select file with metamodel to open"));
        ProxyEditorManager &editorManagerProxy = mMainWindow->editorManagerProxy();

        if (!fileName.isEmpty() && mProjectManager->open(fileName)) {
                editorManagerProxy.setProxyManager(new InterpreterEditorManager(fileName));
                QStringList interpreterDiagramsList;
                foreach (Id const &editor, editorManagerProxy.editors()) {
                        foreach (Id const &diagram, editorManagerProxy.diagrams(editor)) {
                                QString const diagramNodeName = editorManagerProxy.diagramNodeName(editor.editor(), diagram.diagram());
                                if (diagramNodeName.isEmpty()) {
                                        continue;
                                }

                                interpreterDiagramsList.append("qrm:/" + editor.editor() + "/"
                                                + diagram.diagram() + "/" + diagramNodeName);
                        }
                }

                foreach (QString const &interpreterIdString, interpreterDiagramsList) {
                        // TODO: ???
                        mMainWindow->models()->repoControlApi().exterminate();
                        mMainWindow->models()->reinit();
                        mMainWindow->loadPlugins();
                        mMainWindow->createDiagram(interpreterIdString);
                }
        } else {
                show();
                editorManagerProxy.setProxyManager(new EditorManager());
        }
}

void StartWidget::createInterpretedDiagram()
{
        hide();
        ProxyEditorManager &editorManagerProxy = mMainWindow->editorManagerProxy();
        editorManagerProxy.setProxyManager(new InterpreterEditorManager(""));
        bool ok = false;
        QString name = QInputDialog::getText(this, tr("Enter the diagram name:"), tr("diagram name:")
                        , QLineEdit::Normal, "", &ok);
        while (ok && name.isEmpty()) {
                name = QInputDialog::getText(this, tr("Enter the diagram name:"), tr("diagram name:")
                                , QLineEdit::Normal, "", &ok);
        }

        if (ok) {
                QPair<Id, Id> editorAndDiagram = editorManagerProxy.createEditorAndDiagram(name);
                mMainWindow->addEditorElementsToPalette(editorAndDiagram.first, editorAndDiagram.second);
                mMainWindow->models()->repoControlApi().exterminate();
                mMainWindow->models()->reinit();
                mMainWindow->loadPlugins();
        } else {
                show();
                editorManagerProxy.setProxyManager(new EditorManager());
        }
}

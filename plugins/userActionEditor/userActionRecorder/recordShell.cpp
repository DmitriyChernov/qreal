#include "recordShell.h"

#include <QDebug>

using namespace userAction;

RecordShell::RecordShell(QWidget *parent)
	: QWidget(parent)
	, mLayout(new QHBoxLayout(this))
	, mAddHint(new QPushButton(this))
	, mHint(new QTextEdit(this))
	, mRecordSign(new RecordSign(this))
{
	mAddHint->setText("Add hint message");
	mHint->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	mLayout->addWidget(mRecordSign);
	mLayout->addWidget(mHint);
	mLayout->addWidget(mAddHint);
	setLayout(mLayout);

	connect(mAddHint, &QPushButton::clicked, this, &RecordShell::addHintEvent);
	setFixedSize(400, 100);
	setWindowFlags(Qt::WindowStaysOnTopHint);
	raise();
	move(QPoint(10,10));

	mAddHint->setObjectName("addHintButton");
	mHint->setObjectName("hintTextEdit");
}

void RecordShell::addHintEvent()
{
	mHint->clear();
	emit hintAdded(mHint->toPlainText());
}

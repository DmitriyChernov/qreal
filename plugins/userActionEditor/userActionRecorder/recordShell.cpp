#include "recordShell.h"

using namespace userAction;

RecordShell::RecordShell(QWidget *parent)
	: QWidget(parent)
	, mLayout(new QVBoxLayout(this))
	, mAddHint(new QPushButton(this))
	, mHint(new QTextEdit(this))
	, mRecordSign(new RecordSign(this))
{
	mAddHint->setText("Add hint message");
	mAddHint->setFixedSize(30, 30);
	mAddHint->raise();
	mAddHint->show();
	mHint->setFixedWidth(200);
	mHint->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	mHint->raise();
	mHint->show();

	mLayout->addWidget(mRecordSign);
	mLayout->addWidget(mHint);
	mLayout->addWidget(mAddHint);
	setLayout(mLayout);

	connect(mAddHint, &QPushButton::clicked, this, &RecordShell::addHintEvent);
}

void RecordShell::addHintEvent()
{
	qDebug()<<mHint->placeholderText();
	emit hintAdded(mHint->placeholderText());
}

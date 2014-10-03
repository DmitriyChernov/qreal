#pragma once

#include "qrtext/lua/ast/expression.h"

namespace qrtext {
namespace lua {
namespace ast {

class QRTEXT_EXPORT IndexingExpression : public Expression
{
public:
	IndexingExpression(QSharedPointer<Expression> const &table, QSharedPointer<Expression> const &indexer)
		: mTable(table), mIndexer(indexer)
	{
	}

	QSharedPointer<Expression> const &table() const {
		return mTable;
	}

	QSharedPointer<Expression> const &indexer() const {
		return mIndexer;
	}

	QList<QSharedPointer<Node>> children() const override
	{
		return {mTable, mIndexer};
	}

private:
	QSharedPointer<Expression> mTable;
	QSharedPointer<Expression> mIndexer;
};

}
}
}

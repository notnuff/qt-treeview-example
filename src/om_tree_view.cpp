#include "om_tree_view.h"
#include <QPainter>
#include <QStyleOptionViewItem>

namespace {
constexpr int cBranchArrowOffset = 4;
}

OMTreeView::OMTreeView(QWidget *parent) : QTreeView(parent) { }

void OMTreeView::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    QTreeView::drawBranches(painter, rect, index);

    drawNestedBranches(painter, rect, index);
}

void OMTreeView::drawNestedBranches(QPainter *painter, const QRect &rect,
                                    const QModelIndex &index) const
{
    painter->save();

    painter->setPen(QPen(Qt::gray, 1));

    drawRootVLine(painter, rect, index);
    drawSubBranch(painter, rect, index);

    painter->restore();
}
void OMTreeView::drawRootVLine(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{

    auto parent = index.parent();
    if (!parent.isValid()) {
        parent = index;
    }

    const auto parentsRowCount = index.model()->rowCount(parent.parent());
    const auto isFirstParentElement = parent.row() == 0;
    const auto isLastParentElement = parent.row() == parentsRowCount - 1;

    const auto x = rect.left() + indentation() / 2;

    if (parent == index) {
        QStyleOptionViewItem opt;
        opt.rect = rect;

        QRect arrow;

        if (index.model()->rowCount(index) > 0) {
            arrow = style()->subElementRect(QStyle::SE_TreeViewDisclosureItem, &opt, this);
            arrow.setTop(arrow.top() + cBranchArrowOffset);
            arrow.setBottom(arrow.bottom() - cBranchArrowOffset);
        } else {
            arrow = {rect.center(), rect.center()};
        }

        if (!isFirstParentElement) {
            painter->drawLine(x, rect.top(), x, arrow.top());
        }

        if (!isLastParentElement) {
            painter->drawLine(x, arrow.bottom(), x, rect.bottom());
        }

    } else {
        if (!isLastParentElement) {
            painter->drawLine(x, rect.top(), x, rect.bottom());
        }
    }
}
void OMTreeView::drawSubBranch(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    const auto x = getSubBranchX(rect, index);
    const auto &rc = visualRect(index);

    painter->drawLine(x, rc.center().y(), rc.left(), rc.center().y());

    if (const auto &parent = index.parent(); parent.isValid()) {
        const auto rowCount = parent.model()->rowCount(parent);
        const auto isLastChild = index.row() == rowCount - 1;

        const auto y = isLastChild ? rc.center().y() : rc.bottom();

        painter->drawLine(x, rc.top(), x, y);
    }
}

int OMTreeView::getSubBranchX(const QRect &rect, const QModelIndex &index) const
{
    if (const auto &parent = index.parent(); parent.isValid()) {
        const auto parentRect = visualRect(parent);
        const auto thisRect = visualRect(index);
        const auto xMid = (parentRect.left() + thisRect.left()) / 2;
        return xMid;
    }

    if (index.model()->rowCount(index) == 0) {
        return rect.left() + indentation() / 2;
    }

    QStyleOptionViewItem opt;
    opt.rect = rect;

    QRect arrow = style()->subElementRect(QStyle::SE_TreeViewDisclosureItem, &opt, this);

    const auto x = arrow.right() - cBranchArrowOffset;
    return x;
}

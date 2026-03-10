#include "om_tree_delegate.h"
#include <QPainter>
#include <QApplication>
#include <QTreeView>

namespace {
constexpr int cItemVerticalPadding = 4;
constexpr int cItemHorizontalPadding = 4;
constexpr int cItemInnerGap = 4;
}

OMTreeDelegate::OMTreeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void OMTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
{
    painter->save();

    const auto& rc = option.rect;

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(rc, option.palette.highlight());
    } else if (option.state & QStyle::State_MouseOver) {
        painter->fillRect(rc, option.palette.midlight());
    }

    QPixmap icon = index.data(Qt::DecorationRole).value<QPixmap>();
    QString text = index.data(Qt::DisplayRole).toString();

    int xPos = rc.left() + cItemHorizontalPadding;

    if (!icon.isNull()) {
        xPos += cItemInnerGap;
        int iconYBegin = rc.y() + (rc.height() - icon.height()) / 2;
        painter->drawPixmap(xPos, iconYBegin, icon);
        xPos += icon.width() + cItemInnerGap;
    }

    const bool isRootItem = !index.parent().isValid();

    if (isRootItem) {
        QFont boldFont = option.font;
        boldFont.setBold(true);
        painter->setFont(boldFont);
    }

    QColor textColor = (option.state & QStyle::State_Selected)
                       ? option.palette.highlightedText().color()
                       : option.palette.text().color();
    painter->setPen(textColor);

    QRect textRect(xPos, rc.top(),
                   rc.right() - xPos, rc.height());
    painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text);

    painter->setPen(QPen(Qt::gray, 1));
    painter->drawLine(rc.left() + cItemHorizontalPadding, rc.bottom(), rc.right(), rc.bottom());

    painter->restore();
}

QSize OMTreeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(size.height() + cItemVerticalPadding * 2);
    return size;
}

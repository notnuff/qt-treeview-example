#pragma once
#include <QStyledItemDelegate>

class OMTreeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit OMTreeDelegate(QObject *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override;
};

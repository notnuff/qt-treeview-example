#pragma once
#include <QTreeView>

class OMTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit OMTreeView(QWidget *parent = nullptr);

protected:
    virtual void drawBranches(QPainter *painter, const QRect &rect,
                              const QModelIndex &index) const override;

private:
    void drawNestedBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;

    void drawRootVLine(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
    void drawSubBranch(QPainter *painter, const QRect &rect, const QModelIndex &index) const;

    int getSubBranchX(const QRect &rect, const QModelIndex &index) const;
};

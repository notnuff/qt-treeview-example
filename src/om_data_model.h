#pragma once
#include <QAbstractItemModel>

class IOMDataProvider;

class OMDataModel : public QAbstractItemModel
{
public:
    OMDataModel(IOMDataProvider *dataProvider, QObject *parent = nullptr);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

private:
    IOMDataProvider *m_dataProvider;
};

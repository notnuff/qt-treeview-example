#include "om_data_model.h"
#include "dataproviders/i_om_data_provider.h"

#include <QPixmap>

namespace {
const QString cCountryTextFormat = "%1 (%2)";
const QString cCountryIconPathFormat = ":/Countries/%1.png";
const QString cOperatorTextFormat = "%1 (%2-%3)";
const QString cOperatorIconPathFormat = ":/Operators/%1_%2.png";
} // namespace

OMDataModel::OMDataModel(IOMDataProvider *dataProvider, QObject *parent)
    : QAbstractItemModel(parent), m_dataProvider(dataProvider)
{
}

QModelIndex OMDataModel::index(const int row, const int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return {};
    }

    if (!parent.isValid()) {
        // country
        return createIndex(row, column, static_cast<quintptr>(-1));
    }

    // operator
    return createIndex(row, column, parent.row());
}

QModelIndex OMDataModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return {};
    }

    if (child.internalId() == static_cast<quintptr>(-1)) {
        // country
        return {};
    }

    // operator
    return createIndex(child.internalId(), 0, static_cast<quintptr>(-1));
}

int OMDataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0;
    }

    if (!parent.isValid()) {
        return m_dataProvider->getCountriesCount();
    }
    if (!parent.parent().isValid()) {
        const auto idx = parent.row();
        return m_dataProvider->getCountryOperatorsCount(idx);
    }
    return 0;
}

int OMDataModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant OMDataModel::data(const QModelIndex &index, int role) const
{
    QVariant result{};

    const bool isCountry = !index.parent().isValid();
    if (isCountry) {
        const auto idx = index.row();
        switch (role) {
        case Qt::ItemDataRole::DisplayRole:
            result = cCountryTextFormat.arg(m_dataProvider->getCountryName(idx))
                             .arg(m_dataProvider->getCountryCode(idx));
            break;
        case Qt::ItemDataRole::DecorationRole: {
            auto iconPath = cCountryIconPathFormat.arg(m_dataProvider->getCountryCode(idx));
            result = QPixmap(iconPath);
            break;
        }
        default:
            break;
        }
    } else {
        const auto countryIdx = index.parent().row();
        const auto operatorIdx = index.row();

        switch (role) {
        case Qt::ItemDataRole::DisplayRole:
            result = cOperatorTextFormat
                             .arg(m_dataProvider->getOperatorName(countryIdx, operatorIdx))
                             .arg(m_dataProvider->getCountryMcc(countryIdx))
                             .arg(m_dataProvider->getOperatorMnc(countryIdx, operatorIdx));
            break;
        case Qt::ItemDataRole::DecorationRole: {
            auto iconPath = cOperatorIconPathFormat.arg(m_dataProvider->getCountryMcc(countryIdx))
                                    .arg(m_dataProvider->getOperatorMnc(countryIdx, operatorIdx));
            result = QPixmap(iconPath);

            break;
        }
        default:
            break;
        }
    }

    return result;
}
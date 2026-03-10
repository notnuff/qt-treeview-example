#pragma once

#include "i_om_data_provider.h"

#include <QSqlDatabase>
#include <QString>

class SqliteOMDataProvider : public IOMDataProvider
{
public:
    explicit SqliteOMDataProvider(const QString &dbPath = "system.db");
    ~SqliteOMDataProvider() override;

    int getCountriesCount() override;
    QString getCountryName(int countryIdx) override;
    QString getCountryCode(int countryIdx) override;
    int getCountryMcc(int countryIdx) override;

    int getCountryOperatorsCount(int countryIdx) override;
    QString getOperatorName(int countryIdx, int operatorIdx) override;
    int getOperatorMnc(int countryIdx, int operatorIdx) override;

private:
    int getMccForCountryIdx(int countryIdx) const;

    QSqlDatabase m_database;
    bool m_isValid;
};

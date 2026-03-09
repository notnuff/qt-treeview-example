#pragma once

#include "../dataproviders/i_om_data_provider.h"
#include <QVector>
#include <QString>

struct OperatorData
{
    QString name;
    int mnc;
};

struct CountryData
{
    QString name;
    QString code;
    int mcc;
    QVector<OperatorData> operators;
};

class MockDataProviderOMFilled : public IOMDataProvider
{
public:
    MockDataProviderOMFilled();
    virtual ~MockDataProviderOMFilled() override = default;

    virtual int getCountriesCount() override;
    virtual QString getCountryName(int countryIdx) override;
    virtual QString getCountryCode(int countryIdx) override;
    virtual int getCountryMcc(int countryIdx) override;

    virtual int getCountryOperatorsCount(int countryIdx) override;
    virtual QString getOperatorName(int countryIdx, int operatorIdx) override;
    virtual int getOperatorMnc(int countryIdx, int operatorIdx) override;

private:
    void initializeData();
    QVector<CountryData> m_countries;
};

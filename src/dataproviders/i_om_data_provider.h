#pragma once

#include <QString>

class IOMDataProvider
{
public:
    virtual ~IOMDataProvider() = default;

    virtual int getCountriesCount() = 0;
    virtual QString getCountryName(int countryIdx) = 0;
    virtual QString getCountryCode(int countryIdx) = 0;
    virtual int getCountryMcc(int countryIdx) = 0;

    virtual int getCountryOperatorsCount(int countryIdx) = 0;
    virtual QString getOperatorName(int countryIdx, int operatorIdx) = 0;
    virtual int getOperatorMnc(int countryIdx, int operatorIdx) = 0;
};

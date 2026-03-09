#include "mock_data_provider_om_filled.h"

MockDataProviderOMFilled::MockDataProviderOMFilled()
{
    initializeData();
}

int MockDataProviderOMFilled::getCountriesCount()
{
    return m_countries.size();
}

QString MockDataProviderOMFilled::getCountryName(int countryIdx)
{
    if (countryIdx >= 0 && countryIdx < m_countries.size()) {
        return m_countries[countryIdx].name;
    }
    return {};
}

QString MockDataProviderOMFilled::getCountryCode(int countryIdx)
{
    if (countryIdx >= 0 && countryIdx < m_countries.size()) {
        return m_countries[countryIdx].code;
    }
    return {};
}

int MockDataProviderOMFilled::getCountryMcc(int countryIdx)
{
    if (countryIdx >= 0 && countryIdx < m_countries.size()) {
        return m_countries[countryIdx].mcc;
    }
    return 0;
}

int MockDataProviderOMFilled::getCountryOperatorsCount(int countryIdx)
{
    if (countryIdx >= 0 && countryIdx < m_countries.size()) {
        return m_countries[countryIdx].operators.size();
    }
    return 0;
}

QString MockDataProviderOMFilled::getOperatorName(int countryIdx, int operatorIdx)
{
    if (countryIdx >= 0 && countryIdx < m_countries.size()) {
        const auto& operators = m_countries[countryIdx].operators;
        if (operatorIdx >= 0 && operatorIdx < operators.size()) {
            return operators[operatorIdx].name;
        }
    }
    return {};
}

int MockDataProviderOMFilled::getOperatorMnc(int countryIdx, int operatorIdx)
{
    if (countryIdx >= 0 && countryIdx < m_countries.size()) {
        const auto& operators = m_countries[countryIdx].operators;
        if (operatorIdx >= 0 && operatorIdx < operators.size()) {
            return operators[operatorIdx].mnc;
        }
    }
    return 0;
}

void MockDataProviderOMFilled::initializeData()
{
    m_countries.append({
        "Ukraine", "UA", 255,
        {
            {"UMC", 1},
            {"WellCOM", 2},
            {"KYIVSTAR", 3}
        }
    });

    m_countries.append({
        "United States", "US", 310,
        {
            {"Verizon", 4},
            {"AT&T", 410},
            {"T-Mobile USA", 260}
        }
    });

    m_countries.append({
        "India", "IN", 404,
        {
            {"Vodafone India", 1},
            {"Airtel", 10},
            {"Reliance Jio", 27}
        }
    });
}
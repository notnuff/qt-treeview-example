#pragma once

#ifdef USE_MOCK_DATA_PROVIDER
#include "tests/mock_data_provider_om_filled.h"
#endif

inline std::unique_ptr<IOMDataProvider> getOMDataProvider()
{
    #ifdef USE_MOCK_DATA_PROVIDER
    return std::make_unique<MockDataProviderOMFilled>();
    #else
    return std::make_unique<IOMDataProvider>();
    #endif
}
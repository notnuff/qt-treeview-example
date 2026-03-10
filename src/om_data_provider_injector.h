#pragma once

#include <memory>

#ifdef USE_MOCK_DATA_PROVIDER
#include "tests/mock_data_provider_om_filled.h"
#else
#include "dataproviders/sqlite_om_data_provider.h"
#endif

inline std::unique_ptr<IOMDataProvider> getOMDataProvider()
{
#ifdef USE_MOCK_DATA_PROVIDER
    return std::make_unique<MockDataProviderOMFilled>();
#else
    return std::make_unique<SqliteOMDataProvider>("system.db");
#endif
}
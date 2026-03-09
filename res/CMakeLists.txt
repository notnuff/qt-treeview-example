file(GLOB_RECURSE COUNTRIES_FILES "Icons/OM Countries/Countries/*")
file(GLOB_RECURSE OPERATORS_FILES "Icons/OM Operators/Operators/*")

qt_add_library(app_resources STATIC)

qt_add_resources(app_resources "countries"
    PREFIX "/Countries"
    BASE "Icons/OM Countries/Countries"
    FILES ${COUNTRIES_FILES}
)

qt_add_resources(app_resources "operators"
    PREFIX "/Operators"
    BASE "Icons/OM Operators/Operators"
    FILES ${OPERATORS_FILES}
)


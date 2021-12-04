HEADERS += \
    $$PWD/Provider.h \
    $$PWD/ProviderManager.h \
    $$PWD/SearchContext.h \

SOURCES += \
    $$PWD/Provider.cpp \
    $$PWD/ProviderManager.cpp \
    $$PWD/SearchContext.cpp \

include(pegasus_favorites/pegasus_favorites.pri)
include(pegasus_whitelists/pegasus_whitelists.pri)
include(pegasus_metadata/pegasus_metadata.pri)
include(pegasus_playtime/pegasus_playtime.pri)

unix:!macx: pclinux = yes

ENABLED_COMPATS =

defined(USES_JSON_CACHE, var) {
    HEADERS += $$PWD/JsonCacheUtils.h
    SOURCES += $$PWD/JsonCacheUtils.cpp
}


# Print configuration
ENABLED_COMPATS = $$sorted(ENABLED_COMPATS)
message("Enabled third-party data sources:")
for(name, ENABLED_COMPATS): message("  - $$name")
isEmpty(ENABLED_COMPATS): message("  - (none)")

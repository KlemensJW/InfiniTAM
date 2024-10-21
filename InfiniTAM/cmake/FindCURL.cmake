# Try to locate CURL
find_path(CURL_INCLUDE_DIR curl/curl.h
        PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include
)

find_library(CURL_LIBRARY NAMES curl
        PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        /sw/lib
)

# Handle the QUIETLY and REQUIRED arguments and set CURL_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CURL DEFAULT_MSG CURL_LIBRARY CURL_INCLUDE_DIR)

if(CURL_FOUND)
    set(CURL_LIBRARIES ${CURL_LIBRARY})
    set(CURL_INCLUDE_DIRS ${CURL_INCLUDE_DIR})
else()
    set(CURL_LIBRARIES)
    set(CURL_INCLUDE_DIRS)
endif()

mark_as_advanced(CURL_INCLUDE_DIR CURL_LIBRARY)
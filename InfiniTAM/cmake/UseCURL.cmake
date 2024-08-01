######################
# UseCURL.cmake #
######################

OPTION(WITH_CURL "Build with CURL support?" ON)

IF(WITH_CURL)
    FIND_PACKAGE(CURL REQUIRED)
    INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
    ADD_DEFINITIONS(-DCOMPILE_WITH_CURL)
ENDIF()

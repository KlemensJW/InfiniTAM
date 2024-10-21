#######################
# LinkCURL.cmake #
#######################

IF(WITH_CURL)
    TARGET_LINK_LIBRARIES(${targetname} curl)
ENDIF()

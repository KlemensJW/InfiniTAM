#######################
# LinkLibRoyale.cmake #
#######################

IF(WITH_MAVSDK)
  TARGET_LINK_LIBRARIES(${targetname} mavsdk)
ENDIF()

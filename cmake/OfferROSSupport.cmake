#########################
# OfferROSSupport.cmake #
#########################

OPTION(WITH_ROS "Build with ROS 2 support?" OFF)

IF(WITH_ROS)
  FIND_PACKAGE(ament_cmake REQUIRED)
  ament_export_include_directories(${CMAKE_INSTALL_PREFIX}/include)
  ament_export_libraries(FernRelocLib InputSource ITMLib MiniSlamGraphLib ORUtils)

  ament_package()
ENDIF()

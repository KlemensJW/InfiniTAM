cmake_minimum_required(VERSION 3.8)
project(infinitam_ros2)

# ROS2 Integration
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Use the actual InfiniTAM build system
add_subdirectory(InfiniTAM)

# Include InfiniTAM Libraries
include_directories(
    ${CMAKE_SOURCE_DIR}/InfiniTAM/ITMLib
    ${CMAKE_SOURCE_DIR}/InfiniTAM/ORUtils
    ${CMAKE_SOURCE_DIR}/InfiniTAM/InputSource
)


add_executable(infinitam_ros2_node InfiniTAM/Apps/Inifinitam_ROS2/InfiniTAM_Node.cpp)

target_link_libraries(infinitam_ros2_node 
        ITMLib
        ORUtils                
)

ament_target_dependencies(infinitam_ros2_node rclcpp)

install(TARGETS 
        infinitam_ros2_node 
        DESTINATION lib/${PROJECT_NAME})
ament_package()
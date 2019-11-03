cmake_minimum_required(VERSION 3.5)
project(rosbridge_mqtt)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)

include_directories(
  include
)

add_library(rosbridge_mqtt_component SHARED src/rosbridge_mqtt_component.cpp)
target_link_libraries(rosbridge_mqtt_component mosquitto)
ament_target_dependencies(rosbridge_mqtt_component
  rclcpp rclcpp_components)

add_executable(rosbridge_mqtt_node src/rosbridge_mqtt_node.cpp)
target_link_libraries(rosbridge_mqtt_node rosbridge_mqtt_component)
ament_target_dependencies(rosbridge_mqtt_node
  rclcpp rclcpp_components)

rclcpp_components_register_nodes(rosbridge_mqtt_component
  "rosbridge_mqtt::RosbridgeMqttComponent")

install(TARGETS
  rosbridge_mqtt_node
  DESTINATION lib/rosbridge_mqtt
)

install(TARGETS
  rosbridge_mqtt_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

ament_export_libraries(rosbridge_mqtt_component)


#find_package(mosquitto-clients REQUIRED)
#find_package(mosquitto REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

cmake_minimum_required(VERSION 3.8)
project(lab2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_srvs REQUIRED)



rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/RobotStatus.msg"
  DEPENDENCIES geometry_msgs
)


#### Added
add_executable(statusPublisher src/status_publisher_main.cpp src/status_publisher.cpp )
add_executable(PatrolController src/patrol_controller_main.cpp src/patrol_controller.cpp )

rosidl_target_interfaces(statusPublisher
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

rosidl_target_interfaces(PatrolController
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_include_directories(statusPublisher PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/lab2>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(PatrolController PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/lab2>
  $<INSTALL_INTERFACE:include>
)


ament_target_dependencies(
  statusPublisher
  "rclpy"
  "rclcpp"
  "std_msgs"
  "geometry_msgs"
  "turtlesim"
)

ament_target_dependencies(
  PatrolController
  "rclpy"
  "rclcpp"
  "std_msgs"
  "geometry_msgs"
  "turtlesim"
  "std_srvs"
)

install(TARGETS statusPublisher PatrolController
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  params
  DESTINATION share/${PROJECT_NAME}
)

##########################

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_default_runtime)

ament_package()

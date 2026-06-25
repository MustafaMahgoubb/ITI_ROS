cmake_minimum_required(VERSION 3.8)
project(lab1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)


add_executable(temperaturePub src/Temperature/temperaturePub.cpp src/Temperature/tempClass.cpp )

add_executable(velocityLimiter src/Velocity_Limiter/velocityLimiterNode.cpp src/Velocity_Limiter/velocityLimiterNode.cpp )


target_include_directories(temperaturePub PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/lab1/Temperature ${CMAKE_CURRENT_SOURCE_DIR}/include/lab1/Velocity_Limiter>
  $<INSTALL_INTERFACE:include>)


target_compile_features(temperaturePub PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

ament_target_dependencies(
  temperaturePub
  "rclpy"
  "rclcpp"
  "sensor_msgs"
)

install(TARGETS temperaturePub
  DESTINATION lib/${PROJECT_NAME})

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


ament_python_install_package(${PROJECT_NAME})

# Install Python scripts as runnable nodes
install(PROGRAMS
  lab1/NodeA.py
  lab1/NodeB.py
  lab1/OdomPub.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install the launch directory so ros2 launch can find the file
install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch)

ament_package()

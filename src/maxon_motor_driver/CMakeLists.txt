cmake_minimum_required(VERSION 3.0.2)
project(maxon_motor_driver)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  maxon_epos
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES maxon_motor_driver
#  CATKIN_DEPENDS cpp
#  DEPENDS system_lib
)
find_package( maxon_epos )

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include/${PROJECT_NAME}/
  ${catkin_INCLUDE_DIRS}
)

add_executable(maxon_node src/maxon_driver.cpp)
include_directories(maxon_node roscpp)
target_link_libraries( maxon_node
  ${catkin_LIBRARIES}
)

add_executable(sine_wave_generator src/create_sine_wave.cpp)
include_directories(sine_wave_generator roscpp)
target_link_libraries( sine_wave_generator
  ${catkin_LIBRARIES}
)
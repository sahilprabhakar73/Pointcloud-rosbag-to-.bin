cmake_minimum_required(VERSION 3.0.2)
project(pointcloud-rosbag-to-bin)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  pcl_ros
  roscpp
  rospy
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})
add_executable(bag_to_bin src/bag_to_bin.cpp)
target_link_libraries(bag_to_bin ${catkin_LIBRARIES})

# Rosbag to .bin file conversion

- This node converts the rosbag containing LiDAR pointcloud to .bin file (single frame of LiDAR) which is primarily used for most of the object detection model based on KiTTi dataset. 

Clone this into existing ROS workspace and use catkin tools to build the package and then follow the below listed instructions.

## Usage

```
Open the first terminal and run:
	rosrun create_bin_file bag_to_bin [pointcloud_rostopic] [output_directory]

Open the second terminal:
	rosbag play [rosbag_file]
```


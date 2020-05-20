#include <iostream>
#include <chrono>
#include <ostream>
#include <string>

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace{
    using std::cout;
    using std::endl;
    using PointT = pcl::PointXYZI;
    using Cloud = pcl::PointCloud<PointT>;
    std::string output_;
}

void conversion_callback(const sensor_msgs::PointCloud2::ConstPtr &msg_){
    auto start = std::chrono::system_clock::now();
    Cloud::Ptr cloud_ (new Cloud);
    pcl::fromROSMsg(*msg_, *cloud_);

    
    
    std::string file_name = output_ + std::to_string(msg_->header.stamp.toSec()) + ".bin";
    std::ofstream bin_file(file_name, std::ios::out|std::ios::binary|std::ios::app);
    

    if(!bin_file.good()){
        cout << "Error Opening: "<< file_name << endl;
    }

    for (size_t i = 0; i < cloud_->points.size(); ++i)
    {
        bin_file.write((char*)&cloud_->points[i].x,3*sizeof(float)); 
        bin_file.write((char*)&cloud_->points[i].intensity,sizeof(float));
    }
  	
    bin_file.close();

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
    cout << "File Saved: " << file_name << " took " << (duration.count()) / 1000.0 << "s." << endl;
}



int main(int argc, char** argv){
    ros::init(argc, argv, "bag_to_pcd");
    ros::NodeHandle nh;

    if(argc != 3){
        cout << "Usage: rosrun    package_name    node_name   pointcloud_topic_name    output_directory" << endl;
        return -1;
    }
    output_ = argv[2];
    ros::Subscriber sub = nh.subscribe(argv[1], 30, conversion_callback);
    
    while(ros::ok()){
        ros::spinOnce();
    }

    return 0;
}
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <roborex/Info.h>
void callback(const roborex::Info::ConstPtr& msg){
	ROS_INFO("I heard :[ %s ]",msg->first_name.c_str());
	ROS_INFO("I heard :[ %s ]",msg->last_name.c_str());
	ROS_INFO("I heard :[ %d ]",msg->age);
	ROS_INFO("I heard :[ %d ]",msg->score);
}


int main(int argc,char **argv){

	ros::init(argc,argv,"listener");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("chatter",1000,callback);
	ros::spin();

	return 0;
}

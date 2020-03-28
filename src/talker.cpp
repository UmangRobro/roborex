#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <roborex/Info.h>

int main(int argc,char **argv){



	ros::init(argc,argv,"talker");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<roborex::Info>("chatter",1000);
	int count=0;
	ros::Rate loop_rate(10);
	while(ros::ok()){
	
		roborex::Info msg;
		msg.first_name="Umang";
		msg.last_name="Patel";
		msg.age=22;
		msg.score=100;
		ROS_INFO("%s","I sent The Message");
		pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
		++count;
	
	}


	return 0;
}

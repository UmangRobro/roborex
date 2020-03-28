#include "ros/ros.h"
#include "roborex/AddTwoInts.h"


bool add(roborex::AddTwoInts::Request &req,roborex::AddTwoInts::Response &res){
	res.sum=req.a+req.b;
	ROS_INFO("requset: x = %ld ,y =%ld",(long int)req.a,(long int)req.b);
	ROS_INFO("sending respose: %ld",(long int)res.sum);
	return true;
}
int main(int argc,char **argv){
	
	ros::init(argc,argv,"server");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService("Add_Server",add);
	ROS_INFO("Ready to add Two numbers");
	ros::spin();
	return 0;
}


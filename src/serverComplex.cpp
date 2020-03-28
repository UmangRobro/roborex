#include "ros/ros.h"
#include "roborex/ComplexAdd.h"

bool add(roborex::ComplexAdd::Request &req,roborex::ComplexAdd::Response &res){
	res.sum.real_part=req.a.real_part+req.b.real_part;
	res.sum.complex_part=req.a.complex_part+req.b.complex_part;
	ROS_INFO("requset : x= %ld+i%ld ,y =%ld+i%ld",(long int)req.a.real_part,(long int)req.a.complex_part,(long int)req.b.real_part,(long int)req.b.complex_part);
	ROS_INFO("sending respose: %ld+i%d",(long int)res.sum.real_part,(long int)res.sum.complex_part);
	return true;
}
int main(int argc,char **argv){
	
	ros::init(argc,argv,"server");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService("Add_Complex_Server",add);
	ROS_INFO("Ready to add Two numbers");
	ros::spin();
	return 0;
}


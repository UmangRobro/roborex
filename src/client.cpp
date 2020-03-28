#include "ros/ros.h"
#include "roborex/AddTwoInts.h"
#include <cstdlib>


int main(int argc,char **argv){
	ros::init(argc,argv,"Client");
	if(argc != 3){
		ROS_INFO("Need two args");
		return 1;
	}
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<roborex::AddTwoInts>("Add_Server");
	roborex::AddTwoInts srv;
	srv.request.a = atoll(argv[1]);
	srv.request.b = atoll(argv[2]);
	if(client.call(srv)){
		ROS_INFO("sum: %ld",(long int)srv.response.sum);
	}
	else
	{
		ROS_ERROR("Faild to call server");
		return 1;
	}


return 0;
}

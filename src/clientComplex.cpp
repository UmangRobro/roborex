#include "ros/ros.h"
#include "roborex/ComplexAdd.h"
#include <cstdlib>


int main(int argc,char **argv){
	ros::init(argc,argv,"Client");
	if(argc != 5){
		ROS_INFO("Need two args");
		return 1;
	}
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<roborex::ComplexAdd>("Add_Complex_Server");
	roborex::ComplexAdd srv;
	srv.request.a.real_part = atoll(argv[1]);
	srv.request.b.real_part = atoll(argv[3]);

	srv.request.a.complex_part = atoll(argv[2]);
	srv.request.b.complex_part = atoll(argv[4]);

	if(client.call(srv)){
		ROS_INFO("sum: %ld+i%ld",(long int)srv.response.sum.real_part,(long int)srv.response.sum.complex_part);
	}
	else
	{
		ROS_ERROR("Faild to call server");
		return 1;
	}


return 0;
}

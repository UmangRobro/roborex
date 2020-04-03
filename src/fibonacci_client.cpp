#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <roborex/FibonacciAction.h>

int main(int argc,char **argv)
{
	ros::init(argc,argv,"fibonacci_client");
	actionlib::SimpleActionClient<roborex::FibonacciAction> ac("FServer",true);
	ROS_INFO("waiting to start FServer.......");
	ac.waitForServer();
	ROS_INFO("Server Started, Sending goal .....");
	roborex::FibonacciGoal goal;
		ROS_INFO("sending:%d... ",40);
		goal.order=40;
		ac.sendGoal(goal);
		bool finish_before_timeout = ac.waitForResult(ros::Duration(30.0));
		if(finish_before_timeout){
			actionlib::SimpleClientGoalState state = ac.getState();
			ROS_INFO("Action Finish: %s",state.toString().c_str());

		}
		else{
			ROS_INFO("Action did not finished before timeout");
		}


	
	return 0;
}

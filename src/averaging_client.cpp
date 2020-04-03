#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <roborex/AveragingAction.h>
#include <boost/thread.hpp>
void spinThread()
{
	ros::spin();
}
int main(int argc,char **argv)
{
	ros::init(argc,argv,"fibonacci_client");
	actionlib::SimpleActionClient<roborex::AveragingAction> ac("averaging",true);
	boost::thread spin_thread(spinThread);
	ROS_INFO("waiting to start FServer.......");
	ac.waitForServer();
	ROS_INFO("Server Started, Sending goal .....");
	roborex::AveragingGoal goal;
		ROS_INFO("sending:%d... ",40);
		goal.samples=100;
		ac.sendGoal(goal);
		bool finish_before_timeout = ac.waitForResult(ros::Duration(30.0));
		if(finish_before_timeout){
			actionlib::SimpleClientGoalState state = ac.getState();
			ROS_INFO("Action Finish: %s",state.toString().c_str());

		}
		else{
			ROS_INFO("Action did not finished before timeout");
		}


		ros::shutdown();
		
	return 0;
}

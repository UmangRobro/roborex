#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <roborex/FibonacciAction.h>

using namespace roborex;
typedef actionlib::SimpleActionClient<FibonacciAction> Client;

class CallBackClient{
	protected:
		Client ac;
	public:
		CallBackClient():
			ac("FServer",true)
		{
			ROS_INFO("Waiting for action server to start");
			ac.waitForServer();
			ROS_INFO("started sending data");
			
		}
		void doStuff(int order){
		
			FibonacciGoal goal;
			goal.order=order;
			ac.sendGoal(goal,boost::bind(&CallBackClient::doneCB,this,_1,_2));
		}
		void doneCB(const actionlib::SimpleClientGoalState& state,const FibonacciResultConstPtr& result){
		
			ROS_INFO("[%s]: State of Server",state.toString().c_str());
			ROS_INFO("[%s]: Result",result->sequence.back());
			ros::shutdown();
			
		}

};
int main(int argc,char **argv){
	ros::init(argc,argv,"test_client_fibonacci_callback");
	CallBackClient callback;
	callback.doStuff(30);
	ros::spin();

	return 0;
}

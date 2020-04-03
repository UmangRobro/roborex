#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <roborex/FibonacciAction.h>



class FibonacciAction
{
	protected:
		ros::NodeHandle n_;
		actionlib::SimpleActionServer<roborex::FibonacciAction> action_;
		std::string action_name_;
		roborex::FibonacciFeedback feedback_;
		roborex::FibonacciResult result_;
	public:
		FibonacciAction(std::string name):
			action_(n_,name,boost::bind(&FibonacciAction::executeCB,this,_1),false){
			action_name_=name;
			action_.start();
		}
		~FibonacciAction(void){
		}
		void executeCB(const roborex::FibonacciGoalConstPtr &goal){
			ros::Rate r(1);
			bool success = true;
			feedback_.sequence.push_back(0);
			feedback_.sequence.push_back(1);
			ROS_INFO("%s : Executing,Creating Fibonacci sequence of order %i with seed %i,%i",action_name_.c_str(),goal->order,feedback_.sequence[0],feedback_.sequence[1]);
			for (int i=1;i<=goal->order;i++){
				if(action_.isPreemptRequested()||!ros::ok()){
					ROS_INFO("%s: Preempted",action_name_.c_str());
					action_.setPreempted();
					success=false;
					break;
				}
				feedback_.sequence.push_back(feedback_.sequence[i]+feedback_.sequence[i-1]);
				action_.publishFeedback(feedback_);
				r.sleep();
			}
			if(success){
				result_.sequence=feedback_.sequence;
				ROS_INFO("%s:Succeeded",action_name_.c_str());
				action_.setSucceeded(result_);
			}
		
		}


};
int main(int argc,char **argv){



	ros::init(argc,argv,"Fibonacci_Server");
	FibonacciAction fibonacci("FServer");
	ros::spin();
	return 0;
}

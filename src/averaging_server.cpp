#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <std_msgs/Float32.h>
#include <roborex/AveragingAction.h>

class AveragingAction{

	protected:
		ros::NodeHandle n;
		actionlib::SimpleActionServer<roborex::AveragingAction>action_;
		std::string action_name_;
		roborex::AveragingFeedback feedback_;
		roborex::AveragingResult result_;
		int data_count_,goal_;
		float sum_,sum_sq_;
		ros::Subscriber sub_;
	public:
		AveragingAction(std::string name):
			action_(n,name,false),
			action_name_(name){
			
				action_.registerGoalCallback(boost::bind(&AveragingAction::goalCB,this));
				action_.registerPreemptCallback(boost::bind(&AveragingAction::preemptCB,this));
				sub_=n.subscribe("/random_number",1,&AveragingAction::analysisCB,this);	
				action_.start();
			}
		~AveragingAction(void){
		}
		void goalCB(){
			data_count_=0;
			sum_=0;
			sum_sq_=0;
			goal_=action_.acceptNewGoal()->samples;
		}
		void preemptCB(){
			ROS_INFO("%s: Preempted ",action_name_.c_str());
			action_.setPreempted();
		}
		void analysisCB(const std_msgs::Float32::ConstPtr& msg){
			if(!action_.isActive())
				return;
			data_count_++;
			feedback_.sample=data_count_;
			feedback_.data=msg->data;
			sum_+=feedback_.data;
			sum_sq_+=pow(feedback_.data,2);
			feedback_.mean=sum_/data_count_;
			feedback_.std_dev=sqrt(fabs((sum_sq_/data_count_)-pow(feedback_.mean,2)));
			action_.publishFeedback(feedback_);
			if(data_count_>goal_){
				result_.mean=feedback_.mean;
				result_.std_dev=feedback_.std_dev;
				if(result_.mean<5.0)
				{
					ROS_INFO("%s:Aborted",action_name_.c_str());
					action_.setAborted(result_);
				}
				else{
					ROS_INFO("%s:succeeded",action_name_.c_str());
					action_.setSucceeded(result_);
				}


			}
		}

};
int main(int argc,char **argv){
	ros::init(argc,argv,"averaging");
	AveragingAction averaging(ros::this_node::getName());
	ros::spin();
	return 0;
}

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
 
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  ros::Publisher object_state_pub = n.advertise<std_msgs::UInt8>("/object_state", 1);
  
  
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  std_msgs::UInt8 status;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  
  //setting goal to pick-up location
  ROS_INFO("going to pick-up location");
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -1.5;
  goal.target_pose.pose.position.y = 3.5;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    
    //publishing status to "/object_state" topic
    status.data = 1;
    object_state_pub.publish(status);
    
    
    ROS_INFO("Hooray, the base moved to pick-up location");
    ROS_INFO("waiting for picking up object");
    ros::Duration(5.0).sleep();
    ROS_INFO("object picked");   
  }
  else
    ROS_INFO("The base failed to move to pick-up location");
  
  
  
  //setting goal to drop-off location
  ROS_INFO("going to drop-off location");
  
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 3.5;
  goal.target_pose.pose.position.y = -4.0;
  goal.target_pose.pose.orientation.w = 1.5;

   // Send the goal position and orientation for the robot to reach
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Hooray, the base moved to drop-off location");
    
    //publishing status to "/object_state" topic
    status.data = 2;
    object_state_pub.publish(status);
  }
  else
    ROS_INFO("The base failed to move to drop-off location");
  
  
  //publishing status to "/obeject_state" topic
  ros::Duration(3.0).sleep();
  status.data = 3;
  object_state_pub.publish(status);
  
  
  ros::spin();

  return 0;
}
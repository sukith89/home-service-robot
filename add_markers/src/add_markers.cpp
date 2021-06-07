#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/UInt8.h>

uint8_t state = 0;

void stateCallback(const std_msgs::UInt8::ConstPtr& msg)
  {
     state = msg->data;
     return;
  }


// %Tag(INIT)%
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber object_state_sub = n.subscribe("/object_state", 1, stateCallback);


  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;


  
// %Tag(MARKER_INIT)%
  while (ros::ok())
  {
    ros::spinOnce();
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 255.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    
    

    marker.lifetime = ros::Duration();
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    
    
    
    
    
  
 
   switch (state) {
     case 0 : {
        //setting position of the marker at the pick-up location
        marker.pose.position.x = -1.5;
        marker.pose.position.y = 3.0;
        marker.pose.orientation.w = 1.0;

        ROS_INFO("Publishing the marker at the pick-up location");
        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
        break;
      }
        
     case 1 : {
        ROS_INFO("Marker hidden state");
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        break;
      }

     case 2 : {
        //setting position of the marker at the pick-up location
        ROS_INFO("Publishing the marker at the drop-off location");
        marker.pose.position.x = 3.5;
        marker.pose.position.y = -4.0;
        marker.pose.orientation.w = 1.0;
        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
        break;
      }
     case 3 : {
       ROS_INFO("DONE");
       ros::spin();
      }
   }  
       
     
    r.sleep();
    
  }
 
  
}

#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "controller";

// For Block controller/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_controller_std_msgs_Float64> Sub_controller_52;

// For Block controller/Subscribe1
SimulinkSubscriber<std_msgs::Float64, SL_Bus_controller_std_msgs_Float64> Sub_controller_53;

// For Block controller/Subscribe4
SimulinkSubscriber<std_msgs::Float64, SL_Bus_controller_std_msgs_Float64> Sub_controller_54;

// For Block controller/Publish1
SimulinkPublisher<std_msgs::Float64, SL_Bus_controller_std_msgs_Float64> Pub_controller_49;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}


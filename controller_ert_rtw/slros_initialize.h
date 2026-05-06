#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "controller_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block controller/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_controller_std_msgs_Float64> Sub_controller_52;

// For Block controller/Subscribe1
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_controller_std_msgs_Float64> Sub_controller_53;

// For Block controller/Subscribe4
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_controller_std_msgs_Float64> Sub_controller_54;

// For Block controller/Publish1
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_controller_std_msgs_Float64> Pub_controller_49;

void slros_node_init(int argc, char** argv);

#endif

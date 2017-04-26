/** \file summit_xl_controller.h
 * \author Robotnik Automation S.L.L.
 * \version 2.0
 * \date    2012
 *
 * \brief class for the SummitXL CAN multi-axis controller
 * 
 * (C) Robotnik Automation, SLL
*/

#include <string.h>
#include <vector>
#include <stdint.h>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>				// odom
#include <sensor_msgs/Joy.h>			 	// joystick
#include <geometry_msgs/Twist.h>			// cmd_vel
#include <math.h>
#include "summit_xl_controller/Motors.h"

//#include "ros/time.h"
#include "self_test/self_test.h"
#include "diagnostic_msgs/DiagnosticStatus.h"
#include "diagnostic_updater/diagnostic_updater.h"
#include "diagnostic_updater/update_functions.h"
#include "diagnostic_updater/DiagnosticStatusWrapper.h"


namespace summit_xl_ctrl
{

// Source of the robot's angle
enum AngleMode{
	GYRO,
	ODOMETRY
};

//! Class to operate with the ms20 magnets sensor
class summit_xl_controller
{

public:

  	self_test::TestRunner self_test_;
  	diagnostic_updater::Updater diagnostic_;
	ros::NodeHandle node_handle_;
	ros::NodeHandle private_node_handle_;
	int error_count_;
	int slow_count_;
	double desired_freq_;
	diagnostic_updater::FrequencyStatus freq_diag_;

  	ros::Publisher odom_pub_;
	ros::Publisher battery_pub_;
  	//ros::ServiceServer io_write_digital_pub_;
	ros::Subscriber cmd_vel_sub_;

	// Frame id strings
	std::string base_frame_id;
	std::string odom_frame_id;

	//! Broadcast tf
	tf::TransformBroadcaster tf_broadcaster;
	//! Motors component 
	Motors *driver;
	//! Reference state space speeds 
	double dDesiredLinearSpeed, dDesiredAngularSpeed;
	//! Linear accelerations and decelerations
	double dLinearAcceleration, dLinearDeceleration;
	//! Angular accelerations and decelerations
	double dAngularAcceleration, dAngularDeceleration;
	//! Linear Speed increments, decrements
	double dIncLinearSpeed, dDecLinearSpeed;
	//! Angular Speed increments, decrements
	double dIncAngularSpeed, dDecAngularSpeed;
	//! Motor Alarms 
	vector<bool> vAlarms;
	//! Odometry estimation
	Odometry odom;
	//! Distance between wheels
	double dDWheels;
	//! Enable / disable motors
	bool bMotorsEnabled;
	//! Node running
	bool running;	

	// Error counters and flags
	std::string was_slow_;
	std::string error_status_;

private:
	//! Mutex for controlling the changes and access to odomety values
	pthread_mutex_t mutex_odometry;

public:
	//! Public constructor
	summit_xl_controller(ros::NodeHandle h);
	//! Public destructor
	~summit_xl_controller();
	//! Callback - command references
	void cmdVelCallback(const geometry_msgs::Twist::ConstPtr& cmd_vel);
 	//! Start Controller
	int start();
 	//! Stop Controller
	int stop();
	//! Test to connect to Motors
	void ConnectTest(diagnostic_updater::DiagnosticStatusWrapper& status);
	//! Standard device status
	void deviceStatus(diagnostic_updater::DiagnosticStatusWrapper &status);
	//! Enable / Disable motor drives
	void ToggleMotorPower(unsigned char val);
	//! Set odometry 
	void ModifyOdometry(double x, double y, double yaw);
	//! Reset odometry
	void ResetOdometry();
	//! Get battery voltage
	float GetVoltage();
	//! Read data from Motors and publish
	int read_and_publish();
	//! Main loop
	bool spin();

private:
	//! Do the calcs to update the odometry
	void UpdateOdometry();
};

}


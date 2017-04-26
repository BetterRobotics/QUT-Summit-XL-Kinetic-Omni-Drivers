/** \file summit_xl_controller.cc
 * \author Robotnik Automation S.L.L.
 * \version 2.0
 * \date    2012
 *
 * \brief summit_xl_controller class driver
 * Component to manage the Summit XL servo controller set
 * (C) 2012 Robotnik Automation, SLL
*/
#include <string.h>
#include <vector>
#include <stdint.h>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>		    // odom
#include <sensor_msgs/Joy.h>		    // joystick
#include <geometry_msgs/Twist.h>	    // cmd_vel
#include <std_msgs/Float32.h>               // battery and gyro
#include <sensor_msgs/Imu.h>  //Imu
#include <std_msgs/Bool.h>					// 
#include <math.h>
#include <cstdlib>
#include "summit_xl_controller/Motors.h"
#include <robotnik_msgs/set_odometry.h>          // service
#include <robotnik_msgs/set_height.h>
#include <robotnik_msgs/MotorStatus.h>
#include <robotnik_msgs/MotorsStatus.h>
#include <sensor_msgs/JointState.h>

//#include "ros/time.h"
#include "self_test/self_test.h"
#include "diagnostic_msgs/DiagnosticStatus.h"
#include "diagnostic_updater/diagnostic_updater.h"
#include "diagnostic_updater/update_functions.h"
#include "diagnostic_updater/DiagnosticStatusWrapper.h"
#include "diagnostic_updater/publisher.h"
#include <robotnik_msgs/set_mode.h>
#include <robotnik_msgs/get_mode.h>
#include <robotnik_msgs/home.h>
#include <summit_xl_controller/LimitSwitches.h>
#include <robotnik_msgs/set_digital_output.h>

#define   SUMMIT_XL_MIN_COMMAND_REC_FREQ	1.0
#define	  SUMMIT_XL_MAX_COMMAND_REC_FREQ	20.0
#define	  SUMMIT_XL_COMMAND_WATCHDOG	0.1

#define   SKID_STEERING                	1
#define   MECANUM_STEERING             	2
#define   SUMMIT_XL_JOINTS	        9

using namespace std;

class summit_xl_node
{
public:
  self_test::TestRunner self_test_;
  ros::NodeHandle node_handle_;
  ros::NodeHandle private_node_handle_;
  int error_count_;
  int slow_count_;
  double desired_freq_;
  diagnostic_updater::Updater diagnostic_;	  	   // General status diagnostic updater
  diagnostic_updater::FrequencyStatus freq_diag_;          // Component frequency diagnostics
  diagnostic_updater::HeaderlessTopicDiagnostic *subs_command_freq, *subs_yaw_sensor_freq; // Topic reception frequency diagnostics
  ros::Time last_command_time, last_yaw_sensor_time; 	           // Last moment when the component received a command
  diagnostic_updater::FunctionDiagnosticTask command_freq_;
  diagnostic_updater::FunctionDiagnosticTask yaw_sensor_freq_;

  ros::Publisher odom_pub_;
  ros::Publisher battery_pub_;
  ros::Publisher homed_pub_; 
  ros::Publisher scissor_pub_;
  ros::Publisher digital_input_pub_;
  ros::Publisher estop_pub_;
  ros::Publisher in_motion_pub_;  
  ros::Subscriber cmd_vel_sub_;
  ros::Subscriber gyro_sub_;
  ros::Subscriber imu_sub_;

  ros::Publisher joint_state_pub_;
    
  ros::Publisher MotorsStatus_Pub_;
  ros::Publisher MotorStatusX_Pub_;
    
  // Services
  ros::ServiceServer set_odom_service;
  ros::ServiceServer srv_SetMode_;
  ros::ServiceServer srv_GetMode_;
  ros::ServiceServer srv_Home_;
  ros::ServiceServer srv_SetHeight_;
  ros::ServiceServer srv_SetDigitalOutput_;

  // State - active kinematic mode
  int active_kinematic_mode_;
	
  // Joint states
  sensor_msgs::JointState robot_joints_;

  // Frame id strings
  std::string base_frame_id;
  std::string odom_frame_id;

  //! Broadcast tf
  tf::TransformBroadcaster tf_broadcaster;

  //! Motors component 
  Motors *driver;
  
  //! Motor Alarms 
  vector<bool> vAlarms;
  //! Odometry estimation
  Odometry odom;
  //! Init yaw from the yaw sensor (gyro or imu)
  double init_yaw_;
  //! Last yaw read from the yaw sensor (gyro or imu)
  double last_yaw_;
  //! Yaw increment in one period
  double delta_yaw_; 
  //! Variable that integrates yaw only when the robot is in motion
  double motion_yaw_; 
  //! Flag to store first yaw value
  double bFirstYawRead_;
  //! Distance between wheels
  double dDWheels;
  //! Enable / disable motors
  bool bMotorsEnabled;
  //! Node running
  bool running;
  //! XL platform in XWAM configuration
  std::string x_wam_;
  //! CAN device
  std::string can_dev_;
  //! kinematic model
  std::string kinematic_model_;
  //! gearbox reduction
  double gearbox_;
  //! diameter of the wheels
  double diameter_wheel_;
	
  //! Motors Encoders: if Motors with encoders speed must be multiplied by motors_encoders_factor
  //! Be carefull: not use this option if your motors don't have encoders
  std::string motors_encoder_;
  double motors_encoder_factor_;
  
  // Error counters and flags
  std::string was_slow_;
  std::string error_status_;

  //! Mutex for controlling the changes and access to odomety values
  pthread_mutex_t mutex_odometry;

  //! Allow to choose if using the gyroscope of an IMU as yaw sensor
  std::string yaw_source_;

  //! Name of the topic which is publishing sensor_msgs/Imu messages
  //! Allow to choose among different attitude estimators
  std::string imu_topic_;
  
  //! Boolean string param publish odom tf
  std::string publish_odom_tf_;

  //! Boolean string param defines how to use gyro in odometry
  std::string motion_odometry_;
    
  int iPublishstatus;
  
  //! Wheel linear acceleration in m/s2
  double acceleration_; 

  
/*!	\fn summit_controller::summit_xl_controller()
 * 	\brief Public constructor
*/
summit_xl_node(ros::NodeHandle h) : self_test_(), diagnostic_(),
  node_handle_(h), private_node_handle_("~"), 
  error_count_(0),
  slow_count_(0),
  desired_freq_(50),
  freq_diag_(diagnostic_updater::FrequencyStatusParam(&desired_freq_, &desired_freq_, 0.05)),
	command_freq_("Command frequency check", boost::bind(&summit_xl_node::check_command_subscriber, this, _1)),
	yaw_sensor_freq_("Yaw sensor frequency check", boost::bind(&summit_xl_node::check_yaw_sensor_subscriber, this, _1))
  
  {
    running = false;
    ros::NodeHandle summit_xl_node_handle(node_handle_, "summit_xl_controller");
    //private_node_handle_.param("can_device", can_device, string("/dev/pcan32"));
    private_node_handle_.param<std::string>("base_frame_id", base_frame_id, "base_footprint");
    private_node_handle_.param<std::string>("odom_frame_id", odom_frame_id, "odom");
    private_node_handle_.param<std::string>("publish_odom_tf", publish_odom_tf_, "true");
    private_node_handle_.param<std::string>("motion_odometry", motion_odometry_, "true");
    private_node_handle_.param<std::string>("yaw_source", yaw_source_, "gyro");
    private_node_handle_.param<std::string>("imu_topic", imu_topic_, "/imu/data"); //Topic published by the imu_complementary_filter
    ROS_INFO("motion_odometry = %s", motion_odometry_.c_str());
    ROS_INFO("publish_odom_tf = %s", publish_odom_tf_.c_str());
    ROS_INFO("yaw source = %s", yaw_source_.c_str());

    // 1-<param name="xwam" value="true" type="string"/> in the launch file before the node, no ns    
    private_node_handle_.param<std::string>("/xwam", x_wam_, "false");
    // 2-<ns="summit_xl_controller ... in launch file
    // private_node_handle_.param<std::string>("xwam", x_wam_, "false");
    // 3-yaml true/false identified as bool, not string

    private_node_handle_.param<std::string>("port", can_dev_, "/dev/pcan32");
    private_node_handle_.param<std::string>("kinematic_mode", kinematic_model_, "skid");
    private_node_handle_.param<double>("gearbox_reduction", gearbox_, TRAC_GEAR);
    private_node_handle_.param<double>("diameter_wheel", diameter_wheel_, MOTOR_WHEEL_DIAMETER);
    
    // Factor Motors Encoder Modification
    private_node_handle_.param<std::string>("motors_encoder", motors_encoder_, "false");
    private_node_handle_.param<double>("motors_encoder_factor", motors_encoder_factor_, 1.0);   
    private_node_handle_.param<double>("acceleration", acceleration_, LINEAR_ACCELERATION_DEFAULT); 
		
    ROS_INFO("xwam =%s, port = %s, kinematic_model = %s, gearbox = %lf, diameter = %lf", x_wam_.c_str(), can_dev_.c_str(), kinematic_model_.c_str(), gearbox_, diameter_wheel_ );
  
    // Publishing
    odom_pub_ = summit_xl_node_handle.advertise<nav_msgs::Odometry>("/odom", 50);
    battery_pub_ = private_node_handle_.advertise<std_msgs::Float32>("battery", 50);
    if (x_wam_ == "true") {
      homed_pub_ = private_node_handle_.advertise<std_msgs::Bool>("homed", 50);
      scissor_pub_ = private_node_handle_.advertise<std_msgs::Float32>("scissor_position", 50); 
      digital_input_pub_ = private_node_handle_.advertise<summit_xl_controller::LimitSwitches>("limit_switches", 50);
    }
	
    estop_pub_ = private_node_handle_.advertise<std_msgs::Bool>("emergency_stop", 50);
    // Publish joint states for wheel motion visualization
    joint_state_pub_ = summit_xl_node_handle.advertise<sensor_msgs::JointState>("/joint_states", 10);
	
    MotorsStatus_Pub_ = private_node_handle_.advertise<robotnik_msgs::MotorsStatus>("MotorsStatus", 10);
    if (x_wam_=="true") MotorStatusX_Pub_ = private_node_handle_.advertise<robotnik_msgs::MotorStatus>("MotorStatusX", 10);

    in_motion_pub_ = private_node_handle_.advertise<std_msgs::Bool>("in_motion", 50);

    //Advertise services
	if(!kinematic_model_.compare("skid")){
		active_kinematic_mode_ = SKID_STEERING;
	}
	else{
		active_kinematic_mode_ = MECANUM_STEERING; 
	}
    //active_kinematic_mode_ = SKID_STEERING;   // even in omni kinematics, start always in skid steering
			
    srv_SetMode_ = summit_xl_node_handle.advertiseService("set_mode", &summit_xl_node::srvCallback_SetMode, this);
    srv_GetMode_ = summit_xl_node_handle.advertiseService("get_mode", &summit_xl_node::srvCallback_GetMode, this);
    if (x_wam_ == "true") {
      srv_Home_ = summit_xl_node_handle.advertiseService("home", &summit_xl_node::srvCallback_Home, this);
      srv_SetHeight_ = summit_xl_node_handle.advertiseService("set_height", &summit_xl_node::srvCallback_SetHeight, this);
    }
	srv_SetDigitalOutput_ = summit_xl_node_handle.advertiseService("write_digital_output", &summit_xl_node::srvCallback_SetDigitalOutput, this);
    	
    // Subcscribing
    cmd_vel_sub_ = private_node_handle_.subscribe<geometry_msgs::Twist>("command", 1, &summit_xl_node::cmdVelCallback, this );

    if(yaw_source_=="gyro")
      gyro_sub_ = summit_xl_node_handle.subscribe("/gyro", 1, &summit_xl_node::gyroCallback, this);
    else
      imu_sub_ = summit_xl_node_handle.subscribe(imu_topic_, 1, &summit_xl_node::imuCallback, this);
	
    self_test_.add("Connect Test", this, &summit_xl_node::ConnectTest);
    // Component frequency diagnostics
    diagnostic_.setHardwareID("summit_xl_controller-DZ");
    diagnostic_.add("Motor Controller", this, &summit_xl_node::controller_diagnostic);
    diagnostic_.add( freq_diag_ );
    diagnostic_.add( command_freq_ );
    diagnostic_.add( yaw_sensor_freq_ );
    
    // Topics freq control 
    // For /summit_xl_controller/command
    double min_freq = SUMMIT_XL_MIN_COMMAND_REC_FREQ; // If you update these values, the
    double max_freq = SUMMIT_XL_MAX_COMMAND_REC_FREQ; // HeaderlessTopicDiagnostic will use the new values.
    subs_command_freq = new diagnostic_updater::HeaderlessTopicDiagnostic("/summit_xl_controller/command", diagnostic_,
	                    diagnostic_updater::FrequencyStatusParam(&min_freq, &max_freq, 0.1, 10));
    subs_command_freq->addTask(&command_freq_); // Adding an additional task to the control

    
    // For gyro and IMU
    double min_freq_gyro = 50.0; // If you update these values, the
    double max_freq_gyro = 150.0; // HeaderlessTopicDiagnostic will use the new values.
    double min_freq_imu = 50.0;  //TODO: CHECK THESE VALUES
    double max_freq_imu = 300.0;
    if(yaw_source_=="gyro")
       subs_yaw_sensor_freq = new diagnostic_updater::HeaderlessTopicDiagnostic("/gyro", diagnostic_,
							diagnostic_updater::FrequencyStatusParam(&min_freq_gyro, &max_freq_gyro, 0.1, 10));
    else
      subs_yaw_sensor_freq = new diagnostic_updater::HeaderlessTopicDiagnostic(imu_topic_, diagnostic_,
							diagnostic_updater::FrequencyStatusParam(&min_freq_imu, &max_freq_imu, 0.1, 10));
    subs_yaw_sensor_freq->addTask(&yaw_sensor_freq_); // Adding an additional task to the control

    // Advertise service server - set odometry
    // set_odom_service = summit_xl_node_handle.advertiseService("set_odometry", set_odometry);
    // -> moved to main()

    // initialize last_yaw_ and delta_yaw_ variable
    last_yaw_ = 0.0;
    delta_yaw_ = 0.0;
    motion_yaw_ = 0.0;
	
    // first yaw read
    bFirstYawRead_ = false;

    // Initialize joints array 
    char j[3]= "\0";  
    for(int i = 0; i <SUMMIT_XL_JOINTS; i++){
      sprintf(j,"j%d",i+1);
      robot_joints_.name.push_back(j);
      robot_joints_.position.push_back(0.0);
      robot_joints_.velocity.push_back(0.0);
      robot_joints_.effort.push_back(0.0);	
    }

    // Names of the joints
    robot_joints_.name[0] = "joint_front_right_wheel";
    robot_joints_.name[1] = "joint_front_left_wheel";
    robot_joints_.name[2] = "joint_back_left_wheel";
    robot_joints_.name[3] = "joint_back_right_wheel";
    robot_joints_.name[4] = "scissor_prismatic_joint";
    robot_joints_.name[5] = "joint_front_right_steer";
    robot_joints_.name[6] = "joint_front_left_steer";
    robot_joints_.name[7] = "joint_back_left_steer";
    robot_joints_.name[8] = "joint_back_right_steer";
    
    //Initialization for odometry's mutex
    
    iPublishstatus=0;
    pthread_mutex_init(&mutex_odometry, NULL); 
  }

/*!	\fn summit_xl_controller::~summit_xl_controller()
 * 	\brief Public destructor
*/
~summit_xl_node(){

  stop();
  
  driver->ShutDown();
  
  delete driver;
  delete subs_command_freq;
	
  // Destroy odometry mutex
  pthread_mutex_destroy(& mutex_odometry );
}

  /*!    \fn double radnorm( double yaw ) 
    \brief normalize value in radians between -pi and pi
  */
  double radnorm( double yaw )
  {
    if (yaw>3.1415926535) yaw -= 2*3.1415926535;
    if (yaw<-3.1415926535) yaw += 2*3.1415926535;
    return yaw;
  }
  /*!	\fn int summit_xl_controller::start()
   * 	\brief Start Controller
   */
  int start(){

    stop();
    bool bOmni=false;
    if (active_kinematic_mode_ == SKID_STEERING ) {
      bOmni=false;
    } else {
      bOmni=true;
    }
		
    // Create motors	      
    if (x_wam_=="true") {
      ROS_INFO(" XWAM Mode configured ");
      if (motors_encoder_=="true") driver = new Motors(can_dev_, diameter_wheel_, gearbox_, 100.0, true, true, motors_encoder_factor_,bOmni, acceleration_);
      else driver = new Motors(can_dev_, diameter_wheel_, gearbox_, 100.0, true,bOmni,acceleration_);
    } else {
      ROS_INFO(" XWAM Mode NOT configured ");
      if (motors_encoder_=="true") driver = new Motors(can_dev_, diameter_wheel_, gearbox_, 100.0, false, true, motors_encoder_factor_,bOmni, acceleration_);
      else driver = new Motors(can_dev_, diameter_wheel_, gearbox_, 100.0, false,bOmni,acceleration_);
    }
    // Setup motors 	
    if(driver->Setup()!= OK){
      ROS_ERROR("summit_xl_controller::summit_xl_controller: Error in Driver setup.");
    }

    // Start motor controller
    if(driver->Start()!= OK){
      ROS_ERROR("summit_xl_controller::summit_xl_controller: Error in Driver start.");
      return -1;
    }
    
    usleep(100000);
    
    // POSITION_XWAM
    // Home (just in case xwam)
    // if (x_wam_=="true") {
    //  if (driver->Home()!= OK) {
    //	  ROS_ERROR("summit_xl_controller: Error in driver home.");
    //	  }
    //  }

    usleep(10000);
    ROS_INFO("SummitXL controller started");
    freq_diag_.clear();
    running = true;
    return 0;
}

/*!	\fn summit_xl_controller::stop()
 * 	\brief Stop Controller
*/
int stop(){
  
  ROS_INFO("Stopping driver");
  if(running)
    {
      driver->Stop();
      sleep(1);
      running = false;
    }
  return 0;
}

  /*!	\fn summit_xl_controller::ConnectTest()
   * 	\brief Test to connect to Motors
   */
  void ConnectTest(diagnostic_updater::DiagnosticStatusWrapper& status)
  {
  // connection test
    // TBC
    status.summary(0, "Connected successfully.");
  }

  /*
   *\brief Checks the status of the controller. Diagnostics
   *
   */
  void controller_diagnostic(diagnostic_updater::DiagnosticStatusWrapper &stat)
{
  States state = driver->GetState();
  
  if(state == READY_STATE){
    stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "Controller ready");
  }else if(state == INIT_STATE){
    stat.summary(diagnostic_msgs::DiagnosticStatus::WARN, "Controller initialing");
  }else{
    stat.summary(diagnostic_msgs::DiagnosticStatus::ERROR, "Controller on Failure or unknown state");
  }
  
  // add and addf are used to append key-value pairs.
  stat.add("State FLW", driver->GetMotorFlwStateString()); // Internal controller state
  stat.add("State BLW", driver->GetMotorBlwStateString()); // Internal controller state
  stat.add("State FRW", driver->GetMotorFrwStateString()); // Internal controller state
  stat.add("State BRW", driver->GetMotorBrwStateString()); // Internal controller state
  if (x_wam_=="true") stat.add("State Scissor", driver->GetMotorScissorStateString());
  
  // add and addf are used to append key-value pairs.
  stat.add("Status FLW", driver->GetMotorFlwStatusString()); // Internal controller status
  stat.add("Status BLW", driver->GetMotorBlwStatusString()); // Internal controller status
  stat.add("Status FRW", driver->GetMotorFrwStatusString()); // Internal controller status
  stat.add("Status BRW", driver->GetMotorBrwStatusString()); // Internal controller status
  if (x_wam_=="true") stat.add("Status Scissor", driver->GetMotorScissorStatusString());
  
  // add status word string
  stat.add("Status WORD FLW", driver->GetMotorFlwStatusWordString()); 
  stat.add("Status WORD BLW", driver->GetMotorBlwStatusWordString());
  stat.add("Status WORD FRW", driver->GetMotorFrwStatusWordString());
  stat.add("Status WORD BRW", driver->GetMotorBrwStatusWordString());
  if (x_wam_=="true") stat.add("Status WORD Scissor", driver->GetMotorScissorStatusWordString());
	
  // TODO 
  // communication status
  // other errors 
}

/*
 *\brief Publish Motors Status Topics
 *
 */
  void controller_publishing()
  {
  if (x_wam_=="true") {
    robotnik_msgs::MotorStatus MotorX_msg;	
    MotorX_msg.state=driver->GetMotorScissorStateString();	
    MotorX_msg.status=driver->GetMotorScissorStatusString();
    MotorX_msg.statusword=driver->GetMotorScissorStatusWordString();
    MotorX_msg.driveflags=driver->GetMotorScissorStatusFlagsString();
    MotorStatusX_Pub_.publish(MotorX_msg);
  }
	
  robotnik_msgs::MotorsStatus Motors_msg;
  Motors_msg.flwStatus.state = driver->GetMotorFlwStateString();
  Motors_msg.blwStatus.state = driver->GetMotorBlwStateString();
  Motors_msg.frwStatus.state = driver->GetMotorFrwStateString();
  Motors_msg.brwStatus.state = driver->GetMotorBrwStateString();
  
  Motors_msg.flwStatus.status = driver->GetMotorFlwStatusString();
  Motors_msg.blwStatus.status = driver->GetMotorBlwStatusString();
  Motors_msg.frwStatus.status = driver->GetMotorFrwStatusString();
  Motors_msg.brwStatus.status = driver->GetMotorBrwStatusString();
	
  Motors_msg.flwStatus.statusword = driver->GetMotorFlwStatusWordString();
  Motors_msg.blwStatus.statusword = driver->GetMotorBlwStatusWordString();
  Motors_msg.frwStatus.statusword = driver->GetMotorFrwStatusWordString();
  Motors_msg.brwStatus.statusword = driver->GetMotorBrwStatusWordString();
  
  Motors_msg.flwStatus.driveflags = driver->GetMotorFlwStatusFlagsString();
  Motors_msg.blwStatus.driveflags = driver->GetMotorBlwStatusFlagsString();
  Motors_msg.frwStatus.driveflags = driver->GetMotorFrwStatusFlagsString();
  Motors_msg.brwStatus.driveflags = driver->GetMotorBrwStatusFlagsString();
  
  MotorsStatus_Pub_.publish(Motors_msg);
 }

  /*
   *	\brief Checks that the robot is receiving at a correct frequency the command messages. Diagnostics
   *
 */
void check_command_subscriber(diagnostic_updater::DiagnosticStatusWrapper &stat)
{
  ros::Time current_time = ros::Time::now();
  
  double diff = (current_time - last_command_time).toSec();
  
  if(diff > SUMMIT_XL_COMMAND_WATCHDOG){
    stat.summary(diagnostic_msgs::DiagnosticStatus::WARN, "Topic is not receiving commands");
    //ROS_INFO("check_command_subscriber: %lf seconds without commands", diff);
    if (driver) driver->SetDesiredSpeed(0.0, 0.0, 0.0, 0.0);
  }else{
    stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "Topic receiving commands");
  }
}
  
  /*
   *	\brief Checks that the robot is receiving at a correct the yaw values from gyro/imu
   *
   */
  void check_yaw_sensor_subscriber(diagnostic_updater::DiagnosticStatusWrapper &stat)
  {
    ros::Time current_time = ros::Time::now();
    
    double diff = (current_time - last_yaw_sensor_time).toSec();
    //ROS_INFO("check_command_subscriber: %lf seconds without commands", diff);
    if(diff > 2.0){
      stat.summary(diagnostic_msgs::DiagnosticStatus::WARN, "Yaw sensor value is not being received");
      
      //ROS_INFO("check_command_subscriber: %lf seconds without commands", diff);
      if (driver) driver->SetYawSensor(false);
    }else{
      stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "Topic receiving commands");
    }
  }

  /*!     \fn  Service set odometry
   *      Sets the odometry of the robot
   */
  bool set_odometry(robotnik_msgs::set_odometry::Request &req, robotnik_msgs::set_odometry::Response &res )
  {
    ROS_INFO("summit_xl_controller::set_odometry: request -> x = %f, y = %f, a = %f", req.x, req.y, req.orientation);
    
    ModifyOdometry(req.x, req.y, req.orientation);
    res.ret = true;
    
    return true;
  }

////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS

/*!     \fn void summit_xl_controller::ToggleMotorPower(unsigned char val)
 *      \brief Switches on/off the motor
*/
void ToggleMotorPower(unsigned char val)
{
        switch(val) {
        case '1':       //Enable Motors
            driver->Start();
            ROS_INFO("summit_xl_controller::ToggleMotorPower: Motors enabled");
        break;
        case '0':       //Disable Motors
            driver->Stop();
            ROS_INFO("summit_xl_controller::ToggleMotorPower: Motors disabled");
        break;
        }
}

/*!	\fn int summit_xl_controller::ModifyOdometry(double x, double y, double yaw)
	* Changes odometry's current values
*/
void ModifyOdometry(double x, double y, double yaw) {
  pthread_mutex_lock(&mutex_odometry);
  // store new orientation
  init_yaw_ = last_yaw_;
  motion_yaw_ = yaw;
  Odometry odom;
  odom.px = x;
  odom.py = y;
  odom.pa = yaw; 
  odom.v = 0.0;
  odom.w = 0.0;
  driver->ModifyOdometry( odom );
  pthread_mutex_unlock(&mutex_odometry);
}

  /*!	\fn void summit_xl_controller::ResetOdometry()
   * Programs Reset Odometry Message
*/
  void ResetOdometry()
  {
    pthread_mutex_lock(&mutex_odometry);
    // store current orientation as 0 i.e. reset gyro yaw
    init_yaw_ = last_yaw_;
    motion_yaw_ = 0.0;
    driver->ResetOdometry();
    pthread_mutex_unlock(&mutex_odometry);
  }

  // CALLBACKS
  // Service SetMode
  bool srvCallback_SetMode(robotnik_msgs::set_mode::Request& request, robotnik_msgs::set_mode::Response& response)
{
  // Check if the selected mode is available or not
  // 1 - SKID STEERING
  // 2 - OMNIDRIVE 
  // (3 - SWERVE)
	if ( (request.mode == SKID_STEERING) || (request.mode == MECANUM_STEERING and !kinematic_model_.compare("omni")) ) {
        active_kinematic_mode_ = request.mode;
        if (request.mode ==SKID_STEERING) {
			ROS_INFO("summit_xl_controller::srvCallback - set mode SKID_STEERING");
			driver->KinematicMode(false);
		}
        if (request.mode ==MECANUM_STEERING) {
			ROS_INFO("summit_xl_controller::srvCallback - set mode MECANUM_STEERING");
			driver->KinematicMode(true);
		}
        
        return true;
    } else return false;
}

// Service GetMode
bool srvCallback_GetMode(robotnik_msgs::get_mode::Request& request, robotnik_msgs::get_mode::Response& response)
{
  response.mode = active_kinematic_mode_;
  return true;
}

/*!     \fn  Service Home
  *      Performs the z-axis homing, required for later position sets
*/
bool srvCallback_Home(robotnik_msgs::home::Request &req, robotnik_msgs::home::Response &res )
{
	ROS_INFO("summit_xl_controller::srvCallback_Home: Home request");
	
	ReturnValue ret = driver->Home();
	if (ret == ERROR) res.ret = false;
	else res.ret = true;
	
	return true;
}

/*!     \fn  Service set x-height
  *      Sets the desired height of the additional linear axis 
*/
bool srvCallback_SetHeight(robotnik_msgs::set_height::Request &req, robotnik_msgs::set_height::Response &res )
{
	ROS_INFO("summit_xl_controller::set_height: request -> height = %f", req.height);

		driver->SetDesiredPosition( req.height );
	// 
	res.ret = true;
	
	return true;
}

// Callback
/*!     \fn void summit_xl_controller::cmdVelCallback(const geometry_msgs::Twist::ConstPtr& cmd_vel)
        * Callback - velocity references 
*/
void cmdVelCallback(const geometry_msgs::Twist::ConstPtr& cmd_vel)
{
	//static double linear=0.0, angular=0.0;
	//static int count=0;

    // Safety check
	last_command_time = ros::Time::now();
	subs_command_freq->tick();			// For diagnostics
    // Frequency of this callback depends on the frequency of the pad / joystick device
	// so this is not a good location to implement accel / deccel
 	if (driver) {
		if (active_kinematic_mode_ == SKID_STEERING ) 
		    driver->SetDesiredSpeed(cmd_vel->linear.x, 0.0, -cmd_vel->angular.z, cmd_vel->linear.z);
                else if (active_kinematic_mode_ == MECANUM_STEERING ) 
		    driver->SetDesiredSpeed(cmd_vel->linear.x, -cmd_vel->linear.y, -cmd_vel->angular.z, cmd_vel->linear.z);
		}
}

/*
void gyroCallback( const std_msgs::Float32::ConstPtr& yaw_msg )
{
		last_gyro_time = ros::Time::now();	
	   // Store the first value received  
	   if (!bFirstYawRead_) {
			init_yaw_=yaw_msg->data;
			bFirstYawRead_ = true;
}
	   // Compute angle according to the init value
	   last_yaw_ = yaw_msg->data;
	   //double yaw = radnorm( init_yaw_ - last_yaw_ );
	   double yaw = radnorm( last_yaw_ - init_yaw_ );

	   // Use this value (note that if we use gyro, this function is used only as a storage
	   if (driver) driver->SetOdometryAngle( yaw );
	   
	    subs_gyro_freq->tick();
	}
*/

  void gyroCallback( const std_msgs::Float32::ConstPtr& yaw_msg )
  {
    
    if (bFirstYawRead_) delta_yaw_ = yaw_msg->data - last_yaw_;
    
    last_yaw_sensor_time = ros::Time::now();	
    // Store the first value received  
    if (!bFirstYawRead_) {
      init_yaw_=yaw_msg->data;
      bFirstYawRead_ = true;
      motion_yaw_ = init_yaw_; // 
    }
    
    // Compute angle according to the init value
    last_yaw_ = yaw_msg->data;
    
    double yaw;
    if (motion_odometry_=="true") {
      // Integrate yaw only if robot is in motion (avoids integrating drift when robot is stopped for long periods)
      if (driver->InMotion()) motion_yaw_ += delta_yaw_;
      yaw = radnorm( motion_yaw_ );
    }
    else {
      // Compute yaw just according to gyro value (takes into account external actions on the robot)
      yaw = radnorm( last_yaw_ - init_yaw_ );
    }
    
    // Use this value (note that if we use gyro, this function is used only as a storage
    if (driver) driver->SetOdometryAngle( yaw );
    
    subs_yaw_sensor_freq->tick();
  }

  void imuCallback(const sensor_msgs::ImuConstPtr& msg)
  {
    double roll_msg, pitch_msg, yaw_msg;
    tf::Quaternion q(msg->orientation.x, msg->orientation.y, msg->orientation.z,msg->orientation.w);
    tf::Matrix3x3(q).getRPY(roll_msg, pitch_msg, yaw_msg);
    
    if (bFirstYawRead_) delta_yaw_ = yaw_msg - last_yaw_;
    
    last_yaw_sensor_time = ros::Time::now();	
    // Store the first value received  
    if (!bFirstYawRead_) {
      init_yaw_=yaw_msg;
      bFirstYawRead_ = true;
      motion_yaw_ = init_yaw_; // 
    }
    
    // Compute angle according to the init value
    last_yaw_ = yaw_msg;
    
    double yaw;
    if (motion_odometry_=="true") {
      // Integrate yaw only if robot is in motion (avoids integrating drift when robot is stopped for long periods)
      if (driver->InMotion()) motion_yaw_ += delta_yaw_;
      yaw = radnorm( motion_yaw_ );
    }
    else {
      // Compute yaw just according to imu value (takes into account external actions on the robot)
      yaw = radnorm( last_yaw_ - init_yaw_ );
    }
    
    // Use this value (note that if we use imu, this function is used only as a storage
    if (driver) driver->SetOdometryAngle(yaw);  
    subs_yaw_sensor_freq->tick();
  }
    
  //! Sets the digital outputs (note that there are 3 per drive)
  bool srvCallback_SetDigitalOutput(robotnik_msgs::set_digital_output::Request &req, robotnik_msgs::set_digital_output::Response &res )
  {
	ROS_INFO("summit_xl_controller::set_digital_output: request set output %d to %d", req.output, req.value);

	driver->SetDigitalOutput( req.output, req.value );
	// 
	res.ret = true;
	
	return true;
  }
  
  int read_and_publish()
  {
    static double prevtime = 0;
    
    double starttime = ros::Time::now().toSec();
    if (prevtime && prevtime - starttime > 0.05)
      {
	ROS_WARN("Full summit_xl_controller loop took %f ms. Nominal is 10ms.", 1000 * (prevtime - starttime));
	was_slow_ = "Full summit_xl_controller loop was slow.";
	slow_count_++;
      }

    // Get data from the Motors
    odom = driver->GetOdometry();

    double endtime = ros::Time::now().toSec();
    if (endtime - starttime > 0.05)
      {
	ROS_WARN("Gathering data took %f ms. Nominal is 10ms.", 1000 * (endtime - starttime));
	was_slow_ = "Full summit_xl_controller loop was slow.";
	slow_count_++;
      }
    prevtime = starttime;
    starttime = ros::Time::now().toSec();
    ros::Time current_time = ros::Time::now();		
    
    //first we'll publish the transforms over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = odom_frame_id;
    odom_trans.child_frame_id = base_frame_id;
    odom_trans.transform.translation.x = odom.px;   
    odom_trans.transform.translation.y = odom.py;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(odom.pa);
    //send the transform over /tf
    // activate / deactivate with param
    // this tf is needed when not using robot_pose_ekf
    if (publish_odom_tf_=="true") tf_broadcaster.sendTransform(odom_trans);
	
    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom_msg;
    odom_msg.header.stamp = current_time;
    odom_msg.header.frame_id = odom_frame_id;
    //set the position
    odom_msg.pose.pose.position.x = odom.px;
    odom_msg.pose.pose.position.y = odom.py;
    odom_msg.pose.pose.position.z = 0.0;
    odom_msg.pose.pose.orientation = tf::createQuaternionMsgFromYaw(odom.pa);

    //set the velocity
    odom_msg.child_frame_id = base_frame_id;
    odom_msg.twist.twist.linear.x = odom.v * cos( odom.pa );
    odom_msg.twist.twist.linear.y = odom.v * sin( odom.pa );
    //odom_msg.twist.twist.linear.x = odom.v;
    //odom_msg.twist.twist.linear.y = 0.0;	
    odom_msg.twist.twist.angular.z = odom.w;
    
    // Pose covariance
    /*
      for(int i = 0; i < 3; i++)
      odom_msg.pose.covariance[i*6+i] = 0.01;  // test 0.001
      for(int i = 3; i < 6; i++)
      odom_msg.pose.covariance[i*6+i] = 99999;
      // Twist covariance
      for(int i = 0; i < 3; i++)
      odom_msg.twist.covariance[6*i+i] = 0.01;  // test 0.001
      for(int i = 3; i < 6; i++)
      odom_msg.twist.covariance[6*i+i] = 99999;  // test 0.001
    */

    odom_msg.pose.covariance[0]=0.01;   // X
    odom_msg.pose.covariance[7]=0.01;   // Y
    odom_msg.pose.covariance[14]=99999; // Z
    odom_msg.pose.covariance[21]=99999; // R
    odom_msg.pose.covariance[28]=99999; // P
    odom_msg.pose.covariance[35]=0.01;  // Y
    
    odom_msg.twist.covariance[0]=0.02;  // vx
    odom_msg.twist.covariance[7]=99999; // vy
    odom_msg.twist.covariance[14]=99999; // vz
    
    odom_msg.twist.covariance[21]=99999; // wR
    odom_msg.twist.covariance[28]=99999; // wP
    odom_msg.twist.covariance[35]=99999; // wY set to 0 by the driver (could be computed as difference of two measurements)

    //publish the message
    odom_pub_.publish(odom_msg);

    //publish the battery level
    std_msgs::Float32 battery_msg;
    battery_msg.data = driver->GetDCBusVoltage();
    battery_pub_.publish(battery_msg);
	
    if (x_wam_ == "true") {
      // publish the homing status
      std_msgs::Bool homed_msg;
      homed_msg.data = driver->IsHomed();
      homed_pub_.publish(homed_msg);
      
      // publish the scissor mechanism height
      std_msgs::Float32 scissor_msg;
      scissor_msg.data = driver->GetMotorScissorPosition();
      scissor_pub_.publish(scissor_msg);
      
      // publish limit switches
      summit_xl_controller::LimitSwitches limit_switches_msg;
      limit_switches_msg.up = ((driver->GetMotorScissorDigitalInputs() & DIGITAL_INPUT_UP)!=0);
      limit_switches_msg.down = ((driver->GetMotorScissorDigitalInputs() & DIGITAL_INPUT_DOWN)!=0);
      digital_input_pub_.publish( limit_switches_msg );
    }
    
    // publish e-stop
    std_msgs::Bool estop_msg;
    estop_msg.data = ((driver->GetMotorFlwDigitalInputs() & DIGITAL_INPUT_ESTOP)!=0);
    estop_pub_.publish( estop_msg);
    // publish in_motion
    std_msgs::Bool in_motion_msg;
    in_motion_msg.data = driver->InMotion();
    in_motion_pub_.publish( in_motion_msg);
    
    // Get data from the Motors
    double flw, blw, frw, brw, scissor;
    driver->GetMotorSpeeds( &flw, &blw, &frw, &brw, &scissor );
    //ROS_INFO("Motor speeds [m/s]  : flw: %5.2f blw: %5.2f frw: %5.2f brw: %5.2f", flw, blw, frw, brw);
    // driver->GetConsumedCurrent( &flw, &blw, &frw, &brw );
    //ROS_INFO("Motor currents [A]  : flw: %5.2f blw: %5.2f frw: %5.2f brw: %5.2f", flw, blw, frw, brw);
    robot_joints_.header.stamp = ros::Time::now();
    
    // TODO Sign to be moved to a parameter XL HL
    robot_joints_.position[0] = robot_joints_.position[0] - frw * SPEED_SCALE_FACTOR / desired_freq_;
    robot_joints_.position[1] = robot_joints_.position[1] + flw * SPEED_SCALE_FACTOR / desired_freq_;
    robot_joints_.position[2] = robot_joints_.position[2] + blw * SPEED_SCALE_FACTOR / desired_freq_;
    robot_joints_.position[3] = robot_joints_.position[3] - brw * SPEED_SCALE_FACTOR / desired_freq_;
    
    if(x_wam_ == "false")
      robot_joints_.position[4] = 0.0;
    else
      { 
	if( !driver->IsHomed() )
	  robot_joints_.position[4] = 0.0;
	else 
	  {
	    // get scissor height
	    double scissor_position = driver->GetMotorScissorPosition();
	    scissor_position = scissor_position / 4000 * 0.325958931; //counts to mm
	    scissor_position = 200 - scissor_position;
	    double rover_height = sqrt( (571*571)  - ((scissor_position + 353.8)*(scissor_position + 353.8)));
	    
	    //height to joint relative position
	    rover_height = rover_height - 139.09;
	    robot_joints_.position[4] = rover_height * 0.5 / 309.13;
	  }
      }
    
    // TODO sign to be moved to parameter
    robot_joints_.velocity[0] = -frw * SPEED_SCALE_FACTOR;
    robot_joints_.velocity[1] = flw * SPEED_SCALE_FACTOR;
    robot_joints_.velocity[2] = blw * SPEED_SCALE_FACTOR; 
    robot_joints_.velocity[3] = -brw * SPEED_SCALE_FACTOR;
    robot_joints_.velocity[4] = 0.0;
    
    joint_state_pub_.publish( robot_joints_ );
    
    endtime = ros::Time::now().toSec();
    if (endtime - starttime > 0.05)
      {
	ROS_WARN("Publishing took %f ms. Nominal is 10 ms.", 1000 * (endtime - starttime));
	was_slow_ = "Full summit_xl_controller loop was slow.";
	slow_count_++;
      }
    freq_diag_.tick();
    return(0);
}

bool spin()
{
    ROS_INFO("summit_xl_controller::spin() - 1");
    ros::Rate r(desired_freq_);  // 50.0 

    while (!ros::isShuttingDown()) // Using ros::isShuttingDown to avoid restarting the node during a shutdown.
    {
      if (start() == 0)
      {
        // while(node_handle_.ok()) {
	while(ros::ok() && node_handle_.ok()) {
	  if(read_and_publish() < 0)
	    break;
	  self_test_.checkTest();
	  diagnostic_.update();
	  ros::spinOnce();
	  if (iPublishstatus>100) {
	    controller_publishing();
	    iPublishstatus=0;
	  }
	  iPublishstatus++;
	  r.sleep();
	}
	ROS_INFO("END OF ros::ok() !!!");
      } else {
	// No need for diagnostic here since a broadcast occurs in start
	// when there is an error.
	usleep(1000000);
	self_test_.checkTest();
	ros::spinOnce();
      }
    }
    
    ROS_INFO("summit_xl_controller::spin() - 2");
    return true;
}

}; // class summit_xl_node

// MAIN
int main(int argc, char** argv)
{
  //summit_xl_controller::Battery battery;
  ros::init(argc, argv, "summit_xl_controller_node");
  
  ros::NodeHandle n;		
  summit_xl_node sxlc(n);
  
  ros::ServiceServer service = n.advertiseService("set_odometry", &summit_xl_node::set_odometry, &sxlc);
  
  sxlc.spin();
  return (0);
}
// EOF






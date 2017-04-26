/*
 * gps_map_tf
 * Copyright (c) 2013, Robotnik Automation, SLL
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Robotnik Automation, SLL. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \author Robotnik Automation, SLL
 * \brief Allows to use local coordinates based on a gps localization. 
          Initializes gps coords, gets gps heading and publishes a transform from map
	  to gps location.
 */

#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <sensor_msgs/NavSatFix.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include "self_test/self_test.h"
#include "diagnostic_msgs/DiagnosticStatus.h"
#include "diagnostic_updater/diagnostic_updater.h"
#include "diagnostic_updater/update_functions.h"
#include "diagnostic_updater/DiagnosticStatusWrapper.h"
#include "diagnostic_updater/publisher.h"

#include <gps_map_tf/set_gps_origin.h>
//#include <mediatek_gps/gprmc.h>
#include <gps_common/GPSFix.h>

using namespace std;

class gps_map
{

private:
  
  //! Diagnostics
  self_test::TestRunner self_test_;
  ros::NodeHandle node_handle_;
  ros::NodeHandle private_node_handle_;
  double desired_freq_;
  diagnostic_updater::Updater diagnostic_;			// General status diagnostic updater
  diagnostic_updater::FrequencyStatus freq_diag_;		         // Component frequency diagnostics
  diagnostic_updater::HeaderlessTopicDiagnostic *subs_command_freq; // Topic reception frequency diagnostics
  ros::Time last_command_time;					// Last moment when the component received a command

  //! Node running
  bool running;

  //! Origin has been set
  bool origin_set_;

  //! Subscriber to gps msgs
  ros::Subscriber nav_sat_fix_sub_;

  //! Subscriber to utm converted gps-odom odom type localizations
  ros::Subscriber utm_gps_conv_sub_;

  //! Subscriber to gps gprmc messages (to get gps heading estimation)
  ros::Subscriber gps_gprmc_sub_;

  //! Subscriber to gps gprmc messages (to get gps heading estimation)
  ros::Subscriber gps_extended_fix_sub_;

  //! Publisher GPS x,y,th 
  ros::Publisher gps_xyth_pub_; 

  //sensor_msgs::NavSatFix current_localization;
  //sensor_msgs::NavSatFix origin_localization;

  //! current localization variables
  int status_;
  double latitude_;
  double longitude_;
  double altitude_; 
  double ground_speed_;
  double heading_; 

  //! map origin default coordinates 2D [m]
  double x_ori_, y_ori_, yaw_ori_;
  //! current coordinates 2D [m]
  double x_, y_, yaw_;

  //parameter for what odom to use
  std::string odom_frame_id_;
  
  //parameter for what base to use
  std::string base_frame_id_;
  std::string global_frame_id_;
  //! GPS model used ("mediatek" or "gpsd")
  std::string gps_model_;

  //! Transform Listener and Broadcaster
  tf::TransformListener* tf_;
  tf::TransformBroadcaster* tfb_;

  //! Tf published
  tf::Transform latest_tf_;

  //! Ros time - utm conv callback stamp 
  ros::Time timestamp_;
 
  //! Test node with fake gps vo positions
  bool bTest_;

public:

  //! Error counters and flags 
  int error_count_;
  std::string was_slow_;
  std::string error_status_;

  //! Service to define current /map origin related to world coordinates
  ros::ServiceServer srv_set_gps_origin_;

  //! Service to get current /map origin related to world coordinates 
  ros::ServiceServer srv_get_gps_origin_;

  //! Gps localization topic 
  sensor_msgs::NavSatFix NavSatFixMsg;
  
/*!	\fn gps_map_tf()
 * 	\brief Public constructor
*/
gps_map(ros::NodeHandle h) : self_test_(), diagnostic_(),
  node_handle_(h), private_node_handle_("~"), 
  error_count_(0),
  desired_freq_(10),
  freq_diag_(diagnostic_updater::FrequencyStatusParam(&desired_freq_, &desired_freq_, 0.05)   )
  {
    running = false;
    
    ros::NodeHandle gps_map_tf_node_handle(node_handle_, "gps_map_tf");

    // Parameters 
    // global, odom and base frames 
    // TODO: we suppose gps and base_link will be coincident 
    gps_map_tf_node_handle.param("global_frame_id", global_frame_id_, std::string("map"));
    gps_map_tf_node_handle.param("odom_frame_id", odom_frame_id_, std::string("odom"));
    gps_map_tf_node_handle.param("base_frame_id", base_frame_id_, std::string("base_footprint"));

    gps_map_tf_node_handle.param("gps_model", gps_model_, std::string("gpsd"));

	ROS_INFO("Using gps model %s", gps_model_.c_str());

    if (gps_model_ == "mediatek") {

		// Subcscribe to gps standard msg
		nav_sat_fix_sub_ = gps_map_tf_node_handle.subscribe<sensor_msgs::NavSatFix>
								("/gps/nav_sat_fix", 1, &gps_map::gpsNavSatFixCallback, this );

		// Subscribe to gps msg GPRMC in order to read heading
		//gps_gprmc_sub_ = gps_map_tf_node_handle.subscribe<mediatek_gps::gprmc>("/gps/gprmc", 1, &gps_map::gpsGprmcCallback, this);
		}
	else if (gps_model_ == "gpsd") {
		
		// Subcscribe to gps standard msg
		nav_sat_fix_sub_ = gps_map_tf_node_handle.subscribe<sensor_msgs::NavSatFix>
								("/fix", 1, &gps_map::gpsNavSatFixCallback, this );
		
		// Subscribe to gps msg GPRMC in order to read heading
		gps_extended_fix_sub_ = gps_map_tf_node_handle.subscribe<gps_common::GPSFix>("/extended_fix", 1, &gps_map::gpsExtendedFixCallback, this);
	    }
		
    // Subscribe to utm converted gps coordinates
    utm_gps_conv_sub_ = gps_map_tf_node_handle.subscribe<nav_msgs::Odometry>("/vo", 1, &gps_map::gpsUtmGpsConvCallback, this );

    // Advertise topics 
    gps_xyth_pub_ = gps_map_tf_node_handle.advertise<geometry_msgs::Pose2D>("relative_pose", 50);

    // Advertise services
    srv_set_gps_origin_ = gps_map_tf_node_handle.advertiseService("set_gps_origin", &gps_map::srvSetGpsOriginCallback, this);

    // Component frequency diagnostics
    diagnostic_.setHardwareID("gps_map_tf");
    diagnostic_.add("GPS Map Diagnostic", this, &gps_map::gps_map_tf_diagnostic);
    diagnostic_.add( freq_diag_ );    

    // Origin coordinates
    x_ori_ = 0.0; y_ori_ = 0.0; yaw_ori_ = 0.0;
    // Last measured coordinates
    x_ = 0.0; y_ = 0.0; yaw_ = 0.0;

    // New transform broadcaster and listener 
    tf_ = new tf::TransformListener();
    tfb_ = new tf::TransformBroadcaster();

    // Origin is not set at startup
    origin_set_ = false;

    // By default not testing
    bTest_ = false;
  }

/*
 *\brief Subscribed topic gps msg NavSatFix
 *
 */
void gpsNavSatFixCallback(const sensor_msgs::NavSatFix::ConstPtr& navsatfix_msg)
{
     status_ = navsatfix_msg->status.status;   // -1 NO_FIX 0 FIX 1 SBAS_FIX 2 GBAS_FIX
     latitude_ = navsatfix_msg->latitude;
     longitude_ = navsatfix_msg->longitude;
     altitude_ = navsatfix_msg->altitude;
}

/*
 *\brief Subscribed topic gps msg NavSatFix
 *
 */
void gpsUtmGpsConvCallback(const nav_msgs::Odometry::ConstPtr& gpsutmodom_msg)
{
     // Get the position
  
     // First check - update only if status 1 or 2
     if (gpsutmodom_msg->pose.pose.position.z==99999.0) bTest_=true;
     if ((status_ == 1) || (status_ == 2) || (bTest_)) {
       timestamp_ = gpsutmodom_msg->header.stamp;
       x_ = gpsutmodom_msg->pose.pose.position.x;
       y_ = gpsutmodom_msg->pose.pose.position.y;
       }

     // Get the orientation from the course (heading) provided by other GPS messages
     // I assume that the utm gps conv node is not calculating the heading from gps locations.
}

/*
 *\brief Subscribed topic gps msg GPRMC in Mediatek gps to read heading (= course = track)
 *
 */
/*
void gpsGprmcCallback(const mediatek_gps::gprmc::ConstPtr& gprmc_msg)
{
     // Get the data
     // If the GPRMC data is valid
     if ( (gprmc_msg->validity)&&((status_==1)||(status_==2)) ) {
     	ground_speed_ = gprmc_msg->ground_speed;  // in knots
	    yaw_ = (gprmc_msg->course / 180.0) * 3.1415926535;
	    ROS_INFO("Set Yaw = %5.2f", yaw_);
	    }
}
*/

/*
 *\brief Subscribed topic gps msg GPRMC in Mediatek gps to read heading ( = course = track)
 *
 */
void gpsExtendedFixCallback(const gps_common::GPSFix::ConstPtr& gps_extended_fix_msg)
{
     // Get the data
     // The fields to be checked are status, track and err_track
     // err_track = nan when the track data is not stable
     if ( (!std::isnan(gps_extended_fix_msg->err_track)) && ((status_==1)||(status_==2)) ) {
     	ground_speed_ = gps_extended_fix_msg->speed;  // in knots
	    yaw_ = (gps_extended_fix_msg->track / 180.0) * 3.1415926535;
	    ROS_INFO("Set Yaw = %5.2f", yaw_);
	    }
}

/*
 *	\brief Service set_gps_origin
 *
 */
bool srvSetGpsOriginCallback(gps_map_tf::set_gps_origin::Request &req, gps_map_tf::set_gps_origin::Response &res )
{
	ROS_INFO("gps_map_tf::srvSetGpsOrigin Callback");
	if (req.value) {
		// Check if GPS coordinates are coherent and if gps status allows to use the given coords as map origin
		if ((x_ != 0.0) && (y_ !=0.0)) {
			if ((status_ == 1) || (status_ == 2) || (bTest_)) {     // SBAS or GBAS i.e. 3D fix
				x_ori_ = x_;
				y_ori_ = y_;
				// yaw_ori_ = yaw_;
				yaw_ori_ = 0.0;
				ROS_INFO("Set Origin to x: %5.2f y: %5.2f yaw: %5.2f", x_ori_, y_ori_, yaw_ori_);
				origin_set_ = true;
				res.ret = true;
				return true;
			        }
			else {
				ROS_INFO("GPS Status (%d) does not allow to set the current location as origin", status_);
				res.ret = false;
				return false;
			        }
		       }
		else {
		    ROS_INFO("GPS is not measuring position");
		    res.ret = false;
		    return false;
		    }
	        }
	
	// No request 
	res.ret = false;
	return false;
}


/*
 *\brief Checks the status of the component. Diagnostics
 *
 */
void gps_map_tf_diagnostic(diagnostic_updater::DiagnosticStatusWrapper &stat)
{
	/*
	stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "Controller ready");
	stat.summary(diagnostic_msgs::DiagnosticStatus::WARN, "Controller initialing");
	stat.summary(diagnostic_msgs::DiagnosticStatus::ERROR, "Controller on Failure or unknown state");
	// add and addf are used to append key-value pairs.
	stat.add("State FLW", driver->GetMotorFlwStateString()); // Internal controller state
        */ 
}

/*
void test()
{

  Pose 
  map_pose.header.frame_id = "map";
  map_pose.header.stamp = ros::Time::now();
 
  map_pose.pose.position.x = x_;
  map_pose.pose.position.y = y_;
  geometry_msgs::Quaternion quat = tf::createQuaternionMsgFromYaw( th_ );
  map_pose.pose.orientation = quat;

  ROS_INFO("quat (X=%5.2f y=%5.2f z=%5.2f w=%5.2f)", map_pose.pose.orientation.x,
           map_pose.pose.orientation.y, map_pose.pose.orientation.z, map_pose.pose.orientation.w );
  

  //first we'll publish the transforms over tf
  geometry_msgs::TransformStamped odom_trans;
	odom_trans.header.stamp = current_time;
	odom_trans.header.frame_id = odom_frame_id;
	odom_trans.child_frame_id = base_frame_id;
	odom_trans.transform.translation.x = odom.px;   
	odom_trans.transform.translation.y = odom.py;
	odom_trans.transform.translation.z = 0.0;
	odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(odom.pa);
        // activate / deactivate with param
	if (publish_odom_tf_) tf_broadcaster_.sendTransform(odom_trans);


}
*/

/*
  	// time stamp
  	tf_map_to_odom_.stamp_ = ros::Time::now();

  	// specify actual transformation vectors from odometry
  	// NOTE: zeros have to be substituted with actual variable data
  	tf_map_to_odom_.setOrigin(tf::Vector3(0.0f, 0.0f, 0.0f));
  	tf_map_to_odom_.setRotation(tf::Quaternion(0.0f, 0.0f, 0.0f));

	// broadcast transform
	tf_br_.sendTransform(tf_map_to_odom_);
*/


bool spin() 
{
  static double x_ant = 0.0;
  static double y_ant = 0.0;

  /*
  // We know the gps correction map->base_link     
  // Get tf odom->base_link and compute tf map->odom    
  // in summary : mTo = mTb * (oTb)^-1 = mTb * bTo

  // Works ok
  tf::StampedTransform oTb;
        try{
            //listener.lookupTransform("base_link", "odom", ros::Time(0), oTb);
            this->tf_->lookupTransform("odom", "base_link", ros::Time(0), oTb);
           }
        catch (tf::TransformException ex){
            ROS_ERROR("lookupTransform %s",ex.what());
            }

   ROS_INFO("oTb x=%5.5f y=%5.5f", oTb.getOrigin().x(), oTb.getOrigin().y() );
   // tf1.inverseTimes(tf2);
   */ 

   if (origin_set_) {
 
        ROS_INFO("ORIGIN (%5.2f,%5.2f) ACTUAL(%5.2f,%5.2f)", x_ori_, y_ori_,x_,y_);
	// TODO: Let's first work in the GPS world orientation 
	// We could also use an oriented local frame

	double x = x_ - x_ori_;
	double y = y_ - y_ori_;
	double dyaw = yaw_ - yaw_ori_;

        geometry_msgs::Pose2D pose2d;

        // Check if value makes sense or not this might happen even if the status is OK
        if ((fabs(x - x_ant) < 25.0) && (fabs(y - y_ant) < 25.0)) {

	   // Compute tf origin -> gps
	   pose2d.x = x;
	   pose2d.y = y;
   	   pose2d.theta = dyaw;  
	
           // radnorm 
           if (pose2d.theta > 3.1415926535) pose2d.theta -= 2*3.1415926535;
           if (pose2d.theta < -3.1415926535) pose2d.theta += 2*3.1415926535;

	   x_ant = pose2d.x;
	   y_ant = pose2d.y;     	

	   }

	// Publish gps relative position
	gps_xyth_pub_.publish( pose2d );
			
        // this is how AMCL would do it, but in AMCL it seems that the frame seq is base_link->odom->map     
	// subtracting base to odom from map to base and send map to odom instead
	ros::Time current_time = ros::Time::now();		
     	tf::Stamped<tf::Pose> odom_to_map;
	try {
        	tf::Transform tmp_tf(tf::createQuaternionFromYaw(pose2d.theta),
                             tf::Vector3(pose2d.x,
                                         pose2d.y,
                                         0.0));
        	tf::Stamped<tf::Pose> tmp_tf_stamped (tmp_tf.inverse(),
                                              ros::Time(0),
					      //timestamp_,
                                              //current_time,
                                              base_frame_id_);
        	this->tf_->transformPose( odom_frame_id_,
                                 tmp_tf_stamped,
                                 odom_to_map);
      		}
      	catch(tf::TransformException ex) {
                ROS_ERROR("Failed to subtract base to odom transform : %s", ex.what());
        	ROS_DEBUG("Failed to subtract base to odom transform : %s", ex.what());
        	return false;
      		}
      	latest_tf_ = tf::Transform(tf::Quaternion(odom_to_map.getRotation()),
		                 tf::Point(odom_to_map.getOrigin()));

    	ros::Duration transform_tolerance;
	transform_tolerance.fromSec( 0.5 ); // Time in secs 

	// We want to send a transform that is good up until a
	// tolerance time so that odom can be used
	ros::Time transform_expiration = (current_time + transform_tolerance);
	tf::StampedTransform tmp_tf_stamped(latest_tf_.inverse(),
		                          transform_expiration,
		                          global_frame_id_, odom_frame_id_);
	this->tfb_->sendTransform(tmp_tf_stamped);
        
        ROS_INFO("tmp_tf_stamped x=%5.2f y=%5.2f", tmp_tf_stamped.getOrigin().x(), tmp_tf_stamped.getOrigin().y() );  

        /*
        // Transform map->odom
        tf::Transform tf_map_to_base(tf::createQuaternionFromYaw(pose2d.theta),
                             tf::Vector3(pose2d.x,
                                         pose2d.y,
                                         0.0));
        // time stamp
        tf_map_to_odom_.stamp_ = ros::Time::now();

        // specify actual transformation vectors from odometry
        // NOTE: zeros have to be substituted with actual variable data
        tf_map_to_odom_.setOrigin(tf::Vector3(0.0f, 0.0f, 0.0f));
        tf_map_to_odom_.setRotation(tf::Quaternion(0.0f, 0.0f, 0.0f));

        // broadcast transform
        tf_br_.sendTransform(tf_map_to_odom_);
        */

	}

  return true;
}
  
}; // class gps_map_tf


int main(int argc, char** argv){

  ros::init(argc, argv, "gps_map_tf");
 
  ros::NodeHandle n;		
  
  // Create object
  gps_map gps_map(n);

  ros::Rate r(10.0);

  // Main Loop
  while( ros::ok() ){
        
	gps_map.spin();
	ros::spinOnce();
	r.sleep();
	}

  return 0;
}


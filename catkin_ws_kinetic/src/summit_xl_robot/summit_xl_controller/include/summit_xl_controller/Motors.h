/*! \class Motors
 *	\author Robotnik Automation S.L.L
 *	\version 1.2 - XL
 *	\date 2012
 *  \brief Class for controlling motors connected to dpcante's motor drivers and I/O modules
 * 	Controla y gestiona la comunicación con los motores de dirección y tracción conectados a drivers dpcante de AMC
 *  así como la gestión de un módulo de entradas salidas
 *  (C) 2010 Robotnik Automation, SLL
 *  All rights reserved.
 */

#ifndef __DRIVER_H
	#define __DRIVER_H

#include "summit_xl_controller/MotorVelocity.h"
#include "summit_xl_controller/MotorPosition.h"
#include <vector>

// DEFAULT 100Hz 4 drivers 

#define MOTORS_DEFAULT_THREAD_HZ		50.0		// Frequency to control the motors' state by default
#define IO_DEFAULT_THREAD_HZ			50.0		// Frequency to control the inputs/outputs
#define DEFAULT_FLW_ID		    		1		// CAN-ID for Forward Left MotorDrive
#define DEFAULT_BLW_ID                  2 		// CAN-ID for Backward Left MotorDrive
#define DEFAULT_FRW_ID                  3		// CAN-ID for Forward Right MotorDrive
#define DEFAULT_BRW_ID                  4 		// CAN-ID for Backward Right MotorDrive

#define DEFAULT_SCISSOR_ID				7

#define LINEAR_ACCELERATION_DEFAULT		10.0    // 10.0		// m/s²
#define ANGULAR_ACCELERATION_DEFAULT		36.0		// 36.0 //rad/s²
#define DEFAULT_MAX_LINEAR_VELOCITY            	2.25         	// m/s
#define DEFAULT_MAX_ANGULAR_VELOCITY           	6.28         	// rad/s <- max wheel vel will limit first
#define DEFAULT_MAX_SCISSOR_VELOCITY    400.0    // speed of the linear actuator

#define KINEMATIC_PARAM_LA              0.2845   // from robot center to wheel center in Y axis [m]
#define KINEMATIC_PARAM_LB              0.2715;  // from robot center to wheel center in X axis [m]

#define DIGITAL_INPUT_ESTOP             0x01
#define DIGITAL_INPUT_UP                0x02
#define DIGITAL_INPUT_DOWN              0x04

//! Possible alarms
enum DriveAlarm{
	DRIVER_NUM_ERRORS = 10,				// Number of defined erros
	DRIVER_ALARM_COMM_FLW = 0,			// Error CAN Comm on motor FLW
	DRIVER_ALARM_COMM_BLW = 1,			// Error CAN Comm on motor BLW
	DRIVER_ALARM_COMM_FRW = 2,			// Error CAN Comm on motor FLW
	DRIVER_ALARM_COMM_BRW = 3,			// Error CAN Comm on motor BLW
	DRIVER_ALARM_STATUS_FLW = 4,			// Motor FLW on FAULT
	DRIVER_ALARM_STATUS_BLW = 5,			// Motor BLW on FAULT
	DRIVER_ALARM_STATUS_FRW = 6,			// Motor FRW on FAULT
	DRIVER_ALARM_STATUS_BRW = 7,			// Motor BRW on FAULT
	DRIVER_ALARM_CAN = 8,				// Error on communication with CAN device
	DRIVER_ALARM_EMERGENCY_STOP = 9,		// Emergency stop has been pressed		
};

//! Struct to save the odmetry of the robot
typedef struct Odometry{
	//! X coordinate
	double px;
	//! Y coordinate
	double py;
	//! Robot yaw
	double pa;
	//! Linear speed
	double v;
	//! X speed
	double vx;
	//! Y speed
	double vy;
	//! Angular speed
	double w;
}Odometry;

//! Class driver
class Motors: public Component{

private:
	//! CAN device
	PCan *canDev;
	//! motor traction objects
	MotorVelocity *motorFlw;
	MotorVelocity *motorFrw;
	MotorVelocity *motorBlw;
	MotorVelocity *motorBrw;
	//! motor for scissor mechanism
	MotorVelocity *motorScissor;
	
	//! CAN ids
	byte idMotorFlw, idMotorFrw, idMotorBlw, idMotorBrw, idMotorScissor;
	//! Desired linear speed (m/s)
	double dDesiredLinearSpeedX;
	double dDesiredLinearSpeedY;
	//! Desired angular speed (deg/s)
	double dDesiredAngularSpeed;
	//! Desired scissor speed
	double dDesiredScissorSpeed;
	//! Desired position (m)
	double dDesiredPosition;
	//! Real speed (m/s)
	double dRealSpeed;
	//! Contains the last ocurred error
	DriveAlarm deErrorType;
	//! Speed acceleration and deceleration
	// double dAcceleration, dDeceleration;
	//! Value for the maximun velocity of the robot
	double dMaxLinearVelocity;
	//! Value for the maximun velocity of the robot
	double dMaxAngularVelocity;

	//! Time of the last recover action
	struct timespec tRecovery;
	//! Flags vector with errors and alarms
	vector<bool> vAlarms;
	//! Skid-Steer Odometry Value
	Odometry odomPosition;
	//! Mutex for controlling the changes and access to odomety values
	pthread_mutex_t mutexOdometry;
	//! Flag to enable / disable the odometry's internal calc
	bool bOdometry;
	//! Last encoder measure
	int iLastEncoderVelocityValue;
	//! Constant to convert from rpm to mps
	double dRpmToMps;
	//! Flag for markin that homing has been made
	bool bHomed;
	//! Home state machine variable (substates of the ReadyState)
	int iHoming;
	//! Scissor position in the lower limit switch
	int iScissorOriginPosition;
	//! Flag to use or not the yaw sensor (Gyro or IMU) to calculate the orientation
	bool bYawSensor;
	//! Kinematic Mode for Odometry Update
	bool bOmni;	
	//! Component desired frequency
	double dFreq;
	//! Acceleration
	double dAcceleration;
	
public:
        //! Public constructor
	Motors(string dev, double diameter_wheel, double gearbox, double hz, bool xwam,bool omni, double acceleration);
	//! Public constructor
	Motors(string dev, double diameter_wheel, double gearbox, double hz, bool xwam,bool motors_encoder,double motors_encoder_factor,bool omni, double acceleration);        
	//! Public constructor
	Motors(double hz, bool xwam, double acceleration);
	//! Public constructor
	Motors(uint16_t baudrate, bool xwam, double hz, double acceleration);
	//! Public destructor
	~Motors();
	//! Setups the component
	//! @return OK
	//! @return ERROR
	ReturnValue Setup();
	//! Closes and frees the reserved resources
	//! @return OK
	//! @return ERROR if fails when closes the devices
	//! @return RUNNING if the component is running
	//! @return NOT_INITIALIZED if the component is not initialized
	virtual ReturnValue ShutDown();
	//! Starts the control thread of the component and its subcomponents
	//! @return OK
	//! @return ERROR starting the thread
	//! @return RUNNING if it's already running
	//! @return NOT_INITIALIZED if it's not initialized
	ReturnValue Start();
	//! Stops the main control thread of the component and its subcomponents
	//! @return OK
	//! @return ERROR if any error has been produced
	//! @return NOT_RUNNING if the main thread isn't running
	ReturnValue Stop();
	//! Sets the speed of the motor (m/s),(deg/s)
	ReturnValue SetDesiredSpeed(double linearX, double linearY, double angular, double linearZ);
	//! Sets the position of the linear motor (milimeters ???)
	ReturnValue SetDesiredPosition(double position);

	//! Disables the Motors' action
	void DisableMotors();
	//! Enables the Motors' action
	void EnableMotors();
	//! Set digital outputs
	ReturnValue SetDigitalOutput(int output, bool value);
	//! Returns the error produced
	DriveAlarm GetErrorType();
	//! Gets the desired speed of the robot
	void GetDesiredSpeeds( double* linearX, double* linearY, double* angular, double* linearZ);
	//! Gets the speed read from the driver
	void GetMotorSpeeds( double* flw, double* blw, double* frw, double* brw, double* scissor );
	//! Gets the counts read from the driver
	void GetMotorCounts(long* flw, long* blw, long* frw, long* brw);
	//! Gets the position of the scissor motor
	double GetPosScissor();
	//!  return true if homing is complete
	bool IsHomed();
	//! Initializes the homing procedure
	ReturnValue Home();
	
	//! Get the value of the selected input
	bool GetInput(int input);
	//! Gets the value of the selected output
	bool GetOutput(int output);
	//! Gets the battery level
	double GetBattery();
	//! Gets the DC Bus Voltage level
	double GetDCBusVoltage();
	//! Gets the state of the motor FLW
	char *GetMotorFlwStateString();
	//! Gets the state of the motor BLW
	char *GetMotorBlwStateString();
	//! Gets the state of the motor FRW
	char *GetMotorFrwStateString();
	//! Gets the state of the motor BRW
	char *GetMotorBrwStateString();
    //! Gets the state of the motor Scissor
    char *GetMotorScissorStateString();
    //! Gets the communication state of the motor FLW
	char *GetMotorFlwStatusString();
	//! Gets the communication state of the motor BLW
	char *GetMotorBlwStatusString();
	//! Gets the communication state of the motor FRW
	char *GetMotorFrwStatusString();
	//! Gets the communication state of the motor BRW
	char *GetMotorBrwStatusString();
    //! Gets the communication state of the motor Scissor
    char *GetMotorScissorStatusString();
	//! Gets the status word of the motor direction as string
	char *GetMotorFlwStatusWordString();
	//! Gets the status word of the motor direction as string
	char *GetMotorBlwStatusWordString();
	//! Gets the status word of the motor direction as string
	char *GetMotorFrwStatusWordString();
	//! Gets the status word of the motor direction as string
	char *GetMotorBrwStatusWordString();
    //! Gets the status word of the motor Scissor as string
    char *GetMotorScissorStatusWordString();
    //! Gets the status word of the motor direction as string
	char *GetMotorFlwStatusFlagsString();
	//! Gets the status word of the motor direction as string
	char *GetMotorBlwStatusFlagsString();
	//! Gets the status word of the motor direction as string
	char *GetMotorFrwStatusFlagsString();
	//! Gets the status word of the motor direction as string
	char *GetMotorBrwStatusFlagsString();
    //! Gets the status word of the motor Scissor as string
    char *GetMotorScissorStatusFlagsString();
	//! Checks the status and updates the alarm flag vector
	void ErrorCheck();
	//! Returns the alarms vector
	vector<bool> GetAlarms();
	//! Returns the current position from odometry
	Odometry GetOdometry();
	//! Sets new odometry values
	void ModifyOdometry(Odometry odom);
	//! Resets internal odometry
	void ResetOdometry();
	//! Set odometry angle (yaw)
	void SetOdometryAngle( double yaw );
	//! Sets a new value for the diameter
	void SetWheelDiameter(double diameter);
	//! Gets the value of the diameter
	double GetWheelDiameter();
    //! Gets the current consumed current by the motors
    void GetConsumedCurrent(double *current_flw, double *current_blw, double *current_frw, double *current_brw );
	//! Gets the current update rate of the FLW motor 
	double GetMotorFlwUpdateRate();
	//! Gets the current update rate of the BLW motor 
	double GetMotorBlwUpdateRate();
	//! Gets the current update rate of the FRW motor 
	double GetMotorFrwUpdateRate();
	//! Gets the current update rate of the BRW motor 
	double GetMotorBrwUpdateRate();
	//! Get communication status like a string
	char* GetCommunicationStatusString();
	//! Get the digital inputs (limit switches of the scissor axis)
	unsigned int GetMotorScissorDigitalInputs();
    //! Get the digital inputs of a wheel driver (e-stop)
    unsigned int GetMotorFlwDigitalInputs();
	//! Gets the current position of the scissor mechanism motor
	double GetMotorScissorPosition();

	//! Returns whether or not it is using the yaw sensor (gyro or imu)
	bool IsYawSensor();
	//! Enables/disables the use of the yaw sensor (gyro or imu)
	void SetYawSensor(bool value);
	//! Returns true if the robot is in motion, false otherwise
	bool InMotion();
	//! Change Kinematic Mode
	void KinematicMode(bool Omni);	

private:
	//! Read messages from CAN bus
	ReturnValue ReadCANMessages();
	//! Synchronizes the Motors
	ReturnValue SynchronizeDrives();
	//! Actions in initial state
	void InitState();
	//! Actions when Motors are ready
	void ReadyState();
	//! Actions performed on Failure state
	void StandbyState();
	//! Actions in the emergency state
	void EmergencyState();
	//! Actions performed on Failure state
	void FailureState();
	//! Actions performed in all states
	void AllState();
	//! Sends the references to the Motors
	void SetMotorValues();
	//! Sets the desired digital output
	ReturnValue SetOutput(int num, bool value);
	//! Do the calcs to update the odometry
	void UpdateOdometry();
};

#endif

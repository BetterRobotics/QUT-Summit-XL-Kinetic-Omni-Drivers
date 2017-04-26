/** \file MotorPosition.cc
 * \author Robotnik Automation S.L.L.
 * \version 2.0
 * \date 2010
 * \brief Class for motor drive in position mode
 * (C) 2010 Robotnik Automation, SLL
 *  All rights reserved.
*/

#include "summit_xl_controller/MotorPosition.h"

const double MotorPosition::dHomeSpeed1 = 4.0;		// mm/s
const double MotorPosition::dHomeSpeed2 = 2.0;		// mm/s
const double MotorPosition::dHomeAcceleration = 0.2;	// rad/s2

MotorPosition::~MotorPosition(void){
	//printf("MotorPosition::~MotorPosition\n");
}

/*!	\fn ReturnValue MotorPosition::Initialize()
 * 	\brief Initializes the status of the drive
 * 	\return OK
 * 	\return ERROR
*/
ReturnValue MotorPosition::Initialize(){
	//struct timespec wait;
	int method = 0x01;	// Homing on the positive limit switch
    int home_speed1 = (int)(dHomeSpeed1 * dPos2Ref * dScalingFactorDS4);
	int	home_speed2 = (int)(dHomeSpeed2 * dPos2Ref * dScalingFactorDS4);
    int home_offset = iHomeOffset;
	int home_accel = (int)(dHomeAcceleration * dPos2Ref * dScalingFactorDA1);

	ROS_INFO("XXX - MotorPosition::Initialize(): Initializing the driver...");
	ROS_INFO("XXX - home_speed1=%d   home_speed2=%d", home_speed1, home_speed2);

	if(Send(CanId, DISABLE_VOLT_MSG, WRITE, 0) != OK){
		ROS_ERROR("%s: Initialize: Node %d: Error sending disable voltage", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

	if(Send(CanId, SHUTDOWN_MSG, WRITE, 0) != OK){
		ROS_ERROR("%s: Initialize: Node %d: Error sending shutdown", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

/*
	if(Send(CanId, HOME_OFFSET_MSG, WRITE, home_offset) != OK){
		ROS_ERROR("%s::Initialize: Node %d: Error sending configure home offset", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

	// Set homing method
	if(Send(CanId, HOME_METHOD_MSG, WRITE, method) != OK){
		ROS_ERROR("%s::Initialize: Node %d: Error sending configure home method", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

    if(Send(CanId, HOME_SPEED1_MSG, WRITE, home_speed1) != OK){
		ROS_ERROR("%s::Initialize: Node %d: Error sending configure home speed 1", sComponentName.c_str(), CanId);
		return ERROR;
    }
	Delay();
	
    if(Send(CanId, HOME_SPEED2_MSG, WRITE, home_speed2) != OK){
		ROS_ERROR("%s::Initialize: Node %d: Error sending configure home speed 2", sComponentName.c_str(), CanId);
		return ERROR;
    }
	Delay();
*/

    if(Send(CanId, SWITCH_ON_MSG, WRITE, 0) != OK){
		ROS_ERROR("%s: Initialize: Node %d: Error sending switch on", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

    if(Send(CanId, ENABLE_OP_MSG, WRITE, 0) != OK){
		ROS_ERROR("%s: Initialize: Node %d: Error sending enable operation", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

	//Get the Mode Of Operation
	if(Send(CanId, MODE_OF_OPERATION_MSG, READ, 0) != OK){
		ROS_ERROR("%s: Initialize: Node %d: Error sending get mode of operation", sComponentName.c_str(), CanId);
		return ERROR;
	}
	//Delay();

	return OK;
}

/*!	\fn ReturnValue MotorPosition::Home()
 *	\brief Starts Homing procedure
*/
ReturnValue MotorPosition::Home(){
	ROS_INFO("MotorPosition::Home: Starting");
	bHomingComplete = false;

	ROS_INFO("XXX - Sending Home Command");
    if(Send(CanId, START_HOME_MSG, WRITE, 0) != OK){
		ROS_ERROR("%s::Home: Node %d: Error sending start home", sComponentName.c_str(), CanId);
		return ERROR;
	}
	
	bHoming = true;
		
	return OK;
}

/*!	\fn bool MotorPosition::HomingComplete()
 * 	\brief Return if homing has been completed
 * 	\return true if the homing is completed
*/
bool MotorPosition::HomingComplete(){
	return bHomingComplete;
}

/*!	\fn bool MotorPosition::IsHoming()
 * 	\return true if the driver is homing
*/
bool MotorPosition::IsHoming(){
	return bHoming;
}

/*! \fn double MotorPosition::GetMotorPosition()
 *	\brief function to get the motor position
 *	\return motor speed (in RPM)
*/
double MotorPosition::GetMotorPosition(){
	return iPositionRef * dRef2Pos;
}

/*! \fn int MotorPosition::GetMotorCounts()
 *	\brief function to get the motor position
 *	\return counts of the motor's encoder
*/
int MotorPosition::GetMotorCounts(){
	return iPositionRef;
}

/*!	\fn ReturnValue MotorPosition::SetMotorPosition(int position)
 *	\brief function to set motor's position
 * 	\param position as a int, target position
 * 	\return OK
 *  \return ERROR
*/
ReturnValue MotorPosition::SetMotorPosition(int position){
	int position_aux = 0;
	static bool bError = false;

	if( commStatus == OPERATIONAL){
		position_aux = position;
		//ROS_INFO("%s:SetMotorPosition: sending %d", sComponentName.c_str(), position_aux);
		if(Send(CanId, POSITION_PDO_MSG, WRITE, position_aux) != OK) { 	//
			if(!bError){
				ROS_ERROR("MotorPosition::SetMotorPosition(int): Error sending velocity ref");
				bError = true;
                return ERROR;
            }else
                bError = false;
        }

	}else if(!bError){
        ROS_ERROR("MotorPosition::SetMotorPosition(int): bad communication status");
        bError = true;
    }

	return OK;
}

/*!	\fn ReturnValue MotorPosition::SetMotorPosition(double position)
 *  \brief Function to set motor's position
 * 	\param position as a double, target position in radians
 *  \return OK
 *  \return ERROR
*/
ReturnValue MotorPosition::SetMotorPosition(double position){
	int position_aux = 0;
	static bool bError = false;

	if( commStatus == OPERATIONAL){
		position_aux = (int) (position * dPos2Ref);
		//ROS_INFO("%s:SetMotorPosition: sending %d", sComponentName.c_str(), position_aux);
		
		if(Send(CanId, POSITION_PDO_MSG, WRITE, position_aux) != OK) { 	//
			if(!bError){
				ROS_ERROR("MotorPosition::SetMotorPosition(int): Error sending velocity ref");
				bError = true;
                return ERROR;
            }else
                bError = false;
        }

	}else if(!bError){
        ROS_ERROR("MotorPosition::SetMotorPosition(int): bad communication status");
        bError = true;
    }

	return OK;
}

/*!	\fn ReturnValue MotorPosition::SwitchToPositionMode()
 * 	\brief Perform change of mode after home index reached
 * 	\return OK
 * 	\return ERROR
*/
ReturnValue MotorPosition::SwitchToPositionMode(){
	//int mode = POSITION_MODE;

	// First of all - stop homing on node
	if(Send(CanId, STOP_HOME_MSG, WRITE, 0) != OK) {
		ROS_ERROR("%s::SwitchToPositionMode: Node %d: Error sending stop home", sComponentName.c_str(), CanId );
		return ERROR;
	}
	//Delay();

	return OK;
}

/*!	\fn void MotorPosition::ReadyState()
 *	\brief Actions performed on ready state
 *         MotorDrive will be ready while the communication with the device be OK
*/
void MotorPosition::ReadyState(){

    MotorDrive::ReadyState();

    if(bHomingComplete && bHoming){
	    //ROS_INFO("%s::ReadyState: Stopping home mode",sComponentName.c_str());
		SwitchToPositionMode();
		Delay(10);
		SetMotorPosition(0);
		bHoming = false;
	}
}

/*! \fn void MotorPosition::SetOffset(int value)
 *	\brief Sets the offset value
*/
void MotorPosition::SetOffset(int value){
	iHomeOffset = value;
}

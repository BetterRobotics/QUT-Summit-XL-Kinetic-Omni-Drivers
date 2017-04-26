
/** \file MotorVelocity.cc
 * \author Robotnik Automation S.L.L.
 * \version 2.0
 * \date 2010
 * \brief Class for motor drive in position mode
 * (C) 2010 Robotnik Automation, SLL
 *  All rights reserved.
*/

#include "summit_xl_controller/MotorVelocity.h"

MotorVelocity::~MotorVelocity(void){
}

/*! \fn ReturnValue MotorVelocity::SetMotorVelocity(int speed)
*   \brief Function to set the speed of the motor drive
*   \param speed as a int, target speed in velocity units
*   \return OK
*   \return ERROR
*/
ReturnValue MotorVelocity::SetMotorVelocity(int velocity){
	static bool bError = false;
	int velocity_aux = 0;

	if( commStatus == OPERATIONAL){
		//Change sign to move properly
		velocity_aux = velocity;
		if(Send(CanId, VELOCITY_PDO_MSG, WRITE, velocity_aux) != OK) { 	//
			if(!bError){
				ROS_ERROR("MotorVelocity::SetMotorVelocity(int): Error sending velocity ref");
				bError = true;
                return ERROR;
            }else
                bError = false;
            }

	}else if(!bError){
        	ROS_ERROR("MotorVelocity::SetMotorVelocity(int): bad communication status");
        	bError = true;
    }

	return OK;
}

/*! \fn ReturnValue MotorVelocity::SetMotorVelocity(double speed)
 * 	\brief Function to set the speed of the motor drive
 * 	\param speed as a double, target speed in m/s
 * 	\return OK
 *	\return ERROR
*/
ReturnValue MotorVelocity::SetMotorVelocity(double velocity){
	int velocity_aux = 0;
	static bool bError = false;

    
	velocity_aux = (int) (velocity * dMps2Ref);

	if(commStatus == OPERATIONAL){
		//ROS_INFO("MotorVelocity::SetVelocity:Node: %d,value = %lf,ref = %d,Encoders = %d,EncodersFactor=%f,dMps2Ref=%f", CanId, velocity, velocity_aux,bMotorsEncoder,dMotorsEncoderFactor,dMps2Ref);
		
          if(Send(CanId, VELOCITY_PDO_MSG, WRITE, velocity_aux) != OK) {
            ROS_ERROR("MotorVelocity::SetMotorVelocity(double): Error sending velocity ref");
            bError = true;
            return ERROR;
		}else {
            bError = false;
            //ROS_INFO("MotorVelocity::SetMotorVelocity: id=%d, speed=%lf, ref=%d", CanId, velocity, velocity_aux);
            }
	}else if(!bError){
        ROS_ERROR("MotorVelocity::SetMotorVelocity(double): bad communication status");
        bError = true;
    }

	return OK;
}

/*! \fn double MotorVelocity::GetMotorvelocity()
 * 	\brief function to get the motor speed in m/s
*/
double MotorVelocity::GetMotorVelocity(){

    return (double) iVelocityRef * dRef2Mps;
}

/*! \fn int MotorVelocity::GetMotorPosition()
 * 	\brief function to get the motor counts
*/
int MotorVelocity::GetMotorPosition(){
	return iPositionRef;
}

/*! \fn ReturnValue MotorVelocity::ShutDown()
 * Closes and frees the reserved resources
 * \return OK
 * \return THREAD_RUNNING if the component is running
 * @return NOT_INITIALIZED if the component is not initialized
 * \return ERROR
*/
ReturnValue MotorVelocity::ShutDown(){

	if(bRunning){
		ROS_ERROR("%s::ShutDown: Impossible while thread running, first must be stopped",sComponentName.c_str());
		return THREAD_RUNNING;
	}
	if(!bInitialized){
		ROS_ERROR("%s::ShutDown: Impossible because of it's not initialized", sComponentName.c_str());
		return NOT_INITIALIZED;
	}
	// Sets the velocity to zero
	SetMotorVelocity(0);

	Send(CanId, SHUTDOWN_MSG, WRITE, 0);

	bInitialized = false;

	return OK;
}

/*! \fn void MotorVelocity::SetWheelDiameter(double diameter)
 * 	\brief Sets the value of the diameter
*/
void MotorVelocity::SetWheelDiameter(double diameter){
	dMotorWheelDiameter = diameter;
	
	//If motors with encoders speed must be multiplied
    double dFactor=1.0;
    if (bMotorsEncoder) {
		dFactor=dMotorsEncoderFactor;
	} else {
		dFactor=COUNTS_PER_REV_VEL;
	}

    // Reference send in [cnt*/s] (*) scaled counts per second
    dMps2Ref = (1.0/(dMotorWheelDiameter*Pi)) * TRAC_GEAR * SPEED_SCALE_FACTOR*dFactor;
    dRef2Mps =  1.0 / dMps2Ref;
}

/*! \fn double MotorVelocity::GetMotorWheelDiameter()
 * 	\brief Gets the value of the diameter
*/
double MotorVelocity::GetWheelDiameter(){
	return dMotorWheelDiameter;
}

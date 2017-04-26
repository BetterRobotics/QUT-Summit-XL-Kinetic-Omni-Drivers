/*! \class MotorVelocity
 *	\author Robotnik Automation S.L.L
 *	\version 2.0
 *	\date 2012
 *  \brief Class for motor drive in velocity mode
 *  All rights reserved.
*/

#include "summit_xl_controller/MotorDrive.h"


#ifndef __MOTOR_VELOCITY_H
#define __MOTOR_VELOCITY_H


class MotorVelocity: public MotorDrive {

private:
	//! Diameter of the motor wheel
	double dMotorWheelDiameter;
    //! constant to convert velocity from mps to drive units
    double dMps2Ref;
    //! constant to convert velocity from drive units to mps
    double dRef2Mps;
    //! Gearbox relation
    double gearbox;
    //! Motors Encoder
    //! If Motors with encoder speed must be multiplied by Motors_Encoders_Factor
    //! DO NOT USE IF motors without encoder
    bool bMotorsEncoder;
    double dMotorsEncoderFactor;
	
public:

    //! public constructor
    MotorVelocity(byte can_id, PCan *can_device, double hz): MotorDrive(can_id, can_device, hz){
		//char cAux[LOG_STRING_LENGTH] = "\0";
		sComponentName.assign("MotorVelocity");
		modModeOfOperation  = VELOCITY_MODE;
		dMotorWheelDiameter = MOTOR_WHEEL_DIAMETER;
		gearbox = TRAC_GEAR;
		//If motors with encoders speed must be multiplied
		double dFactor=1.0;
		if (bMotorsEncoder) {
			dFactor=dMotorsEncoderFactor;
		} else {
			dFactor=COUNTS_PER_REV_VEL;
		}
		dMps2Ref = (1.0/(dMotorWheelDiameter*Pi)) * dFactor * gearbox * SPEED_SCALE_FACTOR;  // XL dMps2Ref= 5006,5699006876
		dRef2Mps =  1.0 / dMps2Ref; // XL = 0,0001997375
		bAnalogEnable[0] = true;	// Enables analog input 1
		//sprintf(cAux, "MotorVelocity: Diameter = %lf, dMps2Ref = %lf", dMotorWheelDiameter, dMps2Ref);
		//rlcLog->AddInfo(cAux);
		bMotorsEncoder=false;
		dMotorsEncoderFactor=1.0;
	}
	//! public constructor
    MotorVelocity(byte can_id, PCan *can_device, double hz, double diameter_wheel, double gearbox): MotorDrive(can_id, can_device, hz){
		//char cAux[LOG_STRING_LENGTH] = "\0";
		sComponentName.assign("MotorVelocity");
		modModeOfOperation  = VELOCITY_MODE;
		dMotorWheelDiameter = diameter_wheel;
		this->gearbox = gearbox;
		//If motors with encoders speed must be multiplied
		double dFactor=1.0;
		if (bMotorsEncoder) {
			dFactor=dMotorsEncoderFactor;
		} else {
			dFactor=COUNTS_PER_REV_VEL;
		}
		dMps2Ref = (1.0/(dMotorWheelDiameter*Pi)) * dFactor * gearbox * SPEED_SCALE_FACTOR;  // XL dMps2Ref= 5006,5699006876
		dRef2Mps =  1.0 / dMps2Ref; // XL = 0,0001997375
		bAnalogEnable[0] = true;	// Enables analog input 1
		//sprintf(cAux, "MotorVelocity: Diameter = %lf, dMps2Ref = %lf", dMotorWheelDiameter, dMps2Ref);
		//rlcLog->AddInfo(cAux);
		bMotorsEncoder=false;
		dMotorsEncoderFactor=1.0;
	}
    //! public constructor
    MotorVelocity(byte can_id, PCan *can_device, double hz, double diameter_wheel, double gearbox,bool bEncoder,double dEncoderFactor): MotorDrive(can_id, can_device, hz){
		//char cAux[LOG_STRING_LENGTH] = "\0";
		sComponentName.assign("MotorVelocity");
		modModeOfOperation  = VELOCITY_MODE;
		dMotorWheelDiameter = diameter_wheel;
		this->gearbox = gearbox;
		//If motors with encoders speed must be multiplied
		double dFactor=1.0;
		bMotorsEncoder=bEncoder;
		dMotorsEncoderFactor=dEncoderFactor;
		if (bMotorsEncoder) {
			dFactor=dMotorsEncoderFactor;
		} else {
			dFactor=COUNTS_PER_REV_VEL;
		}
		dMps2Ref = (1.0/(dMotorWheelDiameter*Pi)) * dFactor * gearbox * SPEED_SCALE_FACTOR;  // XL dMps2Ref= 5006,5699006876
		//ROS_INFO(" dMotorWheelDiameter:%f,Pi:%f,dFactor:%f,gearbox:%f,SPEED_SCALE_FACTOR:%f",dMotorWheelDiameter,Pi,dFactor,gearbox,SPEED_SCALE_FACTOR); 
		dRef2Mps =  1.0 / dMps2Ref; // XL = 0,0001997375
		bAnalogEnable[0] = true;	// Enables analog input 1
		//sprintf(cAux, "MotorVelocity: Diameter = %lf, dMps2Ref = %lf", dMotorWheelDiameter, dMps2Ref);
		//rlcLog->AddInfo(cAux);
		
	}

    //! public destructor
    ~MotorVelocity(void);
    //! function to get the motor velocity in m/s
    double GetMotorVelocity();
    //! function to set motor's position
    //! @param position as a int, target position
    //! @return OK
    //! @return ERROR
    ReturnValue SetMotorVelocity(int velocity);
    //! function to set motor's velocity
    //! @param position as a double, target position in rads
    //! @return OK
    //! @return ERROR
    ReturnValue SetMotorVelocity(double velocity);
	//! Closes and frees the reserved resources
	//! @return OK
	//! @return ERROR if fails when closes the devices
	//! @return RUNNING if the component is running
	//! @return NOT_INITIALIZED if the component is not initialized
	ReturnValue ShutDown();
	//! Sets the value of the diameter
	void SetWheelDiameter(double diameter);
	//! Gets the value of the diameter
	double GetWheelDiameter();
	//! Gets motor counts
	int GetMotorPosition();
};

#endif

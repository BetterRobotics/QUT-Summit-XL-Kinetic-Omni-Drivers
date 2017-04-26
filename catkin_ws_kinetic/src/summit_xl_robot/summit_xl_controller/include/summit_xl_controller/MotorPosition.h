/*! \class MotorPosition
 *	\author Robotnik Automation S.L.L
 *	\version 2.0
 *	\date 2010
 *  \brief Class for motor drive in position mode
 * (C) 2010 Robotnik Automation, SLL
 *  All rights reserved.
 */

#include <math.h>
#include "summit_xl_controller/MotorDrive.h"

#ifndef __MOTOR_POSITION_H
	#define __MOTOR_POSITION_H

#define HOME_OFFSET	10000
	
#define K_GEARBOX       1.0 		// Gearbox reduction motor to output
#define SPINDLE_STEP_MM 1.0        // 

class MotorPosition: public MotorDrive {

private:
    //! contains the counts of the motor (Used for calibration and tests)
    int iMotorCounts;
    //! Constant to convert radians to drive's reference
    double dPos2Ref;
    //! Constant to convert drive's reference to radians
    double dRef2Pos;
	//! Constant to scale the values to send to the drive (counts/s)
	double dScalingFactorDS4;
	//! Constant to scale the values to send to the drive (counts/s2)
	double dScalingFactorDA1;
	//! Motor offset in counts
	int iHomeOffset;
	//! 1st stage speed offset in rad/s
	static const double dHomeSpeed1;
	//! 2nd zero speed offset in rad/s
	static const double dHomeSpeed2;
	//! Home acceleration in rad/sÂ²
	static const double dHomeAcceleration;
	//! Flag to set the begining of the homing
	bool bHoming;
	//! Speed in rad/s
	static const double dSpeed;
	//! Acceleration in rad/s2
	static const double dAcceleration;
	
public:

    //! public constructor
    MotorPosition(byte can_id, PCan *can_device, double hz): MotorDrive(can_id, can_device, hz){
		sComponentName.assign("MotorPosition");
        iMotorCounts = 0;
        modModeOfOperation = POSITION_MODE;
		// TODO - CHECK CONVERSIONS - ARE NOT EQUAL FOR THE GEARBOX
        dPos2Ref = (COUNTS_PER_REV_POS * K_GEARBOX) / SPINDLE_STEP_MM;  // total counts per mm
        dRef2Pos = 1.0 / dPos2Ref;
		dScalingFactorDS4 = pow(2.0, 17.0)/20000;
		dScalingFactorDA1 = pow(2.0, 34.0)/pow(20000.0,2.0);
		bHoming = false;
		iHomeOffset  = HOME_OFFSET;			// counts
		}

    //! public destructor
    ~MotorPosition(void);
    //! function to get the motor position in rads
    double GetMotorPosition();
    //! function to get the motor position counts
    int GetMotorCounts();
    //! function to set motor's position
    //! @param position as a int, target position
    //! @return OK
    //! @return ERROR
    ReturnValue SetMotorPosition(int position);
    //! function to set motor's position
    //! @param position as a double, target position in rads
    //! @return OK
    //! @return ERROR
    ReturnValue SetMotorPosition(double position);
    //! Returns if homing has been completed or not
    bool HomingComplete();
	//! Sets the drive into position mode
    ReturnValue SwitchToPositionMode();
    //! Starts home's procedure
    ReturnValue Home();
	//! Returns true if the driver is homing
	bool IsHoming();
	//! Changes the value of the offset
	void SetOffset(int value);
	
private:
    //! Reset and initialize the status of the drive
    //! @return OK
    //! @return ERROR
    ReturnValue Initialize();
    //! Actions performed on ready state
    void ReadyState();
};

#endif

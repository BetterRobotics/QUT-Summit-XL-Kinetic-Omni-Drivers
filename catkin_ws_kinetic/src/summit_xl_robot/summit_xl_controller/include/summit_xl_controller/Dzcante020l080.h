/*! \class dzcante020l080
 *  \file dzcante020l080.h
 *	\author Robotnik Automation S.L.L
 *	\version 1.0
 *	\date 2012
 *  \brief Class to manage the communication with the driver dzcante-020l080 via CANOpen
 * (C) 2012 Robotnik Automation, SLL
 *  All rights reserved.
 */

#ifndef __DZCANTE020l080_H
	#define __DZCANTE020l080_H

#include "summit_xl_controller/PCan.h"

#define DZCANTE_DIG_OUTPUTS     4
#define DZCANTE_DIG_INPUTS      8
#define DZCANTE_ANAG_INPUTS     3

//! Class Dzcante020l080
class Dzcante020l080: public Component{
    public:
    //! Internal drive status
    enum DriveStatus{
        UNKNOWN,
        SWITCH_ON_DISABLED,
        READY_TO_SWITCH_ON,
        OPERATION_DISABLED,
        OPERATION_ENABLED,
        FAULT,
        UNDER_VOLTAGE,
        QUICK_STOP
    };
    //! Types of CAN messages
    enum CANMessage{
        ENABLE_OP_MSG,
        RESET_MSG,
        SHUTDOWN_MSG,
        DIGITAL_OUTPUTS_MSG,
        DIGITAL_INPUTS_MSG,
        ANALOG_INPUTS_MSG,
        SWITCH_ON_MSG,
        DISABLE_VOLT_MSG,
        NODEGUARD_MSG,
        POSITION_SDO_MSG,
        POSITION_PDO_MSG,
        VELOCITY_SDO_MSG,
        VELOCITY_PDO_MSG,
        SYNC_MSG,
		START_COMM_MSG,
        RESET_COMM_MSG,
        RESET_NODE_MSG,
		STOP_COMM_MSG,
		PREOPERATIONAL_COMM_MSG,
		MODE_OF_OPERATION_MSG,
        HOME_OFFSET_MSG,
        HOME_METHOD_MSG,
        HOME_SPEED1_MSG,
        HOME_SPEED2_MSG,
        START_HOME_MSG,
        STOP_HOME_MSG,
        CONTROL_WORD_MSG,
        QUICK_STOP_MSG,
		CONF_RPDO1_1_MSG,
		CONF_RPDO1_2_MSG,
		CONF_RPDO21_1_MSG,
		CONF_RPDO21_2_MSG,
		CONF_RPDO22_1_MSG,
		CONF_RPDO22_2_MSG,
		CONF_TPDO1_1_MSG,
		CONF_TPDO1_2_MSG,
		CONF_TPDO3_1_MSG,
		CONF_TPDO3_2_MSG,
		CONF_TPDO4_1_MSG,
		CONF_TPDO4_2_MSG,
		CONF_TPDO21_1_MSG,
		CONF_TPDO21_2_MSG,
		CONF_TPDO22_1_MSG,
		CONF_TPDO22_2_MSG,
		DRIVE_STATUS_MSG,
		GUARD_TIME_MSG,
		LIFE_TIME_FACTOR_MSG,
		EVENT_ACTION_MSG,
		EVENT_RECOVERY_TIME_MSG,
		HEARTBEAT_CONSUMER_MSG,
		HEARTBEAT_MSG,
		ACTUAL_CURRENT_SDO_MSG,
		DC_BUS_SDO_MSG,
		ACTUAL_POSITION_SDO_MSG,
		DIGITAL_OUTPUT_UB1,
		DIGITAL_OUTPUT_UB2,
		DIGITAL_OUTPUT_UB3,
		CONF_SDO_PEAK_CURRENT_LIMIT_MSG
	};
    //! Status word indicators
    enum StatusWordIndicator{
        SW_READY_TO_SWITCH_ON = 0,
        SW_SWITCHED_ON	= 1,
        SW_OP_ENABLED = 2,
        SW_FAULT = 3,
        SW_VOLTAGE_ENABLED = 4,
        SW_QUICK_STOP = 5,
        SW_SWITCH_ON_DISABLED = 6,
        SW_WARNING = 7,
        SW_DELAY = 8,
		SW_TARGET_REACHED =	10,
        SW_HOME_ATTAINED = 12,
        SW_HOMING_ERROR = 13,
        SW_CAPTURE = 14
    };
    //! Modes of operation of the driver
    enum ModeOfOperation{
        POSITION_MODE =	0x01,
        POSITION_MODE2 = 0xA8,
        VELOCITY_MODE = 0x03,
        VELOCITY_MODE2 = 0x98,
        HOME_MODE = 0x06,
        HOME_MODE2	= 0x9F,
		CURRENT_MODE = 0x04,
		CUSTOM_MODE = 0xFF,
		PVT_MODE = 0x07
    };
    //! Homing methods
    enum HomingMethod{
		HOME_METHOD_NEGATIVE = 0x01,
        HOME_METHOD_POSITIVE = 0x02
    };
	enum PDOTransmissionType{
		SYNC_ACYCLIC = 0,
		SYCN_RTR = 0xFC,
		ASYNC_RTR = 0xFD,
		ASYNC = 0xFE
	};
	// Possible event actions when an error is produced
	enum EventActionValues{
		EVENT_NO_ACTION = 0,
		EVENT_DISABLE_POWER = 0x01,
		EVENT_DISABLE_POSITIVE = 0x02,
		EVENT_DISABLE_NEGATIVE = 0x03,
		EVENT_STOP = 0x07
		// There are more values ... (see event actions value definitions)
	};
	enum DriveStatusFlags{
		DS_NUMBER = 65,
		// DRIVE BRIDGE STATUS
		DS_BRIDGE_ENABLED = 0,
		DS_DYNAMIC_BRAKE_ENABLED = 1,
		DS_SHUNT_ENABLED = 2,
		DS_POSITIVE_STOP_ENABLED = 3,
		DS_NEGATIVE_STOP_ENABLED = 4, 
		DS_POSITIVE_TORQUE_INHIBIT_ACTIVE = 5,
		DS_NEGATIVE_TORQUE_INHIBIT_ACTIVE = 6,
		DS_EXTERNAL_BRAKE_ACTIVE = 7,
		// DRIVE PROTECTION STATUS
		DS_DRIVE_RESET = 8,
		DS_DRIVE_INTERNAL_ERROR = 9, 
		DS_SHORT_CIRCUIT = 10,
		DS_CURRENT_OVERSHOOT = 11,
		DS_UNDER_VOLTAGE = 12,
		DS_OVER_VOLTAGE = 13, 
		DS_DRIVER_OVER_TEMPERATURE = 14,
		// SYSTEM PROTECTION STATUS
		DS_PARAMETER_RESTORE_ERROR = 15,
		DS_PARAMETER_STORE_ERROR = 16,
		DS_INVALID_HALL_STATE = 17,
		DS_PHASE_SYNC_ERROR = 18,
		DS_MOTOR_OVER_TEMPERATURE = 19,
		DS_PHASE_DETECTION_FAULT = 20,
		DS_FEEDBACK_SENSOR_ERROR = 21,
		DS_MOTOR_OVER_SPEED = 22,
		DS_MAX_MEASURED_POSITION = 23,
		DS_MIN_MEASURED_POSITION = 24,
		DS_COMMUNICATION_ERROR = 25,
		// DRIVE SYSTEM STATUS 1
		DS_LOG_ENTRY_MISSED = 26,
		DS_COMMANDED_DISABLE = 27,
		DS_USER_DISABLE = 28,
		DS_POSITIVE_INHIBIT = 29,
		DS_NEGATIVE_INHIBIT = 30,
		DS_CURRENT_LIMITING = 31,
		DS_CONTINUOUS_CURRENT = 32,
		DS_CURRENT_LOOP_SATURED = 33,
		DS_USER_UNDER_VOLTAGE = 34,
		DS_USER_OVER_VOLTAGE = 35, 
		DS_NONSINUSOIDAL_COMMUTATION = 36,
		DS_PHASE_DETECTION = 37,
		DS_USER_AUXILIARY_DISABLE = 38,
		DS_SHUNT_REGULATOR = 39,
		DS_PHASE_DETECTION_COMPLETE = 40,
		// DRIVE SYSTEM STATUS 2
		DS_ZERO_VELOCITY = 41,
		DS_AT_COMMAND = 42,
		DS_VELOCITY_FOLLOWING_ERROR = 43,
		DS_POSITIVE_TARGET_VELOCITY_LIMIT = 44,
		DS_NEGATIVE_TARGET_VELOCITY_LIMIT = 45,
		DS_COMMAND_LIMITER_ACTIVE = 46,
		DS_IN_HOME_POSITION = 47,
		DS_POSITON_FOLLOWING_ERROR = 48,
		DS_MAX_TARGET_POSITION_LIMIT = 49,
		DS_MIN_TARGET_POSITION_LIMIT = 50,
		DS_LOAD_MEASURED_POSITION = 51,
		DS_LOAD_TARGET = 52,
		DS_HOMING_ACTIVE = 53,
		DS_HOMING_COMPLETE = 54,
		// DRIVE SYSTEM STATUS 3
		DS_PVT_BUFFER_FULL = 55,
		DS_PVT_BUFFER_EMPTY = 56,
		DS_PVT_BUFFER_THRESHOLD = 57, 
		DS_PVT_BUFFER_FAILURE = 58, 
		DS_PVT_BUFFER_EMPTY_STOP = 59,
		DS_PVT_BUFFER_SEQUENCE_ERROR = 60,
		DS_COMMANDED_STOP = 61,
		DS_USER_QUICKSTOP = 62,
		DS_COMMANDED_POSITIVE_LIMIT = 63,
		DS_COMMANDED_NEGATIVE_LIMIT = 64
	};
    protected:
    //! Direction of used RPDO messages
    static const int RPDO1, RPDO21, RPDO22;
    //! MSB of the direction of used RPDO messages
    static const int RPDO1_MSB, RPDO21_MSB, RPDO22_MSB;
    //! Direction of used TPDO messages
    static const int TPDO1, TPDO3, TPDO4, TPDO21, TPDO22, TPDO25, TPDO26;
    //! MSB of the direction of used TPDO messages
    static const int TPDO1_MSB, TPDO3_MSB, TPDO4_MSB, TPDO21_MSB, TPDO22_MSB, TPDO25_MSB, TPDO26_MSB;

    //! CAN device
    PCan *canDev;

    public:
    //! public constructor
    Dzcante020l080(PCan *can_device);
    //! public constructor
    ~Dzcante020l080();
    //! Checks if the can device is initialized
    //! @return OK
    //! @return ERROR
    virtual ReturnValue Setup();
    //! Sends a CAN message
    virtual ReturnValue Send(byte can_id, CANMessage type, AccessMode mode, int param);  // byte can_id

};

#endif


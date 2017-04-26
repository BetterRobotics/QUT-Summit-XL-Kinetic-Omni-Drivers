/*! \class MotorDrive
 *  \file MotorDrive.h
 *	\author Robotnik Automation S.L.L
 *	\version 3.0
 *	\date 2012
 *  \brief Class to manage the driver DPCANTE of AMC
 *
 * (C) 2010 Robotnik Automation, SLL
 *  All rights reserved.
 */

#ifndef __MOTORDRIVE_H
	#define __MOTORDRIVE_H

#include "summit_xl_controller/Dzcante020l080.h"

// #define TRAC_GEAR                    12.5                            // traction gearbox 1:12.52  - 24VDC Robotnik Hub
// #define MOTOR_WHEEL_DIAMETER		0.219		                // motorwheel diameter 0.250 minus foam_deformation [M]
// #define PPS_REV_VEL			58.0				// pulses per revolution
#define TRAC_GEAR                       9.56                            // traction gearbox 1:9.56   - 48VDC Robotnik Hub
#define MOTOR_WHEEL_DIAMETER            0.237                           // mecanum wheel 0.254 minus rubber deformation and slippage
#define PPS_REV_VEL                     48 
#define QUAD_VEL			1.0				// Encoder's quadrature
#define COUNTS_PER_REV_VEL	PPS_REV_VEL * QUAD_VEL 		// Encoder counts per revolution

#define PPS_REV_POS			4000.0				// pulses per revolution position axis
#define QUAD_POS			1.0				    // Encoder's quadrature
#define COUNTS_PER_REV_POS	PPS_REV_POS * QUAD_POS 		// Encoder counts per revolution

#define MOTOR_PI 			3.14159265358979323846
#define REV_TO_METER			MOTOR_WHEEL_DIAMETER* MOTOR_PI 	// 1 rev -> x meters ( Diameter * Pi)
#define METER_TO_REV			1.0 / REV_TO_METER		// Constant to convert meters into revolutions
#define SPEED_SCALE_FACTOR		6.5536				// Driver scale factor
#define NODEGUARD_TIME			100				// Time (ms) to control the communication with the driver
#define NODEGUARD_FACTOR		5				// factor to mult
#define HEARTBEAT_TIMER			2000				// milliseconds
#define EVENT_RECOVERY_TIME		1000				// milliseconds
#define BATTERY_ANALOG_INPUT	1			                // Analog input used to measure the battery

#define NMT_TIMEOUT	2	// Max timeout (seconds) on the communication with the drivers

enum {
	DRIVE_STATUS_TIMER = 3000000					// uSecs. Timer to generate an alarm when a drive status flag is active
};

//! Main function to execute into test secondary thread
void *AuxMotorDriveControlCommunicationThread(void *threadParam);
//! Main function to execute into the third thread
void *AuxMotorDriveReadSDOMessagesThread(void *threadParam);

//! Class MotorDrive
class MotorDrive: public Dzcante020l080{
    friend void *AuxMotorDriveControlCommunicationThread(void *threadParam);
	friend void *AuxMotorDriveReadSDOMessagesThread(void *threadParam);

public:
    //! Struct to store the value of digital inputs / outputs
    typedef struct Digital{
        //! Value for a maximum of 32 I/O
        unsigned int uiValue;
        //! Value of I/O using a vector
        bool bValue[32];
    }Digital;

protected:
    //! Can identifier
    byte CanId;
    //! Digital Inputs
    Digital digitalInputs;
    //! Digital Outputs (Desired value and read value from device)
    Digital digitalOutputs, digitalRealOutputs;
    //! Number of digital outputs
    static const unsigned int uiNumOfDigOut;
    //! Number of digital inputs
    static const unsigned int uiNumOfDigIn;
    //! Number of analog inputs
    static const unsigned int uiNumOfAnagIn;
    //! CAN communication status
    CommunicationStatus commStatus;
    //! Contains the values of the analog inputs
    double dAnalogInputs[DZCANTE_ANAG_INPUTS];
    //! Time of the last NodeGuard reply from the drive
    struct timespec tNodeGuardReply;
    //! Internal status of the drive
    DriveStatus dsStatus;
    //! Internal desired status of the drive
    DriveStatus dsDesiredStatus;
    //! Temperature of the drive
    double dTemperature;
    //! Status' flags of the drive
    bool bStatusWord[16];
    //! Drive Status flags (provided by CAN object 0x2002h)
    int16_t iDriveStatus[6];
    //! Manufacturer register status' flags of the drive. Flag for all the drive status bit provided by CAN 0x2002h object
    bool bStatusRegister[DS_NUMBER], bLastStatusRegister[DS_NUMBER];
	//! Vector to control the duration of an active flag to avoid too many logs
	struct timespec tStatusRegisterTimer[DS_NUMBER];
    //! Mascara con los flags que hay que controlar de forma peridica
    bool bStatusRegisterMask[DS_NUMBER];
    //! Flag para la lectura del registro de estado del driver
    bool bRegisterError;
    //! Flag to force the reset of the driver
    bool bForceReset;
    //! Delay between consecutive CAN transmissions (nanoseconds)
    static const unsigned int uiDelayTrans;
    //! Mode of operation of the drive
    ModeOfOperation modModeOfOperation;
    //! Velocity of the motor
    int32_t iVelocityRef;
    //! Position of the motor
    int32_t iPositionRef;
    //! Set when the homing method has been correctly executed
    bool bHomingComplete;
	//! Timer to control the transitions of internal drive state
	struct timespec tControlWord;
	//! Flags to read the analog inputs
	bool bAnalogEnable[DZCANTE_ANAG_INPUTS];
	//! Enables/disables log of the Drive Status
	bool bLogDriveStatus;
	//! Value of the instant consumed current, and the average (every second)
	double dInstantCurrent, dAverageCurrent;
	//! Value of the instant battery value, and the average (every second)
	double dInstantBattery, dAverageBattery;
    //! Value of the DC Bus Voltage
    double dDCBusVoltage; 
    //! First Cicle
    bool bFirstCicle;
    //! Emergency Stop Push/Release to Reset
    bool bEmergencyStopToReset;
    
public:
    //! public constructor
    MotorDrive(byte can_id, PCan *can_device, double hz);
    //! public constructor
    ~MotorDrive();
    //! Setups the component
    //! @return OK
    //! @return ERROR
    virtual ReturnValue Setup();
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
	//! Gets the communication status
	CommunicationStatus GetCommunicationStatus();
	//! Gets the communication status like a string
	char *GetCommunicationStatusString();
	//! Puts CAN communication in Operational state
	//! @return OK
	//! @return ERROR
	ReturnValue StartCANCommunication();
	//! Resets the communication control state machine
	//! @return OK
	//! @return ERROR
	ReturnValue ResetCANCommunication();
	//! Stops the communication control state machine to STOPPED state
	//! @return OK
	//! @return ERROR
	ReturnValue StopCANCommunication();
	//! Resets the CAN node and its configuration
	//! @return OK
	//! @return ERROR
	ReturnValue ResetNode();
	//! Change the communication control state machine to PRE-OPERATIONAL state
	//! @return OK
	//! @return ERROR
	ReturnValue PreoperationalCANCommunication();
	//! Process received CAN messages
	//! @param msg as a TPCANMsg, the message to process
	void ProcessCANMessage(TPCANMsg msg);

    //! Function to get the status of the drive
    //! @return the status of the motor drive
    DriveStatus GetStatus();
    //! Function to get the status of the drive
    //! @return the status of the motor drive
    char *GetStatusString();
    //! Gets drive's mode of operation
    ModeOfOperation GetModeOfOperation();
    //! Returns the value of the internal status word as a string
    char *GetStatusWordString();
    //! Returns the value of the internal status word as a string
    char *GetStatusRegisterFlagsString();    
    //! Sets the desired status of the driver
    void SetDesiredStatus(DriveStatus new_status);

    //! Function to get the value of all digital inputs
	//! @return drive's digital inputs as an unsigned integer
	//! @return ERROR
	unsigned int GetDigitalInputs ();
	//! function for getting the selected digital input value
	//! @return true
	//! @return false
	bool GetDigitalInput(unsigned int input);
	//! Function to get the selected analog input value
	double GetAnalogInput(unsigned int input);
	//! Function to set the value of the digital outputs
	//! @param Outputs as unsigned int, value of the digital outputs
	//! @return OK
	//! @return ERROR
	ReturnValue SetDigitalOutputs(unsigned int output);
	//! Function to set drive's digital outputs
	//! @param index as int, number of the digital output
	//! @param value as bool, value of the digital output
	//! @return OK
	//! @return ERROR
	ReturnValue SetDigitalOutputs (unsigned int index, bool value);
	//! Function to get the values of the digital outputs
	//! @return drive's digital outputs
	unsigned int GetDigitalOutputs();
	//! Function for getting the selected digital output value
	//! @return true
	//! @return false
	bool GetDigitalOutput(unsigned int output);
	//! Function to send SYNC message by the CAN network
	ReturnValue Syncronize();
	//! Gets the value of internal drive status object
	int16_t GetDriveStatus(int object);
	//! Prints / Logs the value of every Drive Status flag
	void PrintDriveStatusRegister();
	//!	Returns the string value of the selected flag
	const char *GetStatusRegisterString(DriveStatusFlags flag);
	//! Enables / disables the log of DriveStatus object
	void SetLogDriveStatus(bool value);
	//! Gets the CAN ID
	byte GetCanId();
	//! Gets the consumed current
	double GetCurrent();
	//! Gets the average of battery level
	double GetBattery();
        //! Gets the voltage in the power bus
        double GetDCBusVoltage();
	//! Sets peak current limit
	ReturnValue SetPeakCurrentLimit(float current);


protected:
	//! Configures devices and performance of the component
	//! @return OK
    //! @return ERROR, if the configuration process fails
    ReturnValue Configure();
	//! Configures CAN TPDOs and RPDOs
	//! @return OK
    //! @return ERROR, if the configuration process fails
    ReturnValue ConfigureCANMsgs();
	//! Actions performed on initial state
	virtual void InitState();
	//! Actions performed on ready state
	virtual void ReadyState();
	//! Actions performed on restart state	
	virtual void RestartState();
	
	//! Actions performed on the emergency state
	virtual void EmergencyState();
	//! Actions performed in all states
	virtual void AllState();
	//! Change the value of the communication status
	void SwitchToCommunicationStatus(CommunicationStatus new_status);
	//! Change the value of the communication status
	void SwitchToStatus(DriveStatus new_status);
	//! Process received CAN TPDO1 messages (Default COB-ID= 0x180 + node id).
	//! @param msg as a TPCANMsg, the message to process
	void ProcessTPDO1Msg(TPCANMsg msg);
	//! Process received CAN TPDO22 messages (Default COB-ID= 0x280 + node id).
    //! This type of message contains the following data from Motor Drive:
    //! Velocity Actual Value (4 bytes)
    //! @param msg as a TPCANMsg, the message to process
    void ProcessTPDO22Msg(TPCANMsg msg);
	//! Process received CAN TPDO21 messages (Default COB-ID= 0x280 + node id).
    //! This type of message contains the following data from Motor Drive:
    //! Position Actual Value (4 bytes)
    //! @param msg as a TPCANMsg, the message to process
    void ProcessTPDO21Msg(TPCANMsg msg);
	//! Process the value of the digital inputs received from the drive
	void ProcessDigitalInputs(TPCANMsg msg);
	//! Process the value of the digital Outputs received from the drive
	void ProcessDigitalOutputs(TPCANMsg msg);
	//! Process the value of the analog inputs received from the drive
	void ProcessAnalogInputs(TPCANMsg msg);
	//! Process the mode of operation message read from the drive
	void ProcessModeOfOperation(TPCANMsg msg);
	//! Process the status_word value received from the drive and changes the status of the object
    //! @param status_word as a byte, with the current drive internal status
	void ProcessStatusWord(TPCANMsg msg);
	//! Process received CAN SDO message (Default COB-ID= 0x60ff).
    //! This type of message contains the following data from Motor Drive:
    //! Velocity Actual Value (4 bytes)
    //! @param msg as a TPCANMsg, the message to process
    void ProcessVelocityValue(TPCANMsg msg);
    //! Process received CAN SDO message (Default COB-ID= 0x607A).
    //! This type of message contains the following data from Motor Drive:
    //! Position Actual Value (4 bytes)
    //! @param msg as a TPCANMsg, the message to process
    void ProcessPositionValue(TPCANMsg msg);
    //! Process received CAN SDO message (COB-ID = 0x200F.01)
    //! Contains - DC BUS Voltage (4 bytes) in DV1 units
    //! @param msg as a TPCANMsg, the message to process
    void ProcessDCBusVoltage(TPCANMsg msg);
	//! Process received CAN SDO message (Default COB-ID= 0x2002).
    //! This type of message contains the following data from Motor Drive:
    //! Drive Status Message
    //! @param msg as a TPCANMsg, the message to process
    void ProcessDriveStatus(TPCANMsg msg);
	//! Actions to control the communication state with the drive
    void ControlCommunicationThread();
    //! Sleeps for a moment
	void Delay();
	void Delay(unsigned int value);
	//! Reset and initialize the status of the drive
    //! @return OK
    //! @return ERROR
    virtual ReturnValue Initialize();
	//! Reads SDO messages from the device
	void ReadSDOMessagesThread();
	//! Configures RPDO messages of the drive
	ReturnValue ConfigureRPDO(unsigned int rpdo_num);
	//! Configures TPDO messages
	ReturnValue ConfigureTPDO(unsigned int tpdo_num, byte sync_cycles, bool enable);
	//! Configures timer for nodeguard
	ReturnValue ConfigureNodeGuardTimer();
	//! Process the current consumed by the motors
	void ProcessCurrent(TPCANMsg msg);
    //! Initializes the status register mask
    void InitStatusRegister();
};

#endif

/*! \class MotorDrive
 *  \file MotorDrive.cc
 *	\author Robotnik Automation S.L.L
 *	\version 1.0
 *	\date 2010
 *  \brief Class to manage the state of the inputs and outputs of a module I/O
 *
 * (C) 2010 Robotnik Automation, SLL
 *  All rights reserved.
 */

#include "summit_xl_controller/MotorDrive.h"
#include <math.h>

// Number of digital inputs
const unsigned int MotorDrive::uiNumOfDigIn = DZCANTE_DIG_INPUTS;
// Number of digital outputs
const unsigned int MotorDrive::uiNumOfDigOut = DZCANTE_DIG_OUTPUTS;
// Time
const unsigned int MotorDrive::uiDelayTrans = 1000000;  // nanoseconds
// Number of analgo inputs
const unsigned int MotorDrive::uiNumOfAnagIn = DZCANTE_ANAG_INPUTS;

/*! \fn void *AuxControlCommunicationThread(void *threadParam)
 * \param threadParam as void *, parameters of thread
 * Function executing in the thread
*/
void *AuxMotorDriveControlCommunicationThread(void *threadParam){
    MotorDrive *ComponentThread = (MotorDrive *)threadParam;
	ComponentThread->ControlCommunicationThread();

	pthread_detach(pthread_self());
	return NULL;
}

/*! \fn void *AuxReadSDOMessagesThread(void *threadParam)
 * \param threadParam as void *, parameters of thread
 * Function executing in the thread
*/
void *AuxMotorDriveReadSDOMessagesThread(void *threadParam){
    MotorDrive *ComponentThread = (MotorDrive *)threadParam;
	ComponentThread->ReadSDOMessagesThread();

	pthread_detach(pthread_self());
	return NULL;
}

/*! \fn MotorDrive::MotorDrive(byte CanId, ESDCan *can_device, double desired_hz)
 * Constructor
*/
MotorDrive::MotorDrive(byte can_id, PCan *can_device, double desired_hz):Dzcante020l080(can_device){
    // Change the name to the name of the derived class
    sComponentName.assign("MotorDrive");
    CanId = can_id;
    bHomingComplete = false;
    threadData.dDesiredHz = desired_hz;     // attribute of Component class
    commStatus = (CommunicationStatus)UNKNOWN;
    dsStatus = UNKNOWN;
    dsDesiredStatus = OPERATION_ENABLED;
    bForceReset = false;
    iVelocityRef = iPositionRef = 0;
//    bLogDriveStatus = false;
    bLogDriveStatus = true;

    // Inits Inputs and Outputs
    digitalInputs.uiValue = digitalOutputs.uiValue = digitalRealOutputs.uiValue = 0;
    dInstantBattery = dInstantCurrent = dAverageBattery = dAverageCurrent = 0.0;
    dDCBusVoltage= 0.0;

    for(int i = 0; i < 32; i++)
        digitalInputs.bValue[i] = digitalOutputs.bValue[i] = digitalRealOutputs.bValue[i] = false;

    // Inits flags
    for(int i = 0; i < 16; i++)
	bStatusWord[i] = false;
    // Inits analog inputs
    for(int i = 0; i < (int) uiNumOfAnagIn; i++){
        dAnalogInputs[i] = 0.0;
    	}

    // Inits drive staus
    for(int i = 0; i < 6; i++){
        iDriveStatus[i] = 0;
        }
    // Inits flag for analog inputs
    for(int i = 0; i < DZCANTE_ANAG_INPUTS; i++){
	bAnalogEnable[i] = false;
	}
    // Inits the mask of critical flags and timers
    InitStatusRegister();
    bFirstCicle=true;
    bEmergencyStopToReset=false;
}

/*! \fn MotorDrive::~MotorDrive()
 * Destructor
*/
MotorDrive::~MotorDrive(){

}

/*! \fn ReturnValue MotorDrive::Setup()
 * Configures and initializes the component
 * \return OK
 * \return INITIALIZED if the component is already intialized
 * \return ERROR
*/
ReturnValue MotorDrive::Setup(){

	// Checks if has been initialized
	if(bInitialized){
		ROS_ERROR("%s::Setup: Already initialized",sComponentName.c_str());
		return INITIALIZED;
	}

	if(Dzcante020l080::Setup() == ERROR){
         	ROS_ERROR("%s::Setup: Error in setup",sComponentName.c_str());
		return ERROR;
    	}

	// Configure the component
	if(Configure() != OK){
		ROS_ERROR("%s::Setup: Error in Configure",sComponentName.c_str());
		return ERROR;
	}

	bInitialized = true;
	bHomingComplete = false;

	return OK;
}

/*! \fn ReturnValue MotorDrive::Configure()
 * Configures devices and performance of the component
 * \return OK
 * \return ERROR
*/
ReturnValue MotorDrive::Configure(){
    if(bForceReset){
	if(ResetNode() == ERROR) {
		ROS_ERROR("%s::Configure: Node %d: Error reseting the node", sComponentName.c_str(), CanId);
		return ERROR;
		}
		sleep(4);
	}

	if(ResetCANCommunication() == ERROR) {
		ROS_ERROR("%s::Configure: Node %d: Error reseting CAN communication", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();
	if(PreoperationalCANCommunication() == ERROR) {
		ROS_ERROR("%s::Configure: Node %d: Error preoperational CAN communication", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();
	if(ConfigureCANMsgs() != OK)	{
		ROS_ERROR("%s: Configure: Node %d: Error configuring CAN msgs", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();
	if(Initialize() != OK ){
		ROS_ERROR("%s::Configure: Node %d: Error Initializing the drive", sComponentName.c_str(), CanId);
		return ERROR;
	}

	if(StartCANCommunication() == ERROR)	{
		ROS_ERROR("%s::Configure: Node %d: Error starting communication control state machine", sComponentName.c_str(), CanId);
		return ERROR;
	}

	return OK;
}

/*! \fn ReturnValue MotorDrive::ConfigureCANMsgs()
 * Configures CAN TPDOs and RPDOs messages
 * \return OK
 * \return ERROR
*/
ReturnValue MotorDrive::ConfigureCANMsgs(){

	// Configures Node guards timer
	if(ConfigureNodeGuardTimer()!= OK){
		ROS_ERROR("%s::ConfigureCANMsgs: Node %d: Error configuring Node guard timer", sComponentName.c_str(), CanId);
		return ERROR;
	}

	if(ConfigureTPDO(1, 10, true) != OK){
		ROS_ERROR("%s::ConfigureCANMsgs: Node %d: Error configuring TPDO1", sComponentName.c_str(), CanId);
		return ERROR;
	}else{
		//ROS_INFO("%s::ConfigureCANMsgs: Node %d: configuring TPDO1", sComponentName.c_str(), CanId);
		Delay();
	}

	// Configure user bits (digital outputs)
	if(Send(CanId, DIGITAL_OUTPUT_UB1, WRITE, 0) != OK) {
		ROS_INFO("%s::ConfigureCANMsgs: Node %d: Error Configuring Digital Output Parameters - User Bit 1", sComponentName.c_str(), CanId);
		return ERROR;
	}else Delay();
	
	// Configure user bits (digital outputs)
	if(Send(CanId, DIGITAL_OUTPUT_UB2, WRITE, 0) != OK) {
		ROS_INFO("%s::ConfigureCANMsgs: Node %d: Error Configuring Digital Output Parameters - User Bit 2", sComponentName.c_str(), CanId);
		return ERROR;
	}else Delay();

	// Configure user bits (digital outputs)
	if(Send(CanId, DIGITAL_OUTPUT_UB3, WRITE, 0) != OK) {
		ROS_INFO("%s::ConfigureCANMsgs: Node %d: Error Configuring Digital Output Parameters - User Bit 3", sComponentName.c_str(), CanId);
		return ERROR;
	}else Delay();

	switch(modModeOfOperation){
		case POSITION_MODE:
		case POSITION_MODE2:
			ROS_INFO("%s::ConfigureCANMsgs: Node %d: Position ", sComponentName.c_str(), CanId);
			if(ConfigureRPDO(21) != OK){
				ROS_ERROR("%s::ConfigureCANMsgs: Node %d: Error configuring RPDO21", sComponentName.c_str(), CanId);
				return ERROR;
			}else{
				//ROS_INFO("%s::ConfigureCANMsgs: Node %d: configuring RPDO21", sComponentName.c_str(), CanId);
				Delay();
			}
			if(ConfigureTPDO(21, 1, true) != OK){
				ROS_ERROR("%s::ConfigureCANMsgs: Node %d: Error configuring TPDO21", sComponentName.c_str(), CanId);
				return ERROR;
			}else{
				//ROS_INFO("%s::ConfigureCANMsgs: Node %d: configuring TPDO21", sComponentName.c_str(), CanId);
				Delay();
				return OK;
			}
		break;
		case VELOCITY_MODE:
		case VELOCITY_MODE2:
			ROS_INFO("%s::ConfigureCANMsgs: Node %d: Velocity ", sComponentName.c_str(), CanId);
			if(ConfigureRPDO(22) != OK){
				ROS_INFO("%s::ConfigureCANMsgs: Node %d: Error configuring RPDO22", sComponentName.c_str(), CanId);
				return ERROR;
			}else{
				//ROS_INFO("%s::ConfigureCANMsgs: Node %d: configuring RPDO22", sComponentName.c_str(), CanId);
				Delay();
			}
			if(ConfigureTPDO(22, 1, true) != OK){
				ROS_INFO("%s::ConfigureCANMsgs: Node %d: Error configuring TPDO22", sComponentName.c_str(), CanId);
				return ERROR;
			}else{
				//ROS_INFO("%s::ConfigureCANMsgs: Node %d: configuring TPDO22", sComponentName.c_str(), CanId);
				Delay();
			}
			if(Send(CanId, VELOCITY_SDO_MSG, WRITE, 0) != OK) {
				ROS_INFO("%s::ConfigureCANMsgs: Node %d: Error Setting velocity to 0", sComponentName.c_str(), CanId);
				return ERROR;
			}else {
				//ROS_INFO("%s::ConfigureCANMsgs: Node %d:Setting velocity to 0", sComponentName.c_str(), CanId);
				Delay();
				return OK;
			}

		break;
		case HOME_MODE:
		case HOME_MODE2:
		case CURRENT_MODE:
		case CUSTOM_MODE:
		case PVT_MODE:
		
		break;
	}
	return OK;
}

/*! \fn ReturnValue MotorDrive::ShutDown()
 * Closes and frees the reserved resources
 * \return OK
 * \return THREAD_RUNNING if the component is running
 * @return NOT_INITIALIZED if the component is not initialized
 * \return ERROR
*/
ReturnValue MotorDrive::ShutDown(){

	if(bRunning){
		ROS_INFO("%s::ShutDown: Impossible while thread running, first must be stopped",sComponentName.c_str());
		return THREAD_RUNNING;
	}
	if(!bInitialized){
		ROS_INFO("%s::ShutDown: Impossible because of it's not initialized", sComponentName.c_str());
		return NOT_INITIALIZED;
	}

	Send(CanId, SHUTDOWN_MSG, WRITE, 0);

	bInitialized = false;

	return OK;
}

/*! \fn CommunicationStatus MotorDrive::GetCommunicationStatus(){
 * 	\brief function to get the communication status of the device
 * 	\return Comm status of the of the component
*/
CommunicationStatus MotorDrive::GetCommunicationStatus(){
	return commStatus;
}

/*! \fn char *MotorDrive::GetCommunicationStatusString()
 * Get communication status like a string
*/
char *MotorDrive::GetCommunicationStatusString(){
	switch(commStatus){
		case PRE_OPERATIONAL:
			return (char *)"PRE_OPERATIONAL";
		break;
		case OPERATIONAL:
			return (char *)"OPERATIONAL    ";
		break;
		case STOPPED:
			return (char *)"STOPPED        ";
		break;
		case FAULT:
			return (char *)"FAULT          ";
		break;
		default:
			return (char *)"UNKNOWN        ";
		break;
	}
}

/*!	\fn void ChangeStatus(DriveStatus new_status)
 * 	\brief Change the value of the status
 * 	@param new_status as DriveStatus, new status value
*/
void MotorDrive::SwitchToStatus(DriveStatus new_status){

	if(new_status!= dsStatus){ //Only if it's different
		dsStatus = new_status;
		switch(new_status){
			case UNKNOWN:
				//ROS_INFO("%s::SwitchToStatus: Node %d: Drive status changed to UNKNOWN",sComponentName.c_str(), CanId);
				break;
			case SWITCH_ON_DISABLED:
				//ROS_INFO("%s::SwitchToStatus: Node %d: Drive status changed to SWITCH_ON_DISABLED",sComponentName.c_str(), CanId);
				break;
			case READY_TO_SWITCH_ON:
				//ROS_INFO("%s::SwitchToStatus: Node %d: Drive status changed to READY_TO_SWITCH_ON",sComponentName.c_str(), CanId);
				break;
			case OPERATION_ENABLED:
				//ROS_INFO("%s::SwitchToStatus: Node %d: Drive status changed to OPERATION_ENABLED",sComponentName.c_str(), CanId);
				break;
			case FAULT:
				//ROS_INFO("%s::SwitchToStatus: Node %d: Drive status changed to FAULT", sComponentName.c_str(), CanId);
				break;
			case OPERATION_DISABLED:
				//ROS_INFO("%s::SwitchToStatus: Node %d: Drive status changed to OPERATION_DISABLED",sComponentName.c_str(), CanId);
				break;
			case UNDER_VOLTAGE:
				//ROS_INFO("%s::SwitchToStatus: Node %d: Drive status changed to UNDER_VOLTAGE",sComponentName.c_str(), CanId);
				break;
			case QUICK_STOP:
				//ROS_INFO("%s::SwitchToStatus: Node %d: Drive status changed to QUICK_STOP",sComponentName.c_str(), CanId);
				break;
		}
	}
}

/*!	\fn void MotorDrive::SwitchToCommunicationStatus(CommunicationStatus new_status)
 * 	\brief Change the value of the communication status
 * 	\param new_status as CommunicationStatus, new communication status value
*/
void MotorDrive::SwitchToCommunicationStatus(CommunicationStatus new_status){

	if(new_status!= commStatus){ //Only if it's different
		commStatus = new_status;
		switch(new_status){
			case UNKNOWN:
				ROS_INFO("%s::ChangeCommunicationStatus: Node %d: comm status changed to UNKNOWN", sComponentName.c_str(), CanId);
				break;
			case STOPPED:
				ROS_INFO("%s::ChangeCommunicationStatus: Node %d: comm status changed to STOPPED", sComponentName.c_str(), CanId);
				break;
			case PRE_OPERATIONAL:
				ROS_INFO("%s::ChangeCommunicationStatus: Node %d: comm status changed to PRE_OPERATIONAL", sComponentName.c_str(), CanId);
				break;
			case OPERATIONAL:
				ROS_INFO("%s::ChangeCommunicationStatus: Node %d: comm status changed to OPERATIONAL", sComponentName.c_str(), CanId);
				break;
			case FAULT:
				ROS_INFO("%s::ChangeCommunicationStatus: Node %d: comm status changed to FAULT", sComponentName.c_str(), CanId);
				break;
			default:
				ROS_INFO("%s::ChangeCommunicationStatus: Node %d: comm status changed to ???????\n", sComponentName.c_str(), CanId);
			break;
		}
	}
}

/*!	\fn void MotorDrive::InitState()
 *	\brief Actions performed on initial state
*/
void MotorDrive::InitState(){
	// State transitions
	if(commStatus == (CommunicationStatus)FAULT) {
		//ROS_INFO("%s::InitState: Node %d: Fault To Emergency", sComponentName.c_str(), CanId);
		SwitchToState(EMERGENCY_STATE);		
	} else if(commStatus != OPERATIONAL) {
		//ROS_INFO("%s::InitState: Node %d: Start Communication", sComponentName.c_str(), CanId);
		StartCANCommunication();
	} else {
		//ROS_INFO("%s::InitState: Node %d: To Ready State", sComponentName.c_str(), CanId);
		SwitchToState(READY_STATE);
	}

	// Inits nodeguard reply timer
	clock_gettime(threadData.pthreadPar.clock, &tNodeGuardReply);
	tsnorm(&tNodeGuardReply);
	tControlWord = tNodeGuardReply;	// Control word communication timer
}

/*!	\fn void MotorDrive::ReadyState()
 *	\brief Actions performed on ready state
 *         MotorDrive will be ready while the communication with the device be OK
*/
void MotorDrive::ReadyState(){
	struct timespec tNow;
	long diff = 0;

        // State transitions
	if(commStatus == (CommunicationStatus)FAULT)
		SwitchToState(EMERGENCY_STATE);
	else if(commStatus != OPERATIONAL)
		SwitchToState(INIT_STATE);
		
	if (dsStatus==OPERATION_ENABLED) bFirstCicle=false;

	// Gets current time
	clock_gettime(threadData.pthreadPar.clock, &tNow);
	diff = calcdiff(tNow, tControlWord);

    	// Actions
	// Control State Machine: Manages the internal status transitions of the drive
	if((dsDesiredStatus != dsStatus) && (diff > 50000)){	
		//Only if the actual state is different of the desired state and after ainimum delay
		// Gets the time to the next control
		clock_gettime(threadData.pthreadPar.clock, &tControlWord);
		//ROS_INFO("Diff = %f", (float)diff/1000000);
		if(dsDesiredStatus == OPERATION_ENABLED){
			switch(dsStatus){
				case QUICK_STOP:

				case OPERATION_DISABLED:
					ROS_INFO("%s::ReadyState: Node %d: QuickStop or OpDisabled to Op Enabled", sComponentName.c_str(), CanId);
					Send(CanId, ENABLE_OP_MSG, WRITE, 0);
					//Delay();
				break;

				case READY_TO_SWITCH_ON:
					ROS_INFO("%s::ReadyState: Node %d: ReadyToSwitchOn to Op Enabled", sComponentName.c_str(), CanId);
					Send(CanId, SWITCH_ON_MSG, WRITE, 0);
					//Delay();
				break;

				case SWITCH_ON_DISABLED:
					ROS_INFO("%s::ReadyState: Node %d: SwitchOnDisabled to Op Enabled", sComponentName.c_str(), CanId);
					Send(CanId, SHUTDOWN_MSG, WRITE, 0);
					//Delay();
				break;

				case FAULT:
					//ROS_INFO("%s::ReadyState: Node %d: Fault to Op Enabled", sComponentName.c_str(), CanId);

					if(bStatusRegister[DS_CURRENT_OVERSHOOT]) {
				               ROS_INFO("Attempting to restart drive from DS_CUREENT_OVERSHOT");
				               Send(CanId, RESET_MSG, WRITE, 0);
				               Delay(0.25);
				               Send(CanId, SHUTDOWN_MSG, WRITE, 0);
				               Delay(0.25);
				               Send(CanId, ENABLE_OP_MSG, WRITE, 0);
				               Delay(0.25);
				               Send(CanId, SWITCH_ON_MSG, WRITE, 0);
				               Delay(0.1);
				               }
					else {
  						Send(CanId, ENABLE_OP_MSG, WRITE, 0);
						Delay(1);
						Send(CanId, SWITCH_ON_MSG, WRITE, 0);
						Delay(1);
					     }                                        
				break;
				default:
					ROS_INFO("%s::ReadyState: Node %d: Default to Op Enabled", sComponentName.c_str(), CanId);
					Send(CanId, ENABLE_OP_MSG, WRITE, 0);
					Delay();
				break;
			}
		}
		else if(dsDesiredStatus == QUICK_STOP){
			switch(dsStatus){
				case OPERATION_ENABLED:
					//ROS_INFO("%s::ReadyState: Node %d: Op Enabled to Quick Stop", sComponentName.c_str(), CanId);
					Send(CanId, QUICK_STOP_MSG, WRITE, 0);					
					//Delay();
				break;

				case OPERATION_DISABLED:
					//ROS_INFO("%s::ReadyState: Node %d: Op Disabled to Quick Stop", sComponentName.c_str(), CanId);
					Send(CanId, ENABLE_OP_MSG, WRITE, 0);
					//Delay();
				break;

				case READY_TO_SWITCH_ON:
					//ROS_INFO("%s::ReadyState: Node %d: Ready to Switch On to Quick Stop", sComponentName.c_str(), CanId);
					Send(CanId, SWITCH_ON_MSG, WRITE, 0);
					//Delay();
				break;

				case SWITCH_ON_DISABLED:
					//ROS_INFO("%s::ReadyState: Node %d: Switch On Disabled to Quick Stop", sComponentName.c_str(), CanId);
					Send(CanId, SHUTDOWN_MSG, WRITE, 0);
					//Delay();
				break;

				case FAULT:
					//ROS_INFO("%s::ReadyState: Node %d: Fault to Quick Stop", sComponentName.c_str(), CanId);
					//sleep(4);
					Send(CanId, RESET_MSG, WRITE, 0);
					Delay(1);
					Send(CanId, SHUTDOWN_MSG, WRITE, 0);
					Delay(1);
					Send(CanId, ENABLE_OP_MSG, WRITE, 0);
					Delay(1);
					Send(CanId, SWITCH_ON_MSG, WRITE, 0);
					Delay(1);
				break;
				default:
					//ROS_INFO("%s::ReadyState: Node %d: Unknown to Quick Stop", sComponentName.c_str(), CanId);
					Send(CanId, QUICK_STOP_MSG, WRITE, 0);
					//Delay();
				break;
			}
		} 
	} else if (dsStatus==FAULT){
		if	(commStatus == (CommunicationStatus)OPERATIONAL) {
			 //ROS_INFO("%s::ReadyState: Node %d: FAULT && OPERATIONAL", sComponentName.c_str(), CanId);  
			 //if (!bFirstCicle) SwitchToState( RESTART_STATE );
			 //bEmergencyStopToReset=false;		
		}
	}	
	
	// Check situations to force emergency stop Push/Release to restart
	
	for(int i = 0; i < DS_NUMBER; i++){
	    // If we detect some situations we will force user to press Emergency stop to restart
		if(bStatusRegister[i] && bStatusRegisterMask[i]){
			if(i == DS_CURRENT_LOOP_SATURED){
				// Not Used yet
				//ROS_INFO("%s::ReadyState: Node %d: Current Loop Satured Detected", sComponentName.c_str(), CanId);
				bEmergencyStopToReset=true;
				// Not Used by Now
				//SwitchToState( RESTART_STATE );
			}
		}
	}
	
	if (bEmergencyStopToReset) {
		//ROS_INFO("%s::ReadyState: Node %d: Push/Release Emergency Stop to Restart", sComponentName.c_str(), CanId);
	} 
}


/*!	\fn void MotorDrive::RestartState()
 *	\brief Actions performed on restart state
 *         MotorDrive will be completely restarted
*/
void MotorDrive::RestartState(){
	 
}

/*!	\fn void MotorDrive::EmergencyState()
 *	\brief Actions performed on emergency state
*/
void MotorDrive::EmergencyState(){
    static unsigned int count_cycles = 0;
    static unsigned int recover_cycles = 4*(unsigned int)threadData.dDesiredHz;
    // State transitions
    if(commStatus != (CommunicationStatus)FAULT) 
        SwitchToState(INIT_STATE);       
    else if(count_cycles == recover_cycles){    // Tries to recover the communication
        count_cycles = 0;
        ResetCANCommunication();
    } else
        count_cycles++;

}

/*!	\fn void MotorDrive::AllState()
 *	\brief Actions performed on all states
*/
void MotorDrive::AllState(){

}

/*!	\fn void MotorDrive::ProcessCANMessage(TPCANMsg msg)
 * \brief Process received CAN messages
 * \param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessCANMessage(TPCANMsg msg){
	unsigned int NMT_id = 0x700 + CanId;	// COB-id for NMT message response from drive
	unsigned int SDO_Response_id = 0x580 + CanId;
	unsigned int TPDO1_id = TPDO1 + CanId, TPDO21_id = TPDO21 + CanId, TPDO22_id = TPDO22 + CanId;


	if(msg.ID == NMT_id) { //node Guard message received
		// Saves the current time
		//ROS_INFO(" CanID:%d msg.DATA[0]=%d",CanId,msg.DATA[0]);
		clock_gettime(threadData.pthreadPar.clock, &tNodeGuardReply);
		tsnorm(&tNodeGuardReply);
		// DEBUG NODE_GUARD
		// if (CanId==7)  ROS_INFO("ProcessCANMsg 7 ");

		if((msg.DATA[0]== 0x04) || (msg.DATA[0] == 0x84)){ // Communication in STOPPED state
			SwitchToCommunicationStatus(STOPPED);
			return;
		}
		if((msg.DATA[0]== 0x05) || (msg.DATA[0] == 0x85)){ // Communication in OPERATIONAL state
			SwitchToCommunicationStatus(OPERATIONAL);
			return;
		}
		if((msg.DATA[0]== 0x7F) || (msg.DATA[0] == 0xFF)){ // Communication in PRE_OPERATIONAL state
			SwitchToCommunicationStatus(PRE_OPERATIONAL);
			return;
		}
	}
	//
	// PDO (Process Data Object) Messages
	// Status Word  1 and 2
	if(msg.ID == TPDO1_id){
		ProcessTPDO1Msg(msg);
		return;
	}
	//
	// Position Value
	if(msg.ID == TPDO21_id){
		ProcessTPDO21Msg(msg);
		//ROS_INFO("TPDO21");
		return;
	}
	//
	// Velocity value
	if( msg.ID == TPDO22_id ){ //  &&
		ProcessTPDO22Msg(msg);
		//ROS_INFO("TPDO22");
		return;
	}
	//
	// SDO (Service Data Objects) Messages
	if(msg.ID == SDO_Response_id){
		//ROS_INFO("SDO: %x%x ",msg.DATA[2],msg.DATA[1]);
	    // DIGITAL OUTPUTS
		if( (msg.DATA[1] == 0x24 && msg.DATA[2] == 0x22) ) { // Digital Outputs
			//Process Digital Outputs
			ProcessDigitalOutputs(msg);
			return;
		}
		// DIGITAL INPUTS
		if( (msg.DATA[1] == 0x23 && msg.DATA[2] == 0x20) ) { // Digital Inputs
			//Process Digital Inputs
			ProcessDigitalInputs(msg);
			return;
		}
		// ANALOG INPUTS
		if( (msg.DATA[1] == 0x1A && msg.DATA[2] == 0x20) ) { // Analog Inputs
			//Process Analog Inputs
			ProcessAnalogInputs(msg);
			return;
		}
		// MODE OF OPERATION
		if( (msg.DATA[1] == 0x60 && msg.DATA[2] == 0x60) || (msg.DATA[1] == 0x61 && msg.DATA[2] == 0x60) ) {
			//Process Mode Of Operation
			ProcessModeOfOperation(msg);
			return;
		}
		// SDO VELOCITY VALUE
		if( msg.DATA[1] == 0xff && msg.DATA[2] == 0x60 ) {
			//Process Velocity value
			ProcessVelocityValue(msg);
			return;
		}
		// SDO POSITION VALUE
		if( msg.DATA[1] == 0x7a && msg.DATA[2] == 0x60 ) {
			//Process Position value
			ProcessPositionValue(msg);
			return;
		}
		
		// SDO ACTUAL POSITION (6064h)
		if( msg.DATA[1] == 0x64 && msg.DATA[2] == 0x60 ) {
			//Process Position value
			ProcessPositionValue(msg);
			return;
		}
		
		// CONTROLWORD
		if( (msg.DATA[0] == 0x42) && (msg.DATA[1] == 0x41) && (msg.DATA[2] == 0x60) ) {
			//Process Control Word
			ProcessStatusWord(msg);
			return;
		}
		// DRIVE STATUS
		if( (msg.DATA[1] == 0x02) && (msg.DATA[2] == 0x20) ) {
			//Process Control Word
			ProcessDriveStatus(msg);
			return;
		}
		// MOTOR'S CURRENT
		if( (msg.DATA[1] == 0x77) && (msg.DATA[2] == 0x60) ) {
			//Process Motor current
			ProcessCurrent(msg);
			return;
		}
        // DC BUS VOLTAGE 
        if( (msg.DATA[1] == 0x0F) && (msg.DATA[2] == 0x20) ) {
			ProcessDCBusVoltage(msg);
			return;
		}
	}//else
	//	printf("Unknown message = %x vs %x\n", msg.id, TPDO22_id);
}

/*!	\fn ReturnValue MotorDrive::StartCANCommunication()
 * 	\brief Sends a message to put CAN communication in Operational state
 * 	\return OK
 *  \return ERROR
*/
ReturnValue MotorDrive::StartCANCommunication(){
	//ROS_INFO("%s::StartCANCommunication: starting com for node %d", sComponentName.c_str(), CanId);
    	return Send(CanId, START_COMM_MSG, WRITE, 0);
}

/*!	\fn ReturnValue MotorDrive::ResetCANCommunication()
 * 	\brief Sends a message to reset CAN communication
 * 	\return OK
 *  \return ERROR
*/
ReturnValue MotorDrive::ResetCANCommunication(){
	ROS_INFO("%s::ResetCANCommunication: Reseting com for node %d", sComponentName.c_str(), CanId);
        return Send(CanId, RESET_COMM_MSG, WRITE, 0);
}

/*!	\fn ReturnValue MotorDrive::ResetNode()
 * 	\brief Sends a message to reset the CAN node and its configuration
 * 	\return OK
 *  \return ERROR
*/
ReturnValue MotorDrive::ResetNode(){
	ROS_INFO("%s::ResetNode: reseting node %d", sComponentName.c_str(), CanId);
	return Send(CanId, RESET_NODE_MSG, WRITE, 0);
}

/*!	\fn ReturnValue MotorDrive::StopCANCommunication()
 * 	\brief Sends a message to stop CAN communication
 * 	\return OK
 *  \return ERROR
*/
ReturnValue MotorDrive::StopCANCommunication(){
    return Send(CanId, STOP_COMM_MSG, WRITE, 0);
}

/*!	\fn ReturnValue MotorDrive::PreoperationalCANCommunication()
 * 	\brief Sends a message to put the CAN comm into preoperational state
 * 	\return OK
 *  \return ERROR
*/
ReturnValue MotorDrive::PreoperationalCANCommunication(){
    return Send(CanId, PREOPERATIONAL_COMM_MSG, WRITE, 0);
}

/*!	\fn ReturnValue MotorDrive::Syncronize()
 * 	\brief Function to send SYNC message by the CAN network
 * 	\return OK
 *  \return ERROR
*/
ReturnValue MotorDrive::Syncronize(){
	return Send(CanId, SYNC_MSG, WRITE, 0);
}

/*!	\fn	 void MotorDrive::ProcessTPDO1Msg(TPCANMsg msg)
 * 	\brief Process received CAN TPDO1 messages (Default COB-ID= 0x180 + node id).
 * 	\brief This type of message contains the following data from Motor Drive:
 * 	\brief Status Word (first 4 bytes)
 * 	\param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessTPDO1Msg(TPCANMsg msg){
	int16_t aux_status = 0;
	int i, j;

	//Extract Status word
	aux_status = msg.DATA[1] << 8;
	aux_status |= msg.DATA[0];

	//ROS_INFO("%s::ProcessTPDO1Msg: Node %d:[%x %x] status = %x",sComponentName.c_str(), CanId, msg.DATA[1], msg.DATA[0], aux_status);

	for(i = 0x1, j=0; j < 15; j++, i=i*2){
		if((aux_status & i) > 0){
			bStatusWord[j]= true;
		}else
			bStatusWord[j]= false;
	}

	if(bStatusWord[SW_FAULT])
		SwitchToStatus(FAULT);
	else if(!bStatusWord[SW_VOLTAGE_ENABLED] && bStatusWord[SW_SWITCH_ON_DISABLED])
		SwitchToStatus(SWITCH_ON_DISABLED);
	else if(bStatusWord[SW_OP_ENABLED]){
		if(!bStatusWord[SW_QUICK_STOP])
			SwitchToStatus(QUICK_STOP);
		else
			SwitchToStatus(OPERATION_ENABLED);
	}
	else if( bStatusWord[SW_READY_TO_SWITCH_ON] && bStatusWord[SW_SWITCHED_ON] )
		SwitchToStatus(OPERATION_DISABLED);
	else if(bStatusWord[SW_READY_TO_SWITCH_ON])
		SwitchToStatus(READY_TO_SWITCH_ON);
	else
		SwitchToStatus(UNKNOWN);

	// Changet to ALLSTATE of MotorPosition
	if(bStatusWord[SW_HOME_ATTAINED] && !bHomingComplete){
	    	ROS_INFO("%s::ProcessTPDO1: HOMING COMPLETE!",sComponentName.c_str());
		//SwitchToPositionMode();
		bHomingComplete = true;
	}
}

/*! \fn void MotorDrive::ProcessTPDO21Msg(TPCANMsg msg)
 *  \brief Process received CAN TPDO21 messages
 *  \brief This type of message contains the following data from Motor Drive:
 *  \brief Position Actual Value (first 4 bytes)
 *  \param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessTPDO21Msg(TPCANMsg msg){
	int aux_position = 0;
	//Extract position value
	aux_position = (int) msg.DATA[3] * 16777216 + (int) msg.DATA[2] * 65536 + (int) msg.DATA[1] * 256 + (int) msg.DATA[0];
	iPositionRef = aux_position;
}

/*!	\fn	 void MotorDrive::ProcessTPDO22Msg(TPCANMsg msg)
 * 	\brief Process received CAN TPDO22 messages (Default COB-ID= 0x280 + node id).
 * 	\brief This type of message contains the following data from Motor Drive:
 *  \brief Velocity Actual Value ( 4 bytes)
 * 	\param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessTPDO22Msg(TPCANMsg msg){
    int32_t aux_velocity = 0;
    aux_velocity = (int) msg.DATA[3] * 16777216 + (int) msg.DATA[2] * 65536 + (int) msg.DATA[1] * 256 + (int) msg.DATA[0];

    iVelocityRef = aux_velocity;
}

/*! \fn void MotorDrive::ProcessVelocityValue(TPCANMsg msg)
 *  \brief Process received CAN SDO message (Default COB-ID= 0x60ff).
 *  \brief This type of message contains the following data from Motor Drive:
 *  \brief Velocity Actual Value (4 bytes)
 *  \param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessVelocityValue(TPCANMsg msg){
    int32_t aux_velocity = 0;

    aux_velocity = (int) msg.DATA[7] * 16777216 + (int) msg.DATA[6] * 65536 + (int) msg.DATA[5] * 256 + (int) msg.DATA[4];
    iVelocityRef = aux_velocity;
}

/*! \fn void MotorDrive::ProcessPositionValue(TPCANMsg msg)
 *  \brief Process received CAN SDO message (Default COB-ID= 0x607a).
 *  \brief This type of message contains the following data from Motor Drive:
 *  \brief Position Actual Value (4 bytes)
 *  \param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessPositionValue(TPCANMsg msg){
    int aux_position = 0;
    //Extract position value
    aux_position = (int) msg.DATA[7] * 16777216 + (int) msg.DATA[6] * 65536 + (int) msg.DATA[5] * 256 + (int) msg.DATA[4];
    iPositionRef = aux_position;
}

/*! \fn void MotorDrive::ProcessCurrent(TPCANMsg msg)
 *  \brief Process received CAN SDO message (Default COB-ID= 0x60f1).
 *  \brief This type of message contains the following data from Motor Drive:
 *  \brief Current Actual Value (4 bytes)
 *  \param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessCurrent(TPCANMsg msg){
    int16_t aux_current = 0;
    static double conversion = pow(2,13)/60;

    aux_current =  (int) msg.DATA[5] * 256 + (int) msg.DATA[4];

    dInstantCurrent = (double) aux_current / conversion;
	/*if(CanId == 1){
		ROS_INFO("MotorDrive %d: Current = %lf A" , CanId,  aux );
	}*/
}

/*! \fn void MotorDrive::ProcessDCBusVoltage(TPCANMsg msg)
 *  \brief Process received CAN SDO message (Default COB-ID= 0x200F.01).
 *  \brief This type of message contains the following data from Motor Drive:
 *  \brief DC BUS Voltage (4 bytes)
 *  \param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessDCBusVoltage(TPCANMsg msg){
    int32_t aux_bus_voltage = 0;
    double KOV = 88.0;
    // KOV The hardware defined, DC bus, over-voltage limit of the drive in volts. 
    // This value can be read from 20D8.09h.
    static double conversion = pow(2,14)/(1.05 * KOV);   

    aux_bus_voltage = (int) msg.DATA[7] * 16777216 + (int) msg.DATA[6] * 65536 + (int) msg.DATA[5] * 256 + (int) msg.DATA[4];
    dDCBusVoltage = (double) aux_bus_voltage / conversion;
    //if(CanId == 1){
        //ROS_INFO("MotorDrive::ProcessDCBusVoltage  %d: Voltage  = %lf [V]" , CanId,  dDCBusVoltage );
        //}
}

/*! \fn void MotorDrive::ProcessDriveStatus(TPCANMsg msg)
 *  \brief Process received CAN SDO message Drive Status (0x2002h)
 *  \brief This type of message contains the following data from Motor Drive:
 *  \brief Drive Status
 *  \param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessDriveStatus(TPCANMsg msg){
	int16_t aux = 0;
	aux = msg.DATA[5];
	aux = (aux<<8) | msg.DATA[4];
	int i = 0, j = 0;
	bool bPrintStatus = false; // Print status if it has changed
	struct timespec tNow; // current time
	long diff = 0;

        // Control flag alarm activation, in case active flag is not registered, reset the timer.
        // If it is active for a period longer than established in DRIVE_STATUS_TIMER, then activate the flag
	clock_gettime(threadData.pthreadPar.clock, &tNow);
	// Depending of the subindex
	if(msg.DATA[3] > 0 && msg.DATA[3] <= 6){
		iDriveStatus[msg.DATA[3] - 1] = aux;

		// Sets drive status flags
		switch(msg.DATA[3]){
			case 1: // Drive Bridge Status
				// Bit	Description
				// 0	Bridge Enabled
				// 1	Dynamic brake enabled
				// 2	Shunt Enabled
				// 3	Positive Stop enabled
				// 4 	Negative Stop enabled
				// 5	Positive Torque inhibit active
				// 6	Negative Torque inhibit active
				// 7 	External break active
				for(i = 0x1, j= DS_BRIDGE_ENABLED; j <= DS_EXTERNAL_BRAKE_ACTIVE; j++, i=i*2){
					if((aux & i) > 0){
						diff = calcdiff(tNow, tStatusRegisterTimer[j]);
						if(diff > DRIVE_STATUS_TIMER)
							bStatusRegister[j]= true;
					}else{
						tStatusRegisterTimer[j] = tNow;
						bStatusRegister[j]= false;
					}
					// If the status has changed, will print the flags
					if(bLastStatusRegister[j] != bStatusRegister[j]){
						bLastStatusRegister[j] = bStatusRegister[j];
						bPrintStatus = true;
					}
				}
				//ROS_INFO("Drive Bridge Status: %x [%d %d %d %d %d %d %d %d]", aux, bStatusRegister[0], bStatusRegister[1],
 				//   bStatusRegister[2], bStatusRegister[3], bStatusRegister[4], bStatusRegister[5], 
				//   bStatusRegister[6], bStatusRegister[7]);
			break;
			case 2: // Drive Protection Status
				// Bit	Description
				// 0	Drive Reset
				// 1	Drive Internal Error
				// 2	Short Circuit
				// 3	Current Overshot
				// 4	Under Voltage
				// 5	Over Voltage
				// 6 	Over Temperature
				for(i = 0x1, j= DS_DRIVE_RESET; j <= DS_DRIVER_OVER_TEMPERATURE; j++, i=i*2){
					if((aux & i) > 0){
						diff = calcdiff(tNow, tStatusRegisterTimer[j]);
						if(diff > DRIVE_STATUS_TIMER){
							bStatusRegister[j]= true;
							//ROS_INFO("%s::ProcessDriveStatus: flag = %d, diff = %d", sComponentName.c_str(), j, diff);
						}
					}else{
						tStatusRegisterTimer[j] = tNow;
						bStatusRegister[j]= false;
					}
					// If the status has changed, will print the flags
					if(bLastStatusRegister[j] != bStatusRegister[j]){
						bLastStatusRegister[j] = bStatusRegister[j];
						bPrintStatus = true;
					}
				}
				//ROS_INFO("Drive Protection Status: %x [%d %d %d %d %d %d %d]", aux, 
				//        bStatusRegister[8], bStatusRegister[9], bStatusRegister[10],
				//        bStatusRegister[11], bStatusRegister[12], bStatusRegister[13], bStatusRegister[14]);

			break;
			case 3: // System Protection Status
				// Bit	Description
				// 0	Pararameter Restore Error
				// 1	Parameter Store Error
				// 2	Invalid Hall State
				// 3	Phase Sync Error
				// 4	Motor Over Temperature
				// 5	Phase Detection Fault
				// 6 	Feedback Sensor Error
				// 7	Motor Over Speed
				// 8	Max. Measured Position
				// 9	Min. Measured Position
				// 10	Communication Error (Node Guarding)
				for(i = 0x1, j= DS_PARAMETER_RESTORE_ERROR; j <= DS_COMMUNICATION_ERROR; j++, i=i*2){
					if((aux & i) > 0){
						diff = calcdiff(tNow, tStatusRegisterTimer[j]);
						if(diff > DRIVE_STATUS_TIMER)
							bStatusRegister[j]= true;
					}else{
						tStatusRegisterTimer[j] = tNow;
						bStatusRegister[j]= false;
					}
					// If the status has changed, will print the flags
					if(bLastStatusRegister[j] != bStatusRegister[j]){
						bLastStatusRegister[j] = bStatusRegister[j];
						bPrintStatus = true;
					}
				}

				//ROS_INFO("Protection Status: %x [%d %d %d %d %d %d %d %d %d %d %d]", aux, bStatusRegister[15],
				//	bStatusRegister[16], bStatusRegister[17], bStatusRegister[18], bStatusRegister[19],
				//	bStatusRegister[20], bStatusRegister[21], bStatusRegister[22], bStatusRegister[23],
				//	bStatusRegister[24], bStatusRegister[25]);
			break;
			case 4: // Drive System Status 1
				// Bit	Description
				// 0	Log Entry Missed
				// 1	Commanded Disable
				// 2	User Disable
				// 3	Positive Inhibit
				// 4	Negative Inhibit
				// 5	Current Limiting
				// 6 	Continuous Current
				// 7	Current Loop Satured
				// 8	User Under Voltage
				// 9	User Over Voltage
				// 10	Non-Sinusoidal Commutation
				// 11	Phase Detection
				// 12
				// 13	User Auxiliary Disable
				// 14	Shunt Regulator
				// 15	Phase Detection Complete
				for(i = 0x1, j= DS_LOG_ENTRY_MISSED; j <= DS_PHASE_DETECTION; j++, i=i*2){
					if((aux & i) > 0){
						diff = calcdiff(tNow, tStatusRegisterTimer[j]);
						if(diff > DRIVE_STATUS_TIMER){
							bStatusRegister[j]= true;
							//ROS_INFO("%s::ProcessDriveStatus: flag = %d, diff = %d", sComponentName.c_str(), j, diff);
						}
					}else{
						tStatusRegisterTimer[j] = tNow;
						bStatusRegister[j]= false;
					}
					// If the status has changed, will print the flags
					if(bLastStatusRegister[j] != bStatusRegister[j]){
						bLastStatusRegister[j] = bStatusRegister[j];
						bPrintStatus = true;
					}
				}
				// 12 -> RESERVED
				i = i*2;

				for(j= DS_USER_AUXILIARY_DISABLE; j <= DS_PHASE_DETECTION_COMPLETE; j++, i=i*2){
					if((aux & i) > 0){
						diff = calcdiff(tNow, tStatusRegisterTimer[j]);
						if(diff > DRIVE_STATUS_TIMER)
							bStatusRegister[j]= true;
					}else{
						tStatusRegisterTimer[j] = tNow;
						bStatusRegister[j]= false;
					}
					// If the status has changed, will print the flags
					if(bLastStatusRegister[j] != bStatusRegister[j]){
						bLastStatusRegister[j] = bStatusRegister[j];
						bPrintStatus = true;
					}
				}
			break;
			case 5: // Drive System Status 2
				// Bit	Description
				// 0	Zero Velocity
				// 1	At command
				// 2	Velocity Following Error
				// 3	Positive Target Velocity Limit
				// 4	Negative Targe Velocity Limit
				// 5	Command Limiter Active
				// 6 	In Home Position
				// 7	Position Following Error
				// 8	Max. Target Position Limit
				// 9	Min. Target Position Limit
				// 10	Load Measured Position
				// 11	Load Target
				// 12	Homing Active
				// 13	Reserved
				// 14	Homing Complete
				// 15	Reserved
				for(i = 0x1, j= DS_ZERO_VELOCITY; j <= DS_HOMING_ACTIVE; j++, i=i*2){
					if((aux & i) > 0){
						diff = calcdiff(tNow, tStatusRegisterTimer[j]);
						if(diff > DRIVE_STATUS_TIMER)
							bStatusRegister[j]= true;
					}else{
						tStatusRegisterTimer[j] = tNow;
						bStatusRegister[j]= false;
					}
					// If the status has changed, will print the flags
					if(bLastStatusRegister[j] != bStatusRegister[j]){
						bLastStatusRegister[j] = bStatusRegister[j];
						bPrintStatus = true;
					}
				}
				// 13 -> RESERVED
				i = i*2;
				if((aux & i) > 0){
					diff = calcdiff(tNow, tStatusRegisterTimer[DS_HOMING_COMPLETE]);
					if(diff > DRIVE_STATUS_TIMER)
						bStatusRegister[DS_HOMING_COMPLETE]= true;
				}else{
					tStatusRegisterTimer[DS_HOMING_COMPLETE] = tNow;
					bStatusRegister[DS_HOMING_COMPLETE]= false;
				}
				// If the status has changed, will print the flags
				if(bLastStatusRegister[DS_HOMING_COMPLETE] != bStatusRegister[DS_HOMING_COMPLETE]){
					bLastStatusRegister[DS_HOMING_COMPLETE] = bStatusRegister[DS_HOMING_COMPLETE];
					bPrintStatus = true;
				}
			break;
			case 6: // Drive System Status 3
				// Bit	Description
				// 0	PVT Buffer Full
				// 1	PVT Buffer Empty
				// 2	PVT Buffer Threshold
				// 3	PVT Buffer Failure
				// 4	PVT Buffer Empty Stop
				// 5	PVT Buffer Sequence Error
				// 6 	Commanded Stop
				// 7	User Quick Stop
				// 8	RESERVED
				// 9	RESERVED
				// 10	RESERVED
				// 11	Commanded Positive Limit
				// 12	Commanded Negative Limit
				// 13	RESERVED
				// 14	RESERVED
				// 15	RESERVED
				for(i = 0x1, j= DS_PVT_BUFFER_FULL; j <= DS_USER_QUICKSTOP; j++, i=i*2){
					if((aux & i) > 0){
						diff = calcdiff(tNow, tStatusRegisterTimer[j]);
						if(diff > DRIVE_STATUS_TIMER)
							bStatusRegister[j]= true;
					}else{
						tStatusRegisterTimer[j] = tNow;
						bStatusRegister[j]= false;
					}
					// If the status has changed, will print the flags
					if(bLastStatusRegister[j] != bStatusRegister[j]){
						bLastStatusRegister[j] = bStatusRegister[j];
						bPrintStatus = true;
					}
				}
				// 8,9,10  -> RESERVED
				i = i*8;
				for(j= DS_COMMANDED_POSITIVE_LIMIT; j <= DS_COMMANDED_NEGATIVE_LIMIT; j++, i=i*2){
					if((aux & i) > 0){
						diff = calcdiff(tNow, tStatusRegisterTimer[j]);
						if(diff > DRIVE_STATUS_TIMER)
							bStatusRegister[j]= true;
					}else{
						tStatusRegisterTimer[j] = tNow;
						bStatusRegister[j]= false;
					}
					// If the status has changed, will print the flags
					if(bLastStatusRegister[j] != bStatusRegister[j]){
						bLastStatusRegister[j] = bStatusRegister[j];
						bPrintStatus = true;
					}
				}
			break;
		}
	}
	// Prints / Logs the value of every flags
	if(bPrintStatus && bLogDriveStatus){
		PrintDriveStatusRegister();
	}
	//ROS_INFO("%s::ProcessDriveStatus(%d): [%x %x]-> %x",sComponentName.c_str(), msg.DATA[3], msg.DATA[5], 
	// msg.DATA[4], iDriveStatus[msg.DATA[3] - 1]);
}

/*!	\fn	 void MotorDrive::ProcessDigitalInputs(TPCANMsg msg)
 * 	\brief Process the value of the digital inputs received from the drive
 * 	\param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessDigitalInputs(TPCANMsg msg){
    byte input;
    unsigned int ui_input = 0;

    // 2 bucles of 4x8 = 32 bytes
    for(int i = 0; i < 4; i++){
		input = msg.DATA[i+4];

		for(int j = 0; j < 8; j++){
            if((input& 1) == 1){
                digitalInputs.bValue[i*8 + j] = true;
            }else
                digitalInputs.bValue[i*8 + j] = false;

            input= input>> 1;
        }
	}
    // Saves the value as an unsigned int
	for(int i = 31; i >= 0; i--){
		ui_input <<=1;
		if(digitalInputs.bValue[i] == true)
			ui_input |= 0x00000001;
		else
			ui_input &= 0xFFFFFFFE;
	}

	digitalInputs.uiValue = ui_input;
}

/*!	\fn void MotorDrive::ProcessDigitalOutputs(TPCANMsg msg)
 * 	\brief Process the value of the digital Outputs received from the drive
 * 	\param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessDigitalOutputs(TPCANMsg msg){
    byte output;
    unsigned int ui_output = 0;

    // 2 bucles of 4x8 = 32 bytes
    for(int i = 0; i < 4; i++){
		output = msg.DATA[i+4];

		for(int j = 0; j < 8; j++){
            if((output& 1) == 1){
                digitalRealOutputs.bValue[i*8 + j] = true;
            }else
                digitalRealOutputs.bValue[i*8 + j] = false;

            output = output>> 1;
        }
	}
    // Saves the value as an unsigned int
	for(int i = 31; i >= 0; i--){
		ui_output <<=1;
		if(digitalRealOutputs.bValue[i] == true)
			ui_output |= 0x00000001;
		else
			ui_output &= 0xFFFFFFFE;
	}

	digitalRealOutputs.uiValue = ui_output;
}

/*! \fn void MotorDrive::ProcessAnalogInputs(TPCANMsg msg)
 * 	\brief Process received Analog Inputs messages
 * 	\param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessAnalogInputs(TPCANMsg msg){
	short aux_input = 0;
	int number = 0;

	number = msg.DATA[3]; //Subindex has the number of the analog input
	switch(number){
		case 1:	//Input 1
			aux_input = msg.DATA[5] << 8;
			aux_input|= msg.DATA[4];
			dAnalogInputs[number-1]=(double)aux_input*20.0/pow(2,14); // Convert into volts
			//ROS_INFO("%s::ProcessSDOAnalogInputs: input (%d) received = %lf", sComponentName.c_str(), number, dAnalogInputs[number-1]);
		break;
		case 2: //Input 2
			aux_input = msg.DATA[5] << 8;
			aux_input|= msg.DATA[4];
			dAnalogInputs[number-1]= ((double)aux_input*20.0/pow(2,14));// Convert into volts
		break;
		case 3: //Input 3
			aux_input = msg.DATA[5] << 8;
			aux_input|= msg.DATA[4];
			dAnalogInputs[number-1]= ((double)aux_input*20.0/pow(2,14));// Convert into volts
		break;
		default: //Unknown Input
			ROS_ERROR("%s::ProcessSDOAnalogInputs: Unknow input (%d) received", sComponentName.c_str(), number);
			return;
		break;
	}

}

/*!	\fn	 void MotorDrive::ProcessModeOfOperation(TPCANMsg msg)
 * 	\brief Process received mode of operation message
 * 	\param msg as a TPCANMsg, the message to process
*/
void MotorDrive::ProcessModeOfOperation(TPCANMsg msg){
	modModeOfOperation = (ModeOfOperation)msg.DATA[4];
	//ROS_INFO("%s::ProcessModeOfOperation: Node %d: value = %x", sComponentName.c_str(), CanId, modModeOfOperation);
}

/*!	\fn	unsigned int MotorDrive::GetDigitalInputs()
 * 	\brief Function to get the value of all digital inputs
 * 	\return drive's digital inputs as an unsigned integer
*/
unsigned int MotorDrive::GetDigitalInputs(){

    return digitalInputs.uiValue;
}

/*!	\fn	bool MotorDrive::GetDigitalInput(unsigned int input)
 * 	\brief Function for getting the selected digital input value
 *  \param input as unsigned int, number of the input (1 to uiNumOfDigIn) to get the value
 * 	\return true
 *  \return false
*/
bool MotorDrive::GetDigitalInput(unsigned int input){

    if((input == 0) || (input > uiNumOfDigIn) || (input > 32)){
        ROS_ERROR("MotorDrive::GetDigitalInput: input %d out of range", input);
        return false;
    }

    return digitalInputs.bValue[input - 1];
}

/*!	\fn	double MotorDrive::GetAnalogInput(unsigned int input)
 * 	\brief Function for getting the selected analog input value
 *  \param input as unsigned int, number of the input (1 to uiNumOfAnagIn) to get the value
 * 	\return the value of the input
*/
double MotorDrive::GetAnalogInput(unsigned int input){

    if((input == 0) || (input > uiNumOfAnagIn)){
        ROS_ERROR("MotorDrive::GetAnalogInput: input %d out of range", input);
        return false;
    }

    return dAnalogInputs[input - 1];
}

/*! \fn	ReturnValue MotorDrive::SetDigitalOutputs(unsigned int output)
 *  \brief Function to set the value of the digital outputs
 *  \param Outputs as unsigned int, value of the digital outputs
 *  \return OK
 *  \return ERROR
*/
ReturnValue MotorDrive::SetDigitalOutputs(unsigned int output){

    if( Send(CanId, DIGITAL_OUTPUTS_MSG, WRITE, (int)output) == OK ){

        digitalOutputs.uiValue = output;
         // Saves the current digital outputs value into the structure
        for(int i = 0; i < 32; i++){
            if((output& 1) == 1){
                digitalOutputs.bValue[i] = true;
            }else
                digitalOutputs.bValue[i] = false;

            output = output>> 1;
        }

        return OK;

    } else {
        ROS_ERROR("MotorDrive::SetDigitalOutputs: Error setting the digital outputs to %x", output);
        return ERROR;
    }
}

/*! \fn	ReturnValue MotorDrive::SetDigitalOutputs (unsigned int index, bool value)
 * 	\brief Function to set drive's digital outputs
 *  \param index as int, number of the digital output
 *  \param value as bool, value of the digital output
 *  \return OK
 *  \return ERROR
*/
ReturnValue MotorDrive::SetDigitalOutputs(unsigned int index, bool value){
    unsigned int aux=0;

    if((index == 0) || (index > uiNumOfDigOut) || (index > 32)){
        ROS_ERROR("%s::SetDigitalOutputs: output %d out of range",sComponentName.c_str(), index);
        return ERROR;
    }

    digitalOutputs.bValue[index - 1] = value;

    for(int i = 0; i < 32; i++){
        if(digitalOutputs.bValue[i]) {			
            aux += pow(2.0, i);
            //ROS_INFO("i=%d aux=%d", i, aux);
		    }
    }
    
    digitalOutputs.uiValue = aux;
    // ROS_INFO("SetDigitalOutputs : index=%d, value=%d, aux = %x", index, value, aux);

    if( Send( CanId, DIGITAL_OUTPUTS_MSG, WRITE, (int)aux ) == OK )
        return OK;
    else {
        ROS_ERROR("%s::SetDigitalOutputs: Error setting the digital output %d to %d", sComponentName.c_str(), (int)index, (int)value);
        return ERROR;
    }

}

/*! \fn	unsigned int MotorDrive::GetDigitalOutputs()
 * 	\brief Function to get the values of the digital outputs
 *  \return drive's digital outputs
*/
unsigned int MotorDrive::GetDigitalOutputs(){
    return digitalRealOutputs.uiValue;
}

/*! \fn	bool MotorDrive::GetDigitalOutput(unsigned int output)
 * 	\brief Function for getting the selected digital output value
 *  \return true
 *  \return false
*/
bool MotorDrive::GetDigitalOutput(unsigned int output){

    if((output == 0) || (output > uiNumOfDigOut) || (output > 32)){
        ROS_ERROR("MotorDrive::GetDigitalOutput: output %d out of range", output);
        return false;
    }

    return digitalRealOutputs.bValue[output - 1];
}

/*! \fn ReturnValue MotorDrive::Start()
 * Starts the control thread of the component and its subcomponents
 * \return OK
 * \return RUNNING if it's already running
 * \return NOT_INITIALIZED if the component is not initialized
*/
ReturnValue MotorDrive::Start(){
    ReturnValue ret;
    int priority_aux = 25;
    double frec_aux = 5.0;

    // Starts main thread
    ret = Component::Start();

    if(ret != OK)
        return ret;

    // Creates auxiliar thread to control the communication status with the drive
    ret = Component::CreateTask(priority_aux, frec_aux, AuxMotorDriveControlCommunicationThread);

    if(ret == ERROR){
        bRunning = false;
        ROS_ERROR("%s::Start: Error launching auxiliary thread", sComponentName.c_str());
	return ERROR;
    }

	// Creates auxiliar thread to read SDO messages from the module
    ret = Component::CreateTask(priority_aux, frec_aux, AuxMotorDriveReadSDOMessagesThread);

    if(ret == ERROR){
        bRunning = false;
        ROS_ERROR("%s::Start: Error launching auxiliary thread 2", sComponentName.c_str());
	return ERROR;
    }

    return OK;
}

/*! \fn void MotorDrive::ControlCommunicationThread()
 	* Thread to control the communication with the driver
 	* All auxiliary threads should have this structure
*/
void MotorDrive::ControlCommunicationThread(){
	struct sched_param schedp;
	int policy = threadData.pthreadPar.prio? SCHED_FIFO : SCHED_OTHER;
	struct timespec now, next, interval;
	//long diff;
	unsigned long sampling_period_us;
	thread_data current_data;
	struct timespec time;
	long time_diff = 0;
	bool bPrintError = false;

	// LLamada obligatoria para obtener los datos del thread
	if(GetThreadData(&current_data) == ERROR ){
	ROS_ERROR("%s::ControlCommunicationThread: Error getting thread data", sComponentName.c_str());
	return;
	}
	ROS_INFO("%s::ControlCommunicationThread: Executing thread (%d, %lf)", sComponentName.c_str(), 
				current_data.pthreadPar.prio, current_data.dDesiredHz );

	// Robotnik thread priority and timing management
	memset(&schedp, 0, sizeof(schedp));
	schedp.sched_priority = current_data.pthreadPar.prio;
	sched_setscheduler(0, policy, &schedp);
	clock_gettime(current_data.pthreadPar.clock, &now);
 	next = now;
	next.tv_sec++;  // start in next second?
	sampling_period_us =  (long unsigned int) (1.0 / current_data.dDesiredHz * 1000000.0);
	interval.tv_sec = sampling_period_us / USEC_PER_SEC;  // interval parameter in uS
	interval.tv_nsec = (sampling_period_us % USEC_PER_SEC)*1000;

	ROS_INFO("%s::ControlCommunicationThread: Starting the thread", sComponentName.c_str());

	while(bRunning) { // Executes state machine code while bRunning flag is active
		clock_nanosleep(threadData.pthreadPar.clock, TIMER_ABSTIME, &next, NULL);
		clock_gettime(threadData.pthreadPar.clock, &now);
		next.tv_sec += interval.tv_sec;
		next.tv_nsec += interval.tv_nsec;
		tsnorm(&next);
        //////////////// ACTIONS  //////////////////////////
        // Sending node guard message
        Send(CanId, NODEGUARD_MSG, WRITE, 0);
		//usleep(10000);
		//Send(CanId, HEARTBEAT_MSG, WRITE, 0);

        //if((commStatus != FAULT)){
        // Gets the current time to compare
        clock_gettime(threadData.pthreadPar.clock, &time);
        tsnorm(&time);
        time_diff = time.tv_sec - tNodeGuardReply.tv_sec;

		// Bug - 2013/06/26 - Fails during homing 
        if(time_diff > NMT_TIMEOUT){
			if(!bPrintError){
				ROS_ERROR( "%s::ControlCommunicationThread: Node %d: error in communication with the device", sComponentName.c_str(), CanId);
				bPrintError = true;
				}
            //SwitchToCommunicationStatus((CommunicationStatus)FAULT);
        }else
			bPrintError = false;
        //}

        ////////////////////////////////////////////////////
	}
	ROS_INFO( "%s::ControlCommunicationThread: End", sComponentName.c_str());
};

/*!	\fn void MotorDrive::Delay()
 * 	\brief Sleeps for a moment
*/
void MotorDrive::Delay(){
	struct timespec wait;

	clock_gettime(threadData.pthreadPar.clock, &wait);
	wait.tv_nsec+= uiDelayTrans;
	clock_nanosleep(threadData.pthreadPar.clock, TIMER_ABSTIME, &wait, NULL);
}

/*!	\fn void MotorDrive::Delay(unsigned int value)
 * 	\brief Sleeps for a moment
*/
void MotorDrive::Delay(unsigned int value){
	struct timespec wait;

	clock_gettime(threadData.pthreadPar.clock, &wait);
	wait.tv_nsec+= value * uiDelayTrans;
	clock_nanosleep(threadData.pthreadPar.clock, TIMER_ABSTIME, &wait, NULL);
}

/*! \fn DriveStatus MotorDrive::GetStatus()
 * 	\brief function to get the status of the drive
 * 	\return status of the drive
*/
Dzcante020l080::DriveStatus MotorDrive::GetStatus(){
	return dsStatus;
}

/*! \fn char *MotorDrive::GetStatusString()
 * 	\brief function to get the status of the drive
 * 	\return the status of the motor drive
*/
char *MotorDrive::GetStatusString(){
	switch(dsStatus){
		case UNKNOWN:
			return (char*)"UNKNOWN           ";
		break;
		case SWITCH_ON_DISABLED:
			return (char*)"SWITCH_ON_DISABLED";
		break;
		case READY_TO_SWITCH_ON:
			return (char*)"READY_TO_SWITCH_ON";
		break;
		case OPERATION_ENABLED:
			return (char*)"OPERATION_ENABLED ";
		break;
		case OPERATION_DISABLED:
			return (char*)"OPERATION_DISABLED ";
		break;
		case FAULT:
			return (char*)"FAULT             ";
		break;
		case UNDER_VOLTAGE:
			return (char*)"UNDER_VOLTAGE     ";
		break;
		case QUICK_STOP:
			return (char*)"QUICK_STOP        ";
		break;
		default:
			return (char*)"UNKNOWN           ";
		break;

	}
}

/*!	\fn ModeOfOperation MotorDrive::GetModeOfOperation()
 * 	\brief Gets drive's mode of operation
 * 	\return Mode of operation
*/
Dzcante020l080::ModeOfOperation MotorDrive::GetModeOfOperation(){
	return modModeOfOperation;
}

/*!	\fn char * MotorDrive::GetStatusWordString()
 * 	@return Returns the value of the internal status word as a string
*/
char * MotorDrive::GetStatusWordString(){
	char *cAux = new char[17];

	for(int i= 0; i<16; i++){
		if(bStatusWord[i])
			cAux[i] = '1';
		else
			cAux[i] = '0';
	}
	
	cAux[16]='\0';

	return cAux;
}

/*!	\fn char * MotorDrive::GetStatusWordString()
 * 	@return Returns the value of the internal status word as a string
*/
char * MotorDrive::GetStatusRegisterFlagsString(){
	char *cAux = new char[DS_NUMBER];

	for(int i = 0; i < DS_NUMBER; i++){
		if(bStatusRegister[i])
			cAux[i] = '1';
		else
			cAux[i] = '0';
	}
	
	cAux[DS_NUMBER]='\0';

	return cAux;
}

/*! \fn void MotorDrive::SetDesiredStatus(DriveStatus new_status)
 * 	\brief Sets the desired status of the driver
*/
void MotorDrive::SetDesiredStatus(DriveStatus new_status){
	dsDesiredStatus = new_status;
}

/*! \fn void int16_t MotorDrive::GetDriveStatus(int object)
 * 	\brief 	Gets the value of internal drive status object
 *			1- Drive Bridge Status
 *			2- Drive Protection Status
 *          3- System Protection Status
 *			4- Drive System Status 1
 *			5- Drive System Status 2
 *			6- Drive System Status 3
 *	\param object as int, internal object to read (1 -> 6)
*/
int16_t MotorDrive::GetDriveStatus(int object){
	if(object < 1 || object > 6)
		return -1;

	return iDriveStatus[object - 1];
}

/*!	\fn ReturnValue MotorDrive::Initialize()
 * 	\brief Initializes the status of the drive
 * 	\return OK
 * 	\return ERROR
*/
ReturnValue MotorDrive::Initialize(){

	if(Send(CanId, DISABLE_VOLT_MSG, WRITE, 0) != OK){
		ROS_ERROR( "%s: Initialize: Node %d: Error sending Disable Voltage", sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

	if(Send(CanId, SHUTDOWN_MSG, WRITE, 0) != OK){
		ROS_ERROR( "%s: Initialize: Node %d: Error sending Shutdown",sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

	if(Send(CanId, SWITCH_ON_MSG, WRITE, 0) != OK){
		ROS_ERROR( "%s: Initialize: Node %d: Error sending Switch On",sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

	if(Send(CanId, ENABLE_OP_MSG, WRITE, 0) != OK){
		ROS_ERROR( "%s: Initialize: Node %d: Error sending Enable Operation",sComponentName.c_str(), CanId);
		return ERROR;
	}
	Delay();

	//Get the Mode Of Operation
	if(Send(CanId, MODE_OF_OPERATION_MSG, READ, 0) != OK){
		ROS_ERROR( "%s: Initialize: Node %d: Error sending get mode Of Operation", sComponentName.c_str(), CanId);
		return ERROR;
	}


	return OK;
}

/*!	\fn void MotorDrive::ProcessStatusWord(TPCANMsg msg)
	* Process the status_word value received from the drive and changes the status of the object
	* Data Description:
	* Bit	Description
	*  0	Ready To Switch On state indicator
	*  1	Switched On state indicator
	*  2	Operation Enabled state indicator
	*  3	Fault state indicator
	*  4	Voltage Enabled state indicator
	*  5	Quick Stop state indicator
	*  6	Switch On Disabled state indicator
	*  7	Warning indicator
	*  8	Delay state
    *  9    Remote (1 when drive is in remote mode)
	*  10   Target Reached (Home reached if can mode is active)
    *  11   Internal Limit Active
    *  12   Homing complete 1-when completes 0-otherwise
	*  ..	Not used for this application
	* \param status_word as a byte, with the current drive internal status
*/
void MotorDrive::ProcessStatusWord(TPCANMsg msg){
	int16_t aux_status = 0;
	int i, j;

	//Extract Status word
	aux_status = msg.DATA[5] << 8;
	aux_status |= msg.DATA[4];

	//ROS_INFO "MotorDrive::ProcessStatusWord:Node %d: status = %x, msg[0] = %x", CanId, aux_status, msg.DATA[0]);
	for(i = 0x1, j=0; j < 15; j++, i=i*2){
		if((aux_status & i) > 0){
			bStatusWord[j]= true;
		}else
			bStatusWord[j]= false;
	}

	if(bStatusWord[SW_FAULT])
		SwitchToStatus(FAULT);
	else if(!bStatusWord[SW_VOLTAGE_ENABLED] && bStatusWord[SW_SWITCH_ON_DISABLED])
		SwitchToStatus(SWITCH_ON_DISABLED);
	else if(bStatusWord[SW_OP_ENABLED]){
		if(!bStatusWord[SW_QUICK_STOP])
			SwitchToStatus(QUICK_STOP);
		else
			SwitchToStatus(OPERATION_ENABLED);
	}else if( bStatusWord[SW_READY_TO_SWITCH_ON] && bStatusWord[SW_SWITCHED_ON] )
		SwitchToStatus(OPERATION_DISABLED);
	else if(bStatusWord[SW_READY_TO_SWITCH_ON])
		SwitchToStatus(READY_TO_SWITCH_ON);
	else
		SwitchToStatus(UNKNOWN);

}

/*! \fn void MotorDrive::ReadSDOMessagesThread()
 	* Reads SDO messages from the device
 	* All auxiliary threads should have this structure
*/
void MotorDrive::ReadSDOMessagesThread(){
    struct sched_param schedp;
    int policy = threadData.pthreadPar.prio? SCHED_FIFO : SCHED_OTHER;
    struct timespec now, next, interval;
    unsigned long sampling_period_us;
    thread_data current_data;
    int drive_status_number = 1;	// number of Drive Status object to read (1-6)
    vector<double> vCurrent;        // Vector to store consumed current
    int index = 0;                  // Index of the latest value introduced in the previous vector
    double aux = 0.0;
    vector<double> vBattery;        // Vector to store the latest x values read
    int index_battery = 0;                  // Indice of the latest introduced values
    // Mandatory call to get the thread data
    if(GetThreadData(&current_data) == ERROR ){
        ROS_ERROR("IOModule::ReadSDOMessagesThread: Error getting thread data");
        return;
    }
    //ROS_INFO "%s::ReadSDOMessagesThread: Executing thread (%d, %lf)", sComponentName.c_str(), current_data.pthreadPar.prio, current_data.dDesiredHz );
	// Robotnik thread priority and timing management
	memset(&schedp, 0, sizeof(schedp));
	schedp.sched_priority = current_data.pthreadPar.prio;
	sched_setscheduler(0, policy, &schedp);
	clock_gettime(current_data.pthreadPar.clock, &now);
 	next = now;
	next.tv_sec++;  // start in next second?
	sampling_period_us =  (long unsigned int) (1.0 / current_data.dDesiredHz * 1000000.0);
	interval.tv_sec = sampling_period_us / USEC_PER_SEC;  // interval parameter in uS
	interval.tv_nsec = (sampling_period_us % USEC_PER_SEC)*1000;

	//ROS_INFO ( "%s::ReadSDOMessagesThread: Starting the thread", sComponentName.c_str());

	while(bRunning) { // Executes state machine code while bRunning flag is active
		clock_nanosleep(threadData.pthreadPar.clock, TIMER_ABSTIME, &next, NULL);
		clock_gettime(threadData.pthreadPar.clock, &now);
		next.tv_sec += interval.tv_sec;
		next.tv_nsec += interval.tv_nsec;
		tsnorm(&next);
        //////////////// ACTIONS  //////////////////////////
		//ROS_ERROR( "%s::ControlCommunicationThread: Node %d: Sending node guard", sComponentName.c_str(), CanId);
        if((commStatus != (CommunicationStatus)FAULT)){
                        // Reads Drive status
			Send(CanId, DRIVE_STATUS_MSG, READ, drive_status_number);

			if(++drive_status_number > 6)
				drive_status_number = 1;
			//Delay();
			
			/*
			// Read Analog Inputs
			for(int i = 0; i < DZCANTE_ANAG_INPUTS; i++){
				if(bAnalogEnable[i]){
					Delay();
					Send(CanId, ANALOG_INPUTS_MSG, READ, i+1);
					//ROS_INFO( "%s::ReadSDOMessagesThread: Node %d:  Reading analog input %d", sComponentName.c_str(),CanId, i+1);
				}

			}
			*/
 

		    /*
			// Read Consumed current
			Send(CanId, ACTUAL_CURRENT_SDO_MSG, READ, 0);
			//
			// Average the consumed current
			// Store the first X (thread freq) values. Acts as a cyclic buffer
			if(vCurrent.size() < (unsigned int)current_data.dDesiredHz){
                vCurrent.push_back(dInstantCurrent);
                index++;
			}else{
			    index++;

			    if(index >= (int)current_data.dDesiredHz)
                    index = 0;

                vCurrent[index] = dInstantCurrent;
                aux = 0;    // Initialize auxiliary variable to add the current measured in the last 5 iterations

                for(unsigned int k=0; k < vCurrent.size(); k++){
                    aux += fabs(vCurrent[k]);
                }
                dAverageCurrent = aux/(int)current_data.dDesiredHz;    // Calculate the 5 last measures average

			}
			*/


            // Read DC Bus Voltage
            Send(CanId, DC_BUS_SDO_MSG, READ, 0);

			// Calculate the average of the batery (analog input)
			// dInstantBattery = GetAnalogInput(BATTERY_ANALOG_INPUT);
			
			dInstantBattery = GetDCBusVoltage();

            if(vBattery.size() < (int)current_data.dDesiredHz){
                vBattery.push_back(dInstantBattery);
                index_battery++;
			}else{
			    index_battery++;

			    if(index_battery >= (int)current_data.dDesiredHz)
                    index_battery = 0;

                vBattery[index_battery] = dInstantBattery;
                aux = 0;            // Initialize auxiliary variable to add the battery value measured in the last 5 iterations.

                for(int k=0; k < vBattery.size(); k++){
                    aux += vBattery[k];
                }
                dAverageBattery = aux/(int)current_data.dDesiredHz;    // Calculate average of last 5 measurements
			// ROS_INFO ( "%s - Battery = %lf from %d measures. Index = %d", sComponentName.c_str(), dAverageBattery, vBattery.size(), index_battery);


			// Read Digital Inputs
			Send(CanId, DIGITAL_INPUTS_MSG, READ, 0);
			
			// Read Motor Position (in case it has encoder)
			Send(CanId, ACTUAL_POSITION_SDO_MSG, READ, 0);

			}
		}
	}

	//ROS_INFO ( "%s::ReadSDOMessagesThread: End", sComponentName.c_str());
};

/*! \fn ReturnValue MotorDrive::ConfigureRPDO(unsigned int rpdo_num)
*   \brief Configures RPDO Msg
*	\param rpdo_num as unsigned int, number of the rpdo to configure
*   \return ERROR
*	\return OK
*/
ReturnValue MotorDrive::ConfigureRPDO(unsigned int rpdo_num){
	unsigned int wait = 5;

	switch(rpdo_num){
		case 1:
			if(Send(CanId, CONF_RPDO1_1_MSG, WRITE, 0) != OK){
				ROS_ERROR( "%s::ConfigureRPDO%d-1: Error sending",sComponentName.c_str(), rpdo_num);
				return ERROR;
			}
			Delay(wait);
			if(Send(CanId, CONF_RPDO1_2_MSG, WRITE, (int)ASYNC) != OK){
				ROS_ERROR( "%s::ConfigureRPDO%d-2: Error sending",sComponentName.c_str(), rpdo_num);
				return ERROR;
			}
		break;

		case 21:
			if(Send(CanId, CONF_RPDO21_1_MSG, WRITE, 0) != OK){
				ROS_ERROR( "%s::ConfigureRPDO%d-1: Error sending",sComponentName.c_str(), rpdo_num);
				return ERROR;
			}
			Delay(wait);
			if(Send(CanId, CONF_RPDO21_2_MSG, WRITE, (int)ASYNC) != OK){
				ROS_ERROR( "%s::ConfigureRPDO%d-2: Error sending",sComponentName.c_str(), rpdo_num);
				return ERROR;
			}
		break;

		case 22:
			if(Send(CanId, CONF_RPDO22_1_MSG, WRITE, 0) != OK){
				ROS_ERROR( "%s::ConfigureRPDO%d-1: Error sending",sComponentName.c_str(), rpdo_num);
				return ERROR;
			}
			Delay(wait);
			if(Send(CanId, CONF_RPDO22_2_MSG, WRITE, (int)ASYNC) != OK){
				ROS_ERROR( "%s::ConfigureRPDO%d-2: Error sending",sComponentName.c_str(), rpdo_num);
				return ERROR;
			}
		break;
		default:
			ROS_ERROR( "%s::ConfigureRPDO%d: RPDO unavailable",sComponentName.c_str(), rpdo_num);
			return ERROR;
		break;
	}
	return OK;
}

/*! \fn ReturnValue MotorDrive::ConfigureTPDO(unsigned int tpdo_num, byte sync_cycles, bool enable)
*   \brief Configure TPDO Msgs
*	\param tpdo_num as unsigned int, number of tpdo to calibrate
*	\param sync_cycles as byte, number of sync messages to send the TPDO message
*	\param enable as bool, enables/disables the tpdo message
*   \return ERROR
*	\return OK
*/
ReturnValue MotorDrive::ConfigureTPDO(unsigned int tpdo_num, byte sync_cycles, bool enable){
	int param = 0;
	unsigned int wait = 5;
	// Controls the max number of sync cycles
	if(sync_cycles > 0xF0)
		sync_cycles = 0xF0;
	// Control the flag enable
	if(!enable)
		param = 0x80;

	switch(tpdo_num){
		case 1:
			if(Send(CanId, CONF_TPDO1_1_MSG, WRITE, param) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-1: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
			Delay(wait);
			if(Send(CanId, CONF_TPDO1_2_MSG, WRITE, (int)sync_cycles) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-2: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
		break;

		case 3:
			if(Send(CanId, CONF_TPDO3_1_MSG, WRITE, param) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-1: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
			Delay(wait);
			if(Send(CanId, CONF_TPDO3_2_MSG, WRITE, (int)sync_cycles) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-2: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
		break;

		case 4:
			if(Send(CanId, CONF_TPDO4_1_MSG, WRITE, param) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-1: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
			Delay(wait);
			if(Send(CanId, CONF_TPDO4_2_MSG, WRITE, (int)sync_cycles) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-2: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
		break;

		case 21:
			if(Send(CanId, CONF_TPDO21_1_MSG, WRITE, param) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-1: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
			Delay(wait);
			if(Send(CanId, CONF_TPDO21_2_MSG, WRITE, (int)sync_cycles) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-2: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
		break;

		case 22:
			if(Send(CanId, CONF_TPDO22_1_MSG, WRITE, param) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-1: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
			Delay(wait);
			if(Send(CanId, CONF_TPDO22_2_MSG, WRITE, (int)sync_cycles) != OK){
				ROS_ERROR( "%s::ConfigureTPDO%d-2: Error sending",sComponentName.c_str(), tpdo_num);
				return ERROR;
			}
		break;
		default:
			ROS_ERROR( "%s::ConfigureTPDO%d: TPDO unavailable",sComponentName.c_str(), tpdo_num);
			return ERROR;
		break;
	}

	return OK;
}

/*! \fn ReturnValue MotorDrive::ConfigureTPDO(unsigned int tpdo_num, byte sync_cycles, bool enable)
*   \brief Configures timer for nodeguard
*   \return ERROR
*	\return OK
*/
ReturnValue MotorDrive::ConfigureNodeGuardTimer(){

	if(Send(CanId, GUARD_TIME_MSG, WRITE, NODEGUARD_TIME) != OK){
		ROS_ERROR( "%s::ConfigureNodeGuardTimer: Node guard time: Error sending",sComponentName.c_str());
		return ERROR;
	}
	Delay(5);
	if(Send(CanId, LIFE_TIME_FACTOR_MSG, WRITE, NODEGUARD_FACTOR) != OK){ // NODEGUARD_FACTOR
		ROS_ERROR( "%s::ConfigureNodeGuardTimer: Life time factor Error sending",sComponentName.c_str());
		return ERROR;
	}
	Delay(5);
	if(Send(CanId, HEARTBEAT_CONSUMER_MSG, WRITE, 0) != OK){
		ROS_ERROR( "%s::ConfigureNodeGuardTimer: HeartBeat timer. Error sending",sComponentName.c_str());
		return ERROR;
	}
	Delay(5);
	// Configures actions when the communication error is produced
	if(Send(CanId, EVENT_ACTION_MSG, WRITE, EVENT_DISABLE_POWER) != OK){
		ROS_ERROR( "%s::ConfigureNodeGuardTimer: Event action. Error sending",sComponentName.c_str());
		return ERROR;
	}
	// Configures time to recever from communication error
	if(Send(CanId, EVENT_RECOVERY_TIME_MSG, WRITE, EVENT_RECOVERY_TIME) != OK){
		ROS_ERROR( "%s::ConfigureNodeGuardTimer: Event recovery time. Error sending",sComponentName.c_str());
		return ERROR;
	}
	return OK;

};

/*! \fn void MotorDrive::PrintDriveStatusRegister()
*   \brief Prints / Logs the value of every Drive Status flag
*/
void MotorDrive::PrintDriveStatusRegister(){
	char cAux[LOG_STRING_LENGTH] = "\0";
	bool bLog = false;

	sprintf(cAux, "%s(Node %d) - DriveStatus ", sComponentName.c_str(), CanId);
	for(int i = 0; i < DS_NUMBER; i++){
	    // Print the active flags that are active in the mask
		if(bStatusRegister[i] && bStatusRegisterMask[i]){
			strcat(cAux, " : ");
			strcat(cAux, GetStatusRegisterString((DriveStatusFlags)i));
			bLog = true;
			/*if(i == DS_CURRENT_LOOP_SATURED){
				char cCurrent[6] = "";
				strcat(cAux, " Current = ");
				sprintf(cCurrent, "%2.2lf", dInstantCurrent);
				strcat(cAux, cCurrent);
			}*/
		}
	}
	if(bLog)
		ROS_INFO(cAux);
};

/*! \fn const char *MotorDrive::GetStatusRegisterString(DriveStatusFlags flag)
*   \brief Returns the string value of the selected flag
*/
const char *MotorDrive::GetStatusRegisterString(DriveStatusFlags flag){
	switch(flag){

		case DS_COMMANDED_NEGATIVE_LIMIT: 		return "COMMANDED_NEGATIVE_LIMIT"; 		break;
		case DS_COMMANDED_POSITIVE_LIMIT: 		return "COMMANDED_POSITIVE_LIMIT"; 		break;
		case DS_USER_QUICKSTOP:					return "USER_QUICKSTOP"; 				break;
		case DS_COMMANDED_STOP:					return "COMMANDED_STOP";				break;
		case DS_PVT_BUFFER_SEQUENCE_ERROR:		return "PVT_BUFFER_SEQUENCE_ERROR";		break;
		case DS_PVT_BUFFER_EMPTY_STOP:			return "PVT_BUFFER_EMPTY_STOP";			break;
		case DS_PVT_BUFFER_FAILURE:				return "PVT_BUFFER_FAILURE";			break;
		case DS_PVT_BUFFER_THRESHOLD:			return "PVT_BUFFER_THRESHOLD";			break;
		case DS_PVT_BUFFER_EMPTY:				return "PVT_BUFFER_EMPTY";				break;
		case DS_PVT_BUFFER_FULL:				return "PVT_BUFFER_FULL";				break;
		case DS_HOMING_COMPLETE:				return "HOMING_COMPLETE";				break;
		case DS_HOMING_ACTIVE:					return "HOMING_ACTIVE";					break;
		case DS_LOAD_TARGET:					return "LOAD_TARGET";					break;
		case DS_LOAD_MEASURED_POSITION:			return "LOAD_MEASURED_POSITION";		break;
		case DS_MIN_TARGET_POSITION_LIMIT:		return "MIN_TARGET_POSITION_LIMIT";		break;
		case DS_MAX_TARGET_POSITION_LIMIT:		return "MAX_TARGET_POSITION_LIMIT";		break;
		case DS_POSITON_FOLLOWING_ERROR:		return "POSITON_FOLLOWING_ERROR";		break;
		case DS_IN_HOME_POSITION:				return "IN_HOME_POSITION";				break;
		case DS_COMMAND_LIMITER_ACTIVE:			return "COMMAND_LIMITER_ACTIVE";		break;
		case DS_NEGATIVE_TARGET_VELOCITY_LIMIT:	return "NEGATIVE_TARGET_VELOCITY_LIMIT";break;
		case DS_POSITIVE_TARGET_VELOCITY_LIMIT:	return "POSITIVE_TARGET_VELOCITY_LIMIT";break;
		case DS_VELOCITY_FOLLOWING_ERROR:		return "VELOCITY_FOLLOWING_ERROR";		break;
		case DS_AT_COMMAND:						return "AT_COMMAND";					break;
		case DS_ZERO_VELOCITY:					return "ZERO_VELOCITY";					break;
		case DS_PHASE_DETECTION_COMPLETE:		return "PHASE_DETECTION_COMPLETE";		break;
		case DS_SHUNT_REGULATOR:				return "SHUNT_REGULATOR";				break;
		case DS_USER_AUXILIARY_DISABLE:			return "USER_AUXILIARY_DISABLE";		break;
		case DS_PHASE_DETECTION:				return "PHASE_DETECTION";				break;
		case DS_NONSINUSOIDAL_COMMUTATION:		return "NONSINUSOIDAL_COMMUTATION";		break;
		case DS_USER_OVER_VOLTAGE:				return "USER_OVER_VOLTAGE";				break;
		case DS_USER_UNDER_VOLTAGE:				return "USER_UNDER_VOLTAGE";			break;
		case DS_CURRENT_LOOP_SATURED:			return "CURRENT_LOOP_SATURED";			break;
		case DS_CONTINUOUS_CURRENT:				return "CONTINUOUS_CURRENT";			break;
		case DS_CURRENT_LIMITING:				return "CURRENT_LIMITING";				break;
		case DS_NEGATIVE_INHIBIT:				return "NEGATIVE_INHIBIT";				break;
		case DS_POSITIVE_INHIBIT:				return "POSITIVE_INHIBIT";				break;
		case DS_USER_DISABLE:					return "USER_DISABLE";					break;
		case DS_COMMANDED_DISABLE:				return "COMMANDED_DISABLE";				break;
		case DS_LOG_ENTRY_MISSED:				return "LOG_ENTRY_MISSED";				break;
		case DS_COMMUNICATION_ERROR:			return "COMMUNICATION_ERROR";			break;
		case DS_MIN_MEASURED_POSITION:			return "MIN_MEASURED_POSITION";			break;
		case DS_MAX_MEASURED_POSITION:			return "MAX_MEASURED_POSITION";			break;
		case DS_MOTOR_OVER_SPEED:				return "MOTOR_OVER_SPEED";				break;
		case DS_FEEDBACK_SENSOR_ERROR:			return "FEEDBACK_SENSOR_ERROR";			break;
		case DS_PHASE_DETECTION_FAULT:			return "PHASE_DETECTION_FAULT";			break;
		case DS_MOTOR_OVER_TEMPERATURE:			return "MOTOR_OVER_TEMPERATURE";		break;
		case DS_PHASE_SYNC_ERROR:				return "PHASE_SYNC_ERROR";				break;
		case DS_INVALID_HALL_STATE:				return "INVALID_HALL_STATE";			break;
		case DS_PARAMETER_STORE_ERROR:			return "PARAMETER_STORE_ERROR";			break;
		case DS_PARAMETER_RESTORE_ERROR:		return "PARAMETER_RESTORE_ERROR";		break;
		case DS_DRIVER_OVER_TEMPERATURE:		return "DRIVER_OVER_TEMPERATURE";		break;
		case DS_OVER_VOLTAGE:					return "OVER_VOLTAGE";					break;
		case DS_UNDER_VOLTAGE:					return "UNDER_VOLTAGE";					break;
		case DS_CURRENT_OVERSHOOT:				return "CURRENT_OVERSHOOT";				break;
		case DS_SHORT_CIRCUIT:					return "SHORT_CIRCUIT";					break;
		case DS_DRIVE_INTERNAL_ERROR:			return "DRIVE_INTERNAL_ERROR";			break;
		case DS_DRIVE_RESET:					return "DRIVE_RESET";					break;
		case DS_EXTERNAL_BRAKE_ACTIVE:			return "EXTERNAL_BRAKE_ACTIVE";			break;
		case DS_NEGATIVE_TORQUE_INHIBIT_ACTIVE:	return "NEGATIVE_TORQUE_INHIBIT_ACTIVE";break;
		case DS_POSITIVE_TORQUE_INHIBIT_ACTIVE: return "POSITIVE_TORQUE_INHIBIT_ACTIVE";break;
		case DS_NEGATIVE_STOP_ENABLED:			return "NEGATIVE_STOP_ENABLED";			break;
		case DS_POSITIVE_STOP_ENABLED:			return "POSITIVE_STOP_ENABLED";			break;
		case DS_SHUNT_ENABLED:					return "SHUNT_ENABLED";					break;
		case DS_DYNAMIC_BRAKE_ENABLED:			return "DYNAMIC_BRAKE_ENABLED";			break;
		case DS_BRIDGE_ENABLED:					return "BRIDGE_ENABLED";				break;
		default:
			return "UNKNOWN";
		break;
	}
};

/*! \fn void MotorDrive::SetLogDriveStatus(bool value)
*   \brief Enables / disables the log of DriveStatus object
*/
void MotorDrive::SetLogDriveStatus(bool value){
	bLogDriveStatus = value;
};

/*! \fn byte MotorDrive::GetCanId()
*   \brief Returns the CAN id
*/
byte MotorDrive::GetCanId(){
    return CanId;
};

/*! \fn double MotorDrive::GetCurrent()
*   \brief Gets the consumed current
*/
double MotorDrive::GetCurrent(){
    return dAverageCurrent;
};

/*! \fn double MotorDrive::GetBattery()
*   \brief Gets the average of battery
*/
double MotorDrive::GetBattery(){
    return dAverageBattery;
};

/*! \fn double MotorDrive::GetDCBusVoltage()
*   \bried Gets the DC bus voltage
*/
double MotorDrive::GetDCBusVoltage(){
    return dDCBusVoltage;
};

/*! \fn void MotorDrive::InitStatusRegister()
*   \brief Initializes the status register mask and the control timers
*/
void MotorDrive::InitStatusRegister(){
    // Inicializamos todos los flags a false
	// Inicializamos los timers de control
	// Inits drive status flags
    for(int i = 0; i < DS_NUMBER; i++){
		bStatusRegister[i] = bLastStatusRegister[i] = false;
		bStatusRegisterMask[i] = false;
		clock_gettime(threadData.pthreadPar.clock, &tStatusRegisterTimer[i]);
    }
    //
    // Configuramos los flags que hay que controlar
    bStatusRegisterMask[DS_DRIVE_INTERNAL_ERROR] = true;
    bStatusRegisterMask[DS_SHORT_CIRCUIT] = true;
    //bStatusRegisterMask[DS_UNDER_VOLTAGE] = true;
    bStatusRegisterMask[DS_OVER_VOLTAGE] = true;
    bStatusRegisterMask[DS_DRIVER_OVER_TEMPERATURE] = true;
    bStatusRegisterMask[DS_MOTOR_OVER_SPEED] = true;
    bStatusRegisterMask[DS_COMMUNICATION_ERROR] = true;
    bStatusRegisterMask[DS_CURRENT_LIMITING] = true;
    bStatusRegisterMask[DS_CONTINUOUS_CURRENT] = true;
    bStatusRegisterMask[DS_CURRENT_LOOP_SATURED] = true;
    bStatusRegisterMask[DS_CURRENT_OVERSHOOT] = true;
    //bStatusRegisterMask[DS_USER_UNDER_VOLTAGE] = true;
    bStatusRegisterMask[DS_USER_OVER_VOLTAGE] = true;
    //bStatusRegisterMask[DS_NONSINUSOIDAL_COMMUTATION] = true;
    bStatusRegisterMask[DS_VELOCITY_FOLLOWING_ERROR] = true;
    bStatusRegisterMask[DS_POSITON_FOLLOWING_ERROR] = true;

};

/*! \fn ReturnValue MotorDrive::SetPeakCurrentLimit(int current)
*   \bried Sets the driver Peak Current Limit
*/
ReturnValue MotorDrive::SetPeakCurrentLimit(float current){
    
    if(current < 0.0 || current > 20.0)
			ROS_ERROR("Current limit is out of range");
		
    
    int currentScaled = (int)(current * pow(2,13) / 20);
    
    if(Send(CanId, CONF_SDO_PEAK_CURRENT_LIMIT_MSG, WRITE, currentScaled) != OK) 
		{
			ROS_INFO("%s::SetPeakCurrentLimit: Node %d: Error Setting Peak Current Limit", sComponentName.c_str(), CanId);
			return ERROR;
		}
    else
			return OK;
};

/** \file Motors.cc
 * \author Robotnik Automation S.L.L.
 * \version 1.0
 * \date 2012
 * \brief Class for controlling motors connected to Dzcante's motor drivers and I/O modules
 * Controla y gestiona la comunicación con los motores de dirección y tracción conectados a drivers Dzcante de AMC
 * (C) 2012 Robotnik Automation, SLL
 * All rights reserved.
 */

#include "summit_xl_controller/Motors.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


/*! \fn Motors::Motors(string dev, double hz, bool xwam,bool motors_encoders, double motors_encoders_factors))
 * Constructor by default
*/
Motors::Motors(string dev, double diameter_wheel, double gearbox, double hz, bool xwam,bool motors_encoder, double motors_encoder_factor,bool omni, double acceleration):Component(hz){

    dMaxLinearVelocity = DEFAULT_MAX_LINEAR_VELOCITY;
    dMaxAngularVelocity = DEFAULT_MAX_ANGULAR_VELOCITY;
    dDesiredLinearSpeedX = 0.0;
    dDesiredLinearSpeedY = 0.0;
    dDesiredAngularSpeed = 0.0;
    dDesiredScissorSpeed = 0.0;  
	dDesiredPosition = -1.0;
    idMotorFlw = DEFAULT_FLW_ID;
    idMotorFrw = DEFAULT_FRW_ID;
    idMotorBlw = DEFAULT_BLW_ID;
    idMotorBrw = DEFAULT_BRW_ID;
    idMotorScissor = DEFAULT_SCISSOR_ID;
    sComponentName.assign("Motors");
    pthread_mutex_init(&mutexOdometry, NULL); // Initialization for odometry's mutex
    bOdometry = true;
    bYawSensor = false;
    this->ResetOdometry();
    dFreq = hz;
    dAcceleration = acceleration;
    
    // Creation of every object
    canDev = new PCan( dev, CAN_BAUD_1M );  // default com speed 1M

    motorFlw = new MotorVelocity(idMotorFlw, canDev, hz, diameter_wheel, gearbox, motors_encoder,motors_encoder_factor);
    motorBlw = new MotorVelocity(idMotorBlw, canDev, hz, diameter_wheel, gearbox, motors_encoder,motors_encoder_factor);
    motorFrw = new MotorVelocity(idMotorFrw, canDev, hz, diameter_wheel, gearbox, motors_encoder,motors_encoder_factor);
    motorBrw = new MotorVelocity(idMotorBrw, canDev, hz, diameter_wheel, gearbox, motors_encoder,motors_encoder_factor);

    if (xwam) {
		ROS_INFO(" XWAM Mode configured in Motors ");
		motorScissor = new MotorVelocity( idMotorScissor, canDev, hz);
	}
    else motorScissor = NULL;
    // Homing
	bHomed = false;
	iHoming = 1;
	iScissorOriginPosition = 0;

    // All wheels are equal
    dRpmToMps = (motorFlw->GetWheelDiameter()*Pi)/60.0;	// (Diameter * Pi) / 60

    // Creation of alarm flags
    for(int i = 1 ; i <= DRIVER_NUM_ERRORS; i++){
	vAlarms.push_back(false);
	}
	bOmni=omni;
}

/*! \fn Motors::Motors(string dev, double hz, bool xwam))
 * Constructor by default
*/
Motors::Motors(string dev, double diameter_wheel, double gearbox, double hz, bool xwam,bool omni, double acceleration):Component(hz){

    dMaxLinearVelocity = DEFAULT_MAX_LINEAR_VELOCITY;
    dMaxAngularVelocity = DEFAULT_MAX_ANGULAR_VELOCITY;
    dDesiredLinearSpeedX = 0.0;
    dDesiredLinearSpeedY = 0.0;
    dDesiredAngularSpeed = 0.0;
    dDesiredScissorSpeed = 0.0;  
	dDesiredPosition = -1.0;
    idMotorFlw = DEFAULT_FLW_ID;
    idMotorFrw = DEFAULT_FRW_ID;
    idMotorBlw = DEFAULT_BLW_ID;
    idMotorBrw = DEFAULT_BRW_ID;
    idMotorScissor = DEFAULT_SCISSOR_ID;
    sComponentName.assign("Motors");
    pthread_mutex_init(&mutexOdometry, NULL); // Initialization for odometry's mutex
    bOdometry = true;
    bYawSensor = false;
    this->ResetOdometry();
    dFreq = hz;
    dAcceleration = acceleration;

    // Creation of every object
    canDev = new PCan( dev, CAN_BAUD_1M );  // default com speed 1M

    motorFlw = new MotorVelocity(idMotorFlw, canDev, hz, diameter_wheel, gearbox);
    motorBlw = new MotorVelocity(idMotorBlw, canDev, hz, diameter_wheel, gearbox);
    motorFrw = new MotorVelocity(idMotorFrw, canDev, hz, diameter_wheel, gearbox);
    motorBrw = new MotorVelocity(idMotorBrw, canDev, hz, diameter_wheel, gearbox);

    if (xwam) motorScissor = new MotorVelocity( idMotorScissor, canDev, hz);
    else motorScissor = NULL;
    // Homing
	bHomed = false;
	iHoming = 1;
	iScissorOriginPosition = 0;

    // All wheels are equal
    dRpmToMps = (motorFlw->GetWheelDiameter()*Pi)/60.0;	// (Diameter * Pi) / 60

    // Creation of alarm flags
    for(int i = 1 ; i <= DRIVER_NUM_ERRORS; i++){
	vAlarms.push_back(false);
	}
	bOmni=omni;
}
/*! \fn Motors::Motors(double hz)
 * Constructor by default
*/
Motors::Motors(double hz, bool xwam, double acceleration):Component(hz){

    dMaxLinearVelocity = DEFAULT_MAX_LINEAR_VELOCITY;
    dMaxAngularVelocity = DEFAULT_MAX_ANGULAR_VELOCITY;
    dDesiredLinearSpeedX = 0.0;
    dDesiredLinearSpeedY = 0.0;
    dDesiredAngularSpeed = 0.0;
    dDesiredScissorSpeed = 0.0;  
	dDesiredPosition = -1.0;
    idMotorFlw = DEFAULT_FLW_ID;
    idMotorFrw = DEFAULT_FRW_ID;
    idMotorBlw = DEFAULT_BLW_ID;
    idMotorBrw = DEFAULT_BRW_ID;
    idMotorScissor = DEFAULT_SCISSOR_ID;
    sComponentName.assign("Motors");
    pthread_mutex_init(&mutexOdometry, NULL); // Initialization for odometry's mutex
    bOdometry = true;
    bYawSensor = false;
    this->ResetOdometry();
    dFreq = hz;
    dAcceleration = LINEAR_ACCELERATION_DEFAULT;    

    // Creation of every object
    canDev = new PCan( CAN_BAUD_1M );  // default com speed 1M

    motorFlw = new MotorVelocity(idMotorFlw, canDev, hz);
    motorBlw = new MotorVelocity(idMotorBlw, canDev, hz);
    motorFrw = new MotorVelocity(idMotorFrw, canDev, hz);
    motorBrw = new MotorVelocity(idMotorBrw, canDev, hz);

    if (xwam) motorScissor = new MotorVelocity( idMotorScissor, canDev, hz);
    else motorScissor = NULL;
    // Homing
	bHomed = false;
	iHoming = 1;
	iScissorOriginPosition = 0;

    // All wheels are equal
    dRpmToMps = (motorFlw->GetWheelDiameter()*Pi)/60.0;	// (Diameter * Pi) / 60

    // Creation of alarm flags
    for(int i = 1 ; i <= DRIVER_NUM_ERRORS; i++){
		vAlarms.push_back(false);
	}
	bOmni=false;
}

/*! \fn Motors::Motors(double hz)
 * Constructor by default
*/
Motors::Motors(uint16_t baudrate, bool xwam, double hz, double acceleration):Component(hz){
  
    dMaxLinearVelocity = DEFAULT_MAX_LINEAR_VELOCITY;
    dMaxAngularVelocity = DEFAULT_MAX_ANGULAR_VELOCITY;
    dDesiredLinearSpeedX = 0.0;
    dDesiredLinearSpeedY = 0.0;
    dDesiredAngularSpeed = 0.0;
    dDesiredScissorSpeed = 0.0;
    dDesiredPosition = -1.0;
    idMotorFlw = DEFAULT_FLW_ID;
    idMotorFrw = DEFAULT_FRW_ID;
    idMotorBlw = DEFAULT_BLW_ID;
    idMotorBrw = DEFAULT_BRW_ID;
    idMotorScissor = DEFAULT_SCISSOR_ID;
    sComponentName.assign("Motors");
    pthread_mutex_init(&mutexOdometry, NULL); // Initialization for odometry's mutex
    bOdometry = true;
    this->ResetOdometry();
    dFreq = hz;
    dAcceleration = LINEAR_ACCELERATION_DEFAULT;        

    // Creation of every object
    if (baudrate == 0) baudrate = CAN_BAUD_1M;  // default speed 1M
    canDev = new PCan( baudrate );

    motorFlw = new MotorVelocity(idMotorFlw, canDev, hz);
    motorBlw = new MotorVelocity(idMotorBlw, canDev, hz);
    motorFrw = new MotorVelocity(idMotorFrw, canDev, hz);
    motorBrw = new MotorVelocity(idMotorBrw, canDev, hz);

	if (xwam) motorScissor = new MotorVelocity(idMotorScissor, canDev, hz);
	else motorScissor = NULL;
	bHomed = false;
	iHoming = 1;
	iScissorOriginPosition = 0;

    dRpmToMps = (motorFlw->GetWheelDiameter()*Pi)/60.0;	// (Diameter * Pi) / 60
	
    // Creation of alarm flags
    for(int i = 1 ; i <= DRIVER_NUM_ERRORS; i++){
       vAlarms.push_back(false);
       }
    bOmni=false;
}

/*! \fn Motors::~Motors(void)
	* Destructor by default
*/
Motors::~Motors(void){
    delete motorFlw;
    delete motorFrw;
    delete motorBlw;
    delete motorBrw;
    if (motorScissor!=NULL) delete motorScissor;
    delete canDev;
}

/*! \fn ReturnValue Motors::Setup()
 * Configures and initializes the component
 * \return OK
 * \return INITIALIZED if the component is already intialized
 * \return ERROR
*/
ReturnValue Motors::Setup(){

	// Checks if has been initialized
	if(bInitialized){
		ROS_ERROR( "%s::Setup: Already initialized",sComponentName.c_str());	
		return INITIALIZED;
	}

 	if(canDev->Setup() == ERROR){
           ROS_ERROR("%s::Setup: Error in CAN setup",sComponentName.c_str());
	   return ERROR;
	   }
	usleep(10000);
    if(motorFlw->Setup() == ERROR){
           ROS_ERROR("%s::Setup: Error in IO Dev setup",sComponentName.c_str());
	   return ERROR;
       }
	usleep(200000);
    if(motorFrw->Setup() == ERROR){
           ROS_ERROR("%s::Setup: Error in IO Dev setup",sComponentName.c_str());
	   return ERROR;
       }
	usleep(200000);
    if(motorBlw->Setup() == ERROR){
           ROS_ERROR("%s::Setup: Error in IO Dev setup",sComponentName.c_str());
	   return ERROR;
           }
	usleep(200000);
    if(motorBrw->Setup() == ERROR){
           ROS_ERROR("%s::Setup: Error in IO Dev setup",sComponentName.c_str());
	   return ERROR;
           }
	usleep(200000);

	if (motorScissor!=NULL) {
		if(motorScissor->Setup() == ERROR){
			   ROS_ERROR("%s::Setup: Error in IO Dev setup",sComponentName.c_str());
		   return ERROR;
			   }
		usleep(200000);
		}

	// TEST: Log flag changes in Drive status
	motorFlw->SetLogDriveStatus(true);
	motorFrw->SetLogDriveStatus(true);
	motorBlw->SetLogDriveStatus(true);
	motorBrw->SetLogDriveStatus(true);
    	
    if (motorScissor!=NULL) motorScissor->SetLogDriveStatus(true);

    bInitialized = true;

	return OK;
}

/*! \fn ReturnValue Motors::ShutDown()
 * Closes and frees the reserved resources
 * \return OK
 * \return THREAD_RUNNING if the component is running
 * \return NOT_INITIALIZED if the component is not initialized
 * \return ERROR
*/
ReturnValue Motors::ShutDown(){

	if(bRunning){
	    ROS_ERROR("%s::ShutDown: Impossible while thread running, first must be stopped",sComponentName.c_str());	    
	    return THREAD_RUNNING;
	    }
	if(!bInitialized){
	    ROS_ERROR("%s::ShutDown: Impossible because of it's not initialized", sComponentName.c_str());	    
	    return NOT_INITIALIZED;
	    }
	if(motorFlw->ShutDown() == ERROR){
	    ROS_ERROR("%s::ShutDown: Error shutdown motor vel", sComponentName.c_str());	    
	    return ERROR;
	    }
	if(motorBlw->ShutDown() == ERROR){
	    ROS_ERROR("%s::ShutDown: Error shutdown I/O ", sComponentName.c_str());
	    return ERROR;
	    }
	if(motorFrw->ShutDown() == ERROR){
	    ROS_ERROR("%s::ShutDown: Error shutdown motor pos", sComponentName.c_str());
	    return ERROR;
	    }
	if(motorBrw->ShutDown() == ERROR){
	    ROS_ERROR("%s::ShutDown: Error shutdown I/O ", sComponentName.c_str());
	    return ERROR;
	    }
	    
	if (motorScissor!=NULL) {
		if(motorScissor->ShutDown() == ERROR){
			ROS_ERROR("%s::ShutDown: Error shutdown I/O ", sComponentName.c_str());
			return ERROR;
			}
		}

	sleep(1);
	if(canDev->ShutDown() == ERROR){
	    ROS_ERROR("%s::ShutDown: Error shutdown CAN device", sComponentName.c_str());
		return ERROR;
	}

	bInitialized = false;

	return OK;
}

/*! \fn ReturnValue Motors::Start()
 * Starts the control thread of the component and its subcomponents
 * \return OK
 * \return RUNNING if it's already running
 * \return NOT_INITIALIZED if the component is not initialized
*/
ReturnValue Motors::Start(){
    ReturnValue ret;

     // Starts main thread
    ret = Component::Start();

    if(ret != OK)
        return ret;

    ret = motorFlw->Start();
    if(ret!= OK && ret != THREAD_RUNNING){
        bRunning = false;
        ROS_ERROR("%s::Start: Error starting motor velocity FLW", sComponentName.c_str());
        return ERROR;
    }
    usleep(2000);

    ret = motorBlw->Start();
    if(ret!= OK && ret != THREAD_RUNNING){
        bRunning = false;
        ROS_ERROR("%s::Start: Error starting motor velocity BLW", sComponentName.c_str());
        return ERROR;
    }
    usleep(2000);

    ret = motorFrw->Start();
    if(ret!= OK && ret != THREAD_RUNNING){
        bRunning = false;
        ROS_ERROR("%s::Start: Error starting motor velocity FRW", sComponentName.c_str());
        return ERROR;
    }
    usleep(2000);

    ret = motorBrw->Start();
    if(ret!= OK && ret != THREAD_RUNNING){
        bRunning = false;
        ROS_ERROR("%s::Start: Error starting motor velocity BRW", sComponentName.c_str());
        return ERROR;
    }
    usleep(2000);

	// Motor X
    if (motorScissor!=NULL) {
		ret = motorScissor->Start();
		if(ret!= OK && ret != THREAD_RUNNING){
			bRunning = false;
			ROS_ERROR("%s::Start: Error starting motor position SCISSOR", sComponentName.c_str());
			return ERROR;
			}
		}
    usleep(2000);
    
    // Inits the recovery timer
    clock_gettime(threadData.pthreadPar.clock, &tRecovery);
    
    ROS_INFO("%s::Start: Started", sComponentName.c_str());
    return OK;
}

/*! \fn ReturnValue Motors::Stop()
 * Stops the control thread of the Motors
 * \return OK
 * \return ERROR if it can't be stopped
 * \return THREAD_NOT_RUNNING if the thread is not running
*/
ReturnValue Motors::Stop(){

	if(!bRunning){
		ROS_INFO( "%s::Stop: Thread not running", sComponentName.c_str());
		return THREAD_NOT_RUNNING;
	}
	///////////////////////////////////////////////////
	// Stop other subcomponents if it's necessary 
	///////////////////////////////////////////////////
	motorFlw->Stop();	//STOPS motor FLW
	motorFrw->Stop();	//STOPS motor FRW
	motorBlw->Stop();	//STOPS motor BLW
	motorBrw->Stop();	//STOPS motor BRW
	if (motorScissor!=NULL) motorScissor->Stop();

	ROS_INFO( "%s::Stop: Stopping the thread", sComponentName.c_str());
	bRunning = false;
	usleep(100000);
	return OK;
}

/*! \fn ReturnValue Motors::ReadCANMessages()
 *	\brief Read messages from CAN bus
 *	\return ERROR
 *	\return OK
*/
ReturnValue Motors::ReadCANMessages(){
	TPCANRdMsg tpcmsg_read;
	int len=100;
	int i=0;
	byte aux_id = 0;


	// Read and process up to 100 messages
	for (i=0;i<len;i++) {
                int iRet = canDev->Read(&tpcmsg_read);
		if(iRet == ERROR){
		  ROS_ERROR("Motors::ReadCANMessages: Error Reading messages from bus");
		  return ERROR;
		}else {
		  if (iRet == OK) {  // Something has been read			              
			aux_id = tpcmsg_read.Msg.ID & 0xF; 
			//ROS_INFO( "Motors:ReadCANMessages: Read msg(%d): id=%x, len=%d, data[ %x %x %x %x %x %x %x %x ]", 
			// i, tpcmsg_read.Msg.ID, tpcmsg_read.Msg.LEN, tpcmsg_read.Msg.DATA[0], tpcmsg_read.Msg.DATA[1], 
			//tpcmsg_read.Msg.DATA[2], tpcmsg_read.Msg.DATA[3], tpcmsg_read.Msg.DATA[4], 
			//tpcmsg_read.Msg.DATA[5], tpcmsg_read.Msg.DATA[6], tpcmsg_read.Msg.DATA[7]);		     
			// aux_id = tpcmsg_read.Msg.ID & 0xF; 
			if(aux_id == idMotorFlw)
			    motorFlw->ProcessCANMessage(tpcmsg_read.Msg);
			else if(aux_id == idMotorBlw) 
			    motorBlw->ProcessCANMessage(tpcmsg_read.Msg);
			else if(aux_id == idMotorFrw)
			    motorFrw->ProcessCANMessage(tpcmsg_read.Msg);
			else if(aux_id == idMotorBrw)
		    	    motorBrw->ProcessCANMessage(tpcmsg_read.Msg);
		    else if (aux_id == idMotorScissor)
					if (motorScissor!=NULL) motorScissor->ProcessCANMessage(tpcmsg_read.Msg);
			}
			// there may be nothing to read
		   }
		}
	 return OK;
}

/*!	\fn void Motors::InitState()
 *	\brief Actions performed on InitState
*/
void Motors::InitState(){
      States stateMotorFlw, stateMotorBlw, stateMotorFrw, stateMotorBrw, stateMotorScissor=INIT_STATE;
      MotorDrive::DriveStatus statusMotorFlw, statusMotorBlw, statusMotorFrw, statusMotorBrw, statusMotorScissor=Dzcante020l080::UNKNOWN;

      stateMotorFlw = motorFlw->GetState();
      stateMotorBlw = motorBlw->GetState();
      stateMotorFrw = motorFrw->GetState();
      stateMotorBrw = motorBrw->GetState();
      if (motorScissor!=NULL) stateMotorScissor = motorScissor->GetState();
      statusMotorFlw = motorFlw->GetStatus(); 
      statusMotorBlw = motorBlw->GetStatus();
      statusMotorFrw = motorFrw->GetStatus();
      statusMotorBrw = motorBrw->GetStatus();
      if (motorScissor!=NULL) statusMotorScissor = motorScissor->GetStatus();

      // Transitions?
      // Components on Emergency State
      if(stateMotorFlw == EMERGENCY_STATE || stateMotorFrw == EMERGENCY_STATE 
      || stateMotorBlw == EMERGENCY_STATE || stateMotorBrw == EMERGENCY_STATE 
      || stateMotorScissor == EMERGENCY_STATE){
        SwitchToState(EMERGENCY_STATE);
        return;
        }
      // Checks Drive internal status
      if(statusMotorFlw == Dzcante020l080::FAULT || statusMotorFrw == Dzcante020l080::FAULT
       || statusMotorBlw == Dzcante020l080::FAULT || statusMotorBrw == Dzcante020l080::FAULT 
       || statusMotorScissor == Dzcante020l080::FAULT){
        SwitchToState(EMERGENCY_STATE);
        return;
        }
      if(stateMotorFlw == INIT_STATE || stateMotorFrw == INIT_STATE 
       || stateMotorBlw == INIT_STATE || stateMotorBrw == INIT_STATE){
        return;
        }

	  // Velocity control of X axis, axis home is not needed at this stage
      if (motorScissor!=NULL) {
		if (stateMotorScissor == INIT_STATE) return;
		}
      SwitchToState(STANDBY_STATE);

      // ROS_INFO("Motors:: INIT_STATE");

      // Initialize encoder position values
      // iLastEncoderVelocityValue = motor->GetMotorPosition();
      
      return;
}

/*!	\fn void Motors::StandbyState()
 *	\brief Actions performed on Standby state
*/
void Motors::StandbyState(){
    States stateMotorFlw, stateMotorFrw, stateMotorBlw, stateMotorBrw, stateMotorScissor=INIT_STATE;
    MotorDrive::DriveStatus statusMotorFlw, statusMotorBlw, statusMotorFrw, statusMotorBrw, statusMotorScissor=Dzcante020l080::UNKNOWN;

    stateMotorFlw = motorFlw->GetState();
    stateMotorBlw = motorBlw->GetState();
    stateMotorFrw = motorFrw->GetState();
    stateMotorBrw = motorBrw->GetState();
    if (motorScissor!=NULL) stateMotorScissor = motorScissor->GetState();
    statusMotorFlw = motorFlw->GetStatus(); 
    statusMotorBlw = motorBlw->GetStatus();
    statusMotorFrw = motorFrw->GetStatus();
    statusMotorBrw = motorBrw->GetStatus();
    if (motorScissor!=NULL) statusMotorScissor = motorScissor->GetStatus();

    // Transitions ? 
    // Transition -> Emergency
    if(stateMotorFlw == EMERGENCY_STATE || stateMotorFrw == EMERGENCY_STATE 
       || stateMotorBlw == EMERGENCY_STATE || stateMotorBrw ==EMERGENCY_STATE || stateMotorScissor==EMERGENCY_STATE){
        SwitchToState(EMERGENCY_STATE);
        return;
        }
    // Transition -> Emergency
    if(statusMotorFlw == Dzcante020l080::FAULT || statusMotorFrw == Dzcante020l080::FAULT
       || statusMotorBlw == Dzcante020l080::FAULT || statusMotorBrw == Dzcante020l080::FAULT || statusMotorScissor == Dzcante020l080::FAULT){
       SwitchToState(EMERGENCY_STATE);
       return;
       }

    // Transition -> Ready
    bool bScissorEnabled = true;
    if (motorScissor!=NULL) bScissorEnabled = (statusMotorScissor == Dzcante020l080::OPERATION_ENABLED);     
    bool bPlatformEnabled = (statusMotorFlw == Dzcante020l080::OPERATION_ENABLED) && (statusMotorFrw == Dzcante020l080::OPERATION_ENABLED)
      && (statusMotorBlw == Dzcante020l080::OPERATION_ENABLED) && (statusMotorBrw == Dzcante020l080::OPERATION_ENABLED);
    
    if(bPlatformEnabled && bScissorEnabled){
        SwitchToState(READY_STATE);
        return;
        }

    return;
}

/*!	\fn void Motors::ReadyState()
 *	\brief Actions performed on ReadyState
*/
void Motors::ReadyState(){
    States stateMotorFlw, stateMotorBlw, stateMotorFrw, stateMotorBrw,  stateMotorScissor=INIT_STATE;
    Dzcante020l080::DriveStatus statusMotorFlw, statusMotorBlw, statusMotorFrw, statusMotorBrw, statusMotorScissor=Dzcante020l080::UNKNOWN;
    
    stateMotorFlw = motorFlw->GetState();
    stateMotorBlw = motorBlw->GetState();
    stateMotorFrw = motorFrw->GetState();
    stateMotorBrw = motorBrw->GetState();
    if (motorScissor!=NULL) stateMotorScissor = motorScissor->GetState();
    statusMotorFlw = motorFlw->GetStatus(); 
    statusMotorBlw = motorBlw->GetStatus();
    statusMotorFrw = motorFrw->GetStatus();
    statusMotorBrw = motorBrw->GetStatus();
	if (motorScissor!=NULL) statusMotorScissor = motorScissor->GetStatus();

    // Transitions 
    // Transition -> Emergency
    if(stateMotorFlw == EMERGENCY_STATE || stateMotorFrw == EMERGENCY_STATE 
       || stateMotorBlw == EMERGENCY_STATE || stateMotorBrw ==EMERGENCY_STATE || stateMotorScissor==EMERGENCY_STATE ){
        SwitchToState(EMERGENCY_STATE);
		ROS_ERROR("Motors::ReadyState switch to Emergency");
        SetDesiredSpeed(0.0, 0.0, 0.0, 0.0);  // 
        SetMotorValues();
        return;
        }

    // Transition -> Emergency
    if( statusMotorFlw == Dzcante020l080::FAULT || statusMotorFrw == Dzcante020l080::FAULT
       || statusMotorBlw == Dzcante020l080::FAULT ||  statusMotorBrw == Dzcante020l080::FAULT || statusMotorScissor == Dzcante020l080::FAULT ){
        SetDesiredSpeed(0.0, 0.0, 0.0, 0.0);
        SetMotorValues();
        SwitchToState(EMERGENCY_STATE);
		if (statusMotorFlw == Dzcante020l080::FAULT) ROS_ERROR("Motors::ReadyState detected FAULT in FLW motor");
		if (statusMotorFrw == Dzcante020l080::FAULT) ROS_ERROR("Motors::ReadyState detected FAULT in FRW motor");
		if (statusMotorBlw == Dzcante020l080::FAULT) ROS_ERROR("Motors::ReadyState detected FAULT in BLW motor");
		if (statusMotorBrw == Dzcante020l080::FAULT) ROS_ERROR("Motors::ReadyState detected FAULT in BRW motor");
		if (statusMotorScissor == Dzcante020l080::FAULT) ROS_ERROR("Motors::ReadyState detected FAULT in SCISSOR motor");
		// May detect them not synchronous and switch to other state before showing all the messages.
        return;
        }


    // TRANSITIONS TO INIT
    if(stateMotorFlw == INIT_STATE || stateMotorFrw == INIT_STATE 
       || stateMotorBlw == INIT_STATE || stateMotorBrw == INIT_STATE || ((motorScissor!=NULL)&&(stateMotorScissor==INIT_STATE)) ){
        SetDesiredSpeed(0.0, 0.0, 0.0, 0.0);
        SetMotorValues();
        SwitchToState(INIT_STATE);
		ROS_ERROR("Motors::ReadyState switch to Init");
        return;
        }

    // TRANSITIONS TO STANDBY
    if(statusMotorFlw == Dzcante020l080::QUICK_STOP || statusMotorFrw == Dzcante020l080::QUICK_STOP 
       || statusMotorBlw == Dzcante020l080::QUICK_STOP || statusMotorBrw == Dzcante020l080::QUICK_STOP || statusMotorScissor == Dzcante020l080::QUICK_STOP){
        SetDesiredSpeed(0.0, 0.0, 0.0, 0.0);
        SetMotorValues();
		DisableMotors();
        SwitchToState(STANDBY_STATE);
		ROS_ERROR("Motors::ReadyState switch to Standby");
        return;
        }
    

    // LOG If the drivers are not in OPERATION_ENABLED
    if(statusMotorFlw != Dzcante020l080::OPERATION_ENABLED){
        ROS_INFO( "Motor FLW (ID = %d) on %s status", motorFlw->GetCanId(), motorFlw->GetStatusString());
        }
    if(statusMotorFrw != Dzcante020l080::OPERATION_ENABLED){
        ROS_INFO( "Motor FRW (ID = %d) on %s status", motorFrw->GetCanId(), motorFrw->GetStatusString());
        }
    if(statusMotorBlw != Dzcante020l080::OPERATION_ENABLED){
        ROS_INFO( "Motor BLW (ID = %d) on %s status", motorBlw->GetCanId(), motorBlw->GetStatusString());
        }
    if(statusMotorBrw != Dzcante020l080::OPERATION_ENABLED){
        ROS_INFO( "Motor BRW (ID = %d) on %s status", motorBrw->GetCanId(), motorBrw->GetStatusString());
        }
	if ((motorScissor!=NULL) && (statusMotorScissor != Dzcante020l080::OPERATION_ENABLED)) {
		if (motorScissor!=NULL) ROS_INFO( "Motor Scissor (ID = %d) on %s status", motorScissor->GetCanId(), motorScissor->GetStatusString());
		}

    //
    // ACTIONS
    //
    // Homing
    if (motorScissor!=NULL) {
		if ((!bHomed)&&(iHoming!=0)) {
			switch (iHoming) {
				case 0: 
					break;
				case 1: // Start motion in negative direction
					//  dDesiredScissorSpeed = -0.3;   // commented to force manual home
					iHoming = 2;
					break;
				case 2: // Found negative limit switch
					// dDesiredScissorSpeed = -0.3;   // commented to force manual home
				
					if ((DIGITAL_INPUT_DOWN & GetMotorScissorDigitalInputs())!=0)  {
						iHoming = 0;
						iScissorOriginPosition = motorScissor->GetMotorPosition(); 
						bHomed = true;
					}
				break;
			}
		}
	}
        
    // Position mode
    if ((dDesiredPosition >=0) && (bHomed)) {
		double tolerance = 5000.0;
		double sat_speed = 0.3;
		double Kp =1.0 / 100000;
		double ep = dDesiredPosition - GetMotorScissorPosition();
		
		double v_ref = Kp * ep;
		// Saturation 
		if (v_ref > sat_speed) v_ref = sat_speed;
		if (v_ref < -sat_speed) v_ref = -sat_speed;
		dDesiredScissorSpeed = v_ref;
		
		// End state condition 
		if ((GetMotorScissorPosition()<(dDesiredPosition+tolerance)) && (GetMotorScissorPosition()>(dDesiredPosition-tolerance))) {
			dDesiredScissorSpeed = 0;
			dDesiredPosition = -1;
			}		
		}
		
    SetMotorValues();
}

/*!	\fn void Component::EmergencyState()
 *	\brief Actions performed on emergency state
*/
void Motors::EmergencyState(){

    States stateMotorFlw, stateMotorFrw, stateMotorBlw, stateMotorBrw, stateMotorScissor=INIT_STATE;;
    Dzcante020l080::DriveStatus statusMotorFlw, statusMotorBlw, statusMotorFrw, statusMotorBrw, statusMotorScissor=Dzcante020l080::UNKNOWN;

    bool bStatusError = false;
    
    bHomed = false;
    iHoming = true;

    stateMotorFlw = motorFlw->GetState();
    stateMotorBlw = motorBlw->GetState();
    stateMotorFrw = motorFrw->GetState();
    stateMotorBrw = motorBrw->GetState();
	if (motorScissor!=NULL) stateMotorScissor = motorScissor->GetState();
    statusMotorFlw = motorFlw->GetStatus(); 
    statusMotorBlw = motorBlw->GetStatus();
    statusMotorFrw = motorFrw->GetStatus();
    statusMotorBrw = motorBrw->GetStatus();
	if (motorScissor!=NULL) statusMotorScissor = motorScissor->GetStatus();    
    // STATE Transitions?
    // TRANSITIONS FROM EMERGENCY
    if( (stateMotorFlw != EMERGENCY_STATE) &&  
        (stateMotorFrw != EMERGENCY_STATE) && 
        (stateMotorBlw != EMERGENCY_STATE) && 
        (stateMotorBrw != EMERGENCY_STATE) && 
        (stateMotorScissor != EMERGENCY_STATE)) {			

		// Show internal drive status
		if( statusMotorFlw == Dzcante020l080::FAULT || 
		    statusMotorFrw == Dzcante020l080::FAULT || 
		    statusMotorBlw == Dzcante020l080::FAULT || 
		    statusMotorBrw == Dzcante020l080::FAULT) {
		     bStatusError = true;		     
		     }
		if (motorScissor!=NULL){     
			if( statusMotorScissor == Dzcante020l080::FAULT ) {
				bStatusError = true;				
				}
		}

		if(!bStatusError){	// Transitions only if there aren't status errors
			// TRANSITIONS TO INIT
			if(stateMotorFlw == INIT_STATE || 
			   stateMotorFrw == INIT_STATE || 
               stateMotorBlw == INIT_STATE || 
               stateMotorBrw == INIT_STATE || 
               ((motorScissor!=NULL) && (stateMotorScissor==INIT_STATE))) {
			    SwitchToState(INIT_STATE);			    
			    return;
			   }
			   
			// TRANSITIONS TO STANDBY
			if(statusMotorFlw == Dzcante020l080::QUICK_STOP || 
			   statusMotorBlw == Dzcante020l080::QUICK_STOP || 
			   statusMotorFrw == Dzcante020l080::QUICK_STOP || 
			   statusMotorBrw == Dzcante020l080::QUICK_STOP || 
			   statusMotorScissor == Dzcante020l080::QUICK_STOP){
				SwitchToState(STANDBY_STATE);
			//	motorFlw->SetLogDriveStatus(false);
			//	motorFrw->SetLogDriveStatus(false);
			//	motorBlw->SetLogDriveStatus(false);
			//	motorBrw->SetLogDriveStatus(false);				
				return;
			    }
			
			// TRANSITIONS TO READY
			bool bScissorEnabled = true;
			if (motorScissor!=NULL) {
				bScissorEnabled = (statusMotorScissor == Dzcante020l080::OPERATION_ENABLED);				
			}     
			bool bPlatformEnabled = (statusMotorFlw == Dzcante020l080::OPERATION_ENABLED) && 
			                        (statusMotorFrw == Dzcante020l080::OPERATION_ENABLED) && 
			                        (statusMotorBlw == Dzcante020l080::OPERATION_ENABLED) && 
			                        (statusMotorBrw == Dzcante020l080::OPERATION_ENABLED);
			
			if(bPlatformEnabled && bScissorEnabled){
				SwitchToState(READY_STATE);				
				return;
				}
     		}
	}
     // Actions
     SetDesiredSpeed(0.0, 0.0, 0.0, 0.0);
     SetMotorValues();
}

/*!	\fn void Component::FailureState()
 *	\brief Actions performed on failure state
*/
void Motors::FailureState(){
	struct timespec tNow;
	long diff;

	clock_gettime(threadData.pthreadPar.clock, &tNow);

	diff = calcdiff(tNow, tRecovery);

	if(diff > 5000000){
		ROS_INFO("Motors::FailureState: Trying to recover from the error");
		if(canDev->ShutDown() != ERROR){
			if(canDev->Setup() == OK){
				SwitchToState(EMERGENCY_STATE);
				ROS_ERROR("Motors::FailureState: CAN Recovered successfully");
			}else
				ROS_ERROR("Motors::FailureState: Error on CAN setup");
		}else
			ROS_ERROR("Motors::FailureState: Error on CAN shutdown");

		tRecovery = tNow;
	}
}

/*!	\fn void Component::AllState()
 *	\brief Actions performed on all states
*/
void Motors::AllState(){
	static int counter = 0, max_counts = 2*threadData.dDesiredHz;
        if(iState != FAILURE_STATE){
		if(counter >= max_counts){
			counter = 0;
		}else
			counter++;

		if(ReadCANMessages() == ERROR) {	// Read CAN messages
            SwitchToState(FAILURE_STATE);
			}

		// Syncronize 
		motorFlw->Syncronize();		// Sends CAN synchronize message
		//motorBlw->Syncronize();		// Sends CAN synchronize message
		//motorFrw->Syncronize();		// Sends CAN synchronize message
		//motorBrw->Syncronize();		// Sends CAN synchronize message
		//if (motorScissor!=NULL) motorScissor->Syncronize();
		
		if(bOdometry) UpdateOdometry();
		
		// TEST: Logs the number of read / sent CAN messages
		//ROS_INFO( "Motors::AllState: CAN msgs sent = %d, read = %d", canDev->GetSentMsgs(), canDev->GetReadMsgs());
        }
	// Checks and updates the alarms vector
	ErrorCheck();
}

/*!	\fn  ReturnValue Motors::SetDesiredSpeed(double linear, double angular){
 *	\brief  Sets the linear speed of the motor in (m/s) and angular speed in (deg/s)
*/
ReturnValue Motors::SetDesiredSpeed(double linearX, double linearY, double angular, double linearZ){
	
	if(iState != READY_STATE){	// Only accepts modifications on READY STATE 		
		return ERROR;
		}

        if( linearX < -dMaxLinearVelocity ) 
		linearX = -dMaxLinearVelocity;
	else if (linearX > dMaxLinearVelocity)
		linearX = dMaxLinearVelocity;
	dDesiredLinearSpeedX = linearX;

	//if (linearX == dMaxLinearVelocity) ROS_INFO("Motors:: MAX_LINEAR ");
	//if (linearX == -dMaxLinearVelocity) ROS_INFO("Motors:: -MAX_LINEAR ");

        if( linearY < -dMaxLinearVelocity )
                linearY = -dMaxLinearVelocity;
        else if (linearY > dMaxLinearVelocity)
                linearY = dMaxLinearVelocity;
        dDesiredLinearSpeedY = linearY;
  
        if(angular < -dMaxAngularVelocity)
		angular = -dMaxAngularVelocity;
	else if (angular > dMaxAngularVelocity)
		angular = dMaxAngularVelocity;
	dDesiredAngularSpeed = angular;

    // TBD Limit scissor speed
    dDesiredScissorSpeed = linearZ;
	
	//ROS_INFO("Motors::SetDesiredSpeed: linear = %lf, angular = %lf", dDesiredLinearSpeed, dDesiredAngularSpeed);
	return OK;
}

/*!	\fn ReturnValue Motors::SetDesiredPosition(double position)
 *	\brief	Sets the position of the linear motor (milimeters ???)
*/
ReturnValue Motors::SetDesiredPosition(double position){
	
	if(iState != READY_STATE){	// Only accepts modifications on READY STATE
		return ERROR;
		}
	
	if (!bHomed) return ERROR;

         //To control the height (and not the counts):
         //h(l) = sqrt( 571^2 - (353.8 + l)^2) 
         //h(0) = 139.09   mmiHoming = 1;
         //h(200) = 448.18 mm

	if( position < 0){
		dDesiredPosition = 0;
		ROS_INFO("Motors::SetDesiredPosition: - Min position reachead");
	}else if ( position > 2295000 ) {
		dDesiredPosition = 2295000;
		ROS_INFO("Motors::SetDesiredPosition: + Max position reachead");
	} else
		dDesiredPosition = position;

	return OK;
}

/*!	\fn  void Motors::GetDesiredSpeeds( double* linear, double *angular)
 *	\brief Returns the value of the desired speed
*/
void Motors::GetDesiredSpeeds( double* linearX, double* linearY, double *angular, double *linearZ){
       
	*linearX = dDesiredLinearSpeedX;
    *linearY = dDesiredLinearSpeedY;
	*angular = dDesiredAngularSpeed;
	*linearZ = dDesiredScissorSpeed;
	return;
}

/*!	\fn double Motors::GetMotorSpeeds( double* flw, double* blw, double* frw, double* brw )
 *	\brief Returns the speeds 
*/
void Motors::GetMotorSpeeds( double* flw, double* blw, double* frw, double* brw, double* scissor ){

	*flw = motorFlw->GetMotorVelocity();
	*blw = motorBlw->GetMotorVelocity();
	*frw = motorFrw->GetMotorVelocity();
	*brw = motorBrw->GetMotorVelocity();
	if (motorScissor!=NULL) {
		*scissor = motorScissor->GetMotorVelocity();
	} else {
		*scissor=0;	
	}
	return; 
}

/*!	\fn double Motors::GetBattery()
 *	\brief	Gets the battery level
*/
double Motors::GetBattery(){
	return (motorFlw->GetBattery() + motorFrw->GetBattery() + motorBlw->GetBattery() + motorBrw->GetBattery())/4; 
}

/*! \fn double Motors::GetDCBusVoltage()
    \brief  Gets the voltage of the power supply
*/
double Motors::GetDCBusVoltage(){
   return motorFlw->GetDCBusVoltage();
}

/*!	\fn char *Motors::GetMotorFlwStateString()
 * 	\brief Gets the state of the motor FLW
*/
char *Motors::GetMotorFlwStateString(){
	return motorFlw->GetStateString();
}

/*!	\fn char *Motors::GetMotorBlwStateString()
 * 	\brief Gets the state of the motor BLW
*/
char *Motors::GetMotorBlwStateString(){
	return motorBlw->GetStateString();
}
/*!	\fn char *Motors::GetMotorFrwStateString()
 * 	\brief Gets the state of the motor FRW
*/
char *Motors::GetMotorFrwStateString(){
	return motorFrw->GetStateString();
}
/*!	\fn char *Motors::GetMotorBrwStateString()
 * 	\brief Gets the state of the motor BRW
*/
char *Motors::GetMotorBrwStateString(){
	return motorBrw->GetStateString();
}

/*!     \fn char *Motors::GetMotorScissorStateString()
 *      \brief Gets the state of the motor Scissor
*/
char *Motors::GetMotorScissorStateString(){
        if (motorScissor!=NULL) return motorScissor->GetStateString();
        else return (char *)"UNKNOWN";
}

/*!	\fn char *Motors::GetMotorFlwStatusString()
 * 	\brief Gets the status of the motor FLW
*/
char *Motors::GetMotorFlwStatusString(){
	return motorFlw->GetStatusString();
}

/*!	\fn char *Motors::GetMotorBlwStatusString()
 * 	\brief Gets the status of the motor BLW
*/
char *Motors::GetMotorBlwStatusString(){
	return motorBlw->GetStatusString();
}

/*!	\fn char *Motors::GetMotorFrwStatusString()
 * 	\brief Gets the status of the motor FRW
*/
char *Motors::GetMotorFrwStatusString(){
	return motorFrw->GetStatusString();
}

/*!	\fn char *Motors::GetMotorBrwStatusString()
 * 	\brief Gets the status of the motor BRW
*/
char *Motors::GetMotorBrwStatusString(){
	return motorBrw->GetStatusString();
}

/*! \fn char *Motors::GetMotorScissorStatusString()
 *  \brief Gets the status of the motor Scissor
*/
char *Motors::GetMotorScissorStatusString(){
	if (motorScissor!=NULL) return motorScissor->GetStatusString();
		else return (char *)"NONE";
}

/*!	\fn char *Motors::GetMotorFlwStatusFlagsString()
 * 	\brief Gets the status Flags of the motor FLW
*/
char *Motors::GetMotorFlwStatusFlagsString(){
	return motorFlw->GetStatusRegisterFlagsString();
}

/*!	\fn char *Motors::GetMotorBlwStatusFlagsString()
 * 	\brief Gets the status Flags of the motor BLW
*/
char *Motors::GetMotorBlwStatusFlagsString(){
	return motorBlw->GetStatusRegisterFlagsString();
}

/*!	\fn char *Motors::GetMotorFrwStatusFlagsString()
 * 	\brief Gets the status Flags of the motor FRW
*/
char *Motors::GetMotorFrwStatusFlagsString(){
	return motorFrw->GetStatusRegisterFlagsString();
}

/*!	\fn char *Motors::GetMotorBrwStatusWordString()
 * 	\brief Gets the status word of the motor BRW
*/
char *Motors::GetMotorBrwStatusFlagsString(){
	return motorBrw->GetStatusRegisterFlagsString();
}

/*!  \fn char *Motors::GetMotorScissorStatusWordString()
 *   \brief Gets the status word of the motor Scissor
*/
char *Motors::GetMotorScissorStatusFlagsString(){
    if (motorScissor!=NULL) return motorScissor->GetStatusRegisterFlagsString();
        else return (char *)"NONE";
}

/*!	\fn char *Motors::GetMotorFlwStatusWordString()
 * 	\brief Gets the status word of the motor FLW
*/
char *Motors::GetMotorFlwStatusWordString(){
	return motorFlw->GetStatusWordString();
}

/*!	\fn char *Motors::GetMotorBlwStatusWordString()
 * 	\brief Gets the status word of the motor BLW
*/
char *Motors::GetMotorBlwStatusWordString(){
	return motorBlw->GetStatusWordString();
}

/*!	\fn char *Motors::GetMotorFrwStatusWordString()
 * 	\brief Gets the status word of the motor FRW
*/
char *Motors::GetMotorFrwStatusWordString(){
	return motorFrw->GetStatusWordString();
}

/*!	\fn char *Motors::GetMotorBrwStatusWordString()
 * 	\brief Gets the status word of the motor BRW
*/
char *Motors::GetMotorBrwStatusWordString(){
	return motorBrw->GetStatusWordString();
}

/*!     \fn char *Motors::GetMotorScissorStatusWordString()
 *      \brief Gets the status word of the motor Scissor
*/
char *Motors::GetMotorScissorStatusWordString(){
        if (motorScissor!=NULL) return motorScissor->GetStatusWordString();
        else return (char *)"NONE";
}

/*!	\fn void Motors::SetMotorValues()
 *	\brief Sends the references to the motors
*/
void Motors::SetMotorValues(){

// TODO parameter to ROS PARAM
        // Wheel radius
        // double R = 0.125; 
        double frw1, flw2, blw3, brw4, fz1;
        double lab = KINEMATIC_PARAM_LA + KINEMATIC_PARAM_LB;
        static double frw=0.0, flw=0.0, blw=0.0, brw=0.0, fz=0.0;

	// Omniwheel driver configuration
        // double vx = dDesiredLinearSpeedX;
        // Latest driver configuration
        double vx = -dDesiredLinearSpeedX;
	double vy = dDesiredLinearSpeedY;
        double w = dDesiredAngularSpeed; 

	// frw = (1.0 / R) * (vx + vy +(la+lb)*w);  
        // Speed references in m/s
        frw1 = vx + vy + lab * w;
        flw2 = vx - vy - lab * w;
        blw3 = vx + vy - lab * w;
        brw4 = vx - vy + lab * w;

	// ROS_INFO("Desired speeds : vx=%5.2f vy=%5.2f w=%5.2f", vx, vy, w );
    // ROS_INFO("vx=%5.2f vy=%5.2f  frw flw blw brw = %5.2f %5.2f %5.2f %5.2f", vx, vy, frw1, flw2, blw3, brw4);

	double dIncSpeed = dAcceleration / dFreq; // desired_freq_; 

        // FORWARD RIGHT WHEEL
        if(frw1 > 0.0){
                double frw_new_incremented_speed = frw+dIncSpeed;

                if(frw1 > (frw_new_incremented_speed))
                        frw += dIncSpeed;
                else
                        frw = frw1;
        }else if(frw1 < 0.0){
                double frw_new_decremented_speed = frw-dIncSpeed;

                if(frw1 < (frw_new_decremented_speed))
                        frw -= dIncSpeed;
                else
                        frw = frw1;
        }else
                frw = 0.0;

      // FORWARD LEFT WHEEL
        if(flw2 > 0.0){
                double flw_new_incremented_speed = flw+dIncSpeed;

                if(flw2 > (flw_new_incremented_speed))
                        flw += dIncSpeed;
                else
                        flw = flw2;
        }else if(flw2 < 0.0){
                double flw_new_decremented_speed = flw-dIncSpeed;

                if(flw2 < (flw_new_decremented_speed))
                        flw -= dIncSpeed;
                else
                        flw = flw2;
        }else
                flw = 0.0;

        // BACKWARD RIGHT WHEEL
        if(brw4 > 0.0){
                double brw_new_incremented_speed = brw+dIncSpeed;

                if(brw4 > (brw_new_incremented_speed))
                        brw += dIncSpeed;
                else
                        brw = brw4;
        }else if(brw4 < 0.0){
                double brw_new_decremented_speed = brw-dIncSpeed;

                if(brw4 < (brw_new_decremented_speed))
                        brw -= dIncSpeed;
                else
                        brw = brw4;
        }else
                brw = 0;

        // BACKWARD LEFT WHEEL
        if(blw3 > 0.0){
                double blw_new_incremented_speed = blw+dIncSpeed;

                if(blw3 > (blw_new_incremented_speed))
                        blw += dIncSpeed;
                else
                        blw = blw3;
        }else if(blw3 < 0.0){
                double blw_new_decremented_speed = blw-dIncSpeed;

                if(blw3 < (blw_new_decremented_speed))
                        blw -= dIncSpeed;
                else
                        blw = blw3;
        }else
                blw = 0;


	// ROS_INFO("Motor velocities : flw=%5.2f blw=%5.2f frw=%5.2f brw=%5.2f", -flw, -blw, frw, brw );

        if (motorFlw->SetMotorVelocity(-flw)!=OK) 
                ROS_ERROR("Motors::SetMotorValues: Error setting the FLW velocity");
        if (motorBlw->SetMotorVelocity(-blw)!=OK) 
                ROS_ERROR("Motors::SetMotorValues: Error setting the BLW velocity");
        if (motorFrw->SetMotorVelocity(frw)!=OK) 
                ROS_ERROR("Motors::SetMotorValues: Error setting the FRW velocity");
        if (motorBrw->SetMotorVelocity(brw)!=OK) 
                ROS_ERROR("Motors::SetMotorValues: Error setting the BRW velocity");

	if (motorScissor!=NULL) {
		double dIncSpeedZ = 200.0 / 50.0; // depend on desired_freq_
		   fz1 = dDesiredScissorSpeed * 400.0;  // MAX_SPEED_DRIVER_REF_UNITS 
		   if (fz1 > (fz + dIncSpeedZ)) fz +=dIncSpeedZ;
		   if (fz1 < (fz - dIncSpeedZ)) fz -=dIncSpeedZ;
		   if ((fz1 > -dIncSpeedZ) && (fz1 < dIncSpeedZ) && (fz1 > -dIncSpeedZ ) && (fz1 < dIncSpeedZ)) fz = 0.0;
		   if (fz > DEFAULT_MAX_SCISSOR_VELOCITY) fz = DEFAULT_MAX_SCISSOR_VELOCITY;
		   if (fz < -DEFAULT_MAX_SCISSOR_VELOCITY) fz = -DEFAULT_MAX_SCISSOR_VELOCITY;		 
		   
		   if (bHomed) {
                      // If homed, speed is limited near the limits
                      if ((GetMotorScissorPosition() < 100000)||(GetMotorScissorPosition() > 2100000)) {
			if (fz > (DEFAULT_MAX_SCISSOR_VELOCITY / 10.0)) fz = DEFAULT_MAX_SCISSOR_VELOCITY / 10.0;
			if (fz < (-DEFAULT_MAX_SCISSOR_VELOCITY / 10.0)) fz = -DEFAULT_MAX_SCISSOR_VELOCITY / 10.0;
			}
                      }
		   else { 
                      // Before homing speed is always limited 
                      if (fz > (DEFAULT_MAX_SCISSOR_VELOCITY * 0.3)) fz = DEFAULT_MAX_SCISSOR_VELOCITY * 0.3;
                      if (fz < (-DEFAULT_MAX_SCISSOR_VELOCITY * 0.3)) fz = -DEFAULT_MAX_SCISSOR_VELOCITY * 0.3;
		      }
 		   
		   if (motorScissor->SetMotorVelocity( fz )!=OK)  
		  	ROS_ERROR("Motors::SetMotorValues: Error setting the Scissor reference");
                   
		}
		
	//ROS_INFO( "Setting velocity to left:%.3lf  right:%.3lf", v_left_mps, v_right_mps);
}

//! Puts the drivers on QuickStopState
void Motors::DisableMotors(){
    motorFlw->SetDesiredStatus(Dzcante020l080::QUICK_STOP);
    motorBlw->SetDesiredStatus(Dzcante020l080::QUICK_STOP);
    motorFrw->SetDesiredStatus(Dzcante020l080::QUICK_STOP);
    motorBrw->SetDesiredStatus(Dzcante020l080::QUICK_STOP);
	if (motorScissor!=NULL) motorScissor->SetDesiredStatus(Dzcante020l080::QUICK_STOP);
    // ROS_INFO("Motors::DisableMotors"); //TEST
}

/*!	\fn void Motors::EnableMotors()
 *	\brief Puts the drivers on QuickStopState
*/
void Motors::EnableMotors(){
	// Under some circumstances motors may not be enabled
	motorFlw->SetDesiredStatus(Dzcante020l080::OPERATION_ENABLED);
	motorBlw->SetDesiredStatus(Dzcante020l080::OPERATION_ENABLED);
	motorFrw->SetDesiredStatus(Dzcante020l080::OPERATION_ENABLED);
	motorBrw->SetDesiredStatus(Dzcante020l080::OPERATION_ENABLED);
	if (motorScissor!=NULL) motorScissor->SetDesiredStatus(Dzcante020l080::OPERATION_ENABLED);
}


/*!	\fn ReturnValue Motors::SetDigitalOutput(int output, bool value)
 *	\brief	Sets the requested digital output to the given value
*/
ReturnValue Motors::SetDigitalOutput(int output, bool value){
	
	// Set the variable that will be used by each MotorDrive in its ReadSDOMessagesThread 
	if ((output>=1)&&(output<=3)) 
		motorFlw->SetDigitalOutputs( (unsigned int) output , value );     // 1
	if ((output>=4)&&(output<=6))
		motorBlw->SetDigitalOutputs( (unsigned int) (output-3), value );  // 2
	if ((output>=7)&&(output<=9))
	        motorFrw->SetDigitalOutputs( (unsigned int) (output-6), value );  // 3 
	if ((output>=10)&&(output<=12))
	        motorBrw->SetDigitalOutputs( (unsigned int) (output-9), value );  // 4
		
	// motorFlw->SetDigitalOutputs( 0x03 );	
}

/*!	\fn int Motors::GetMotorCounts(long* flw, long* blw, long* frw, long* brw)
 * 	\brief Gets the position (on counts) of the motor FLW
 * 	\return Counts number of motor position
*/
void Motors::GetMotorCounts(long* flw, long* blw, long* frw, long* brw) {

// TODO : convert from speed counts
//	*flw = motorFlw->GetMotorCounts();
//	*blw = motorBlw->GetMotorCounts();
//	*frw = motorFrw->GetMotorCounts();
//	*brw = motorBrw->GetMotorCounts();
       *flw = 0; *blw = 0; *frw = 0; *brw = 0;
}


/*!	\fn bool Motors::IsHomed()
 * 	\return true if homing is complete
 *  \return false if homing is not complete
*/
bool Motors::IsHomed(){
  if (motorScissor!=NULL) return bHomed;
	else return false;
}

/*!	\fn ReturnValue Motors::Home()
 *  \brief  Initializes the homing procedure
*/
ReturnValue Motors::Home(){
	
	if (motorScissor==NULL) return ERROR;
	else if(iState != READY_STATE){
		ROS_ERROR("Motors::Home: Home has to be done in READY_STATE");
		return ERROR;
		}
		
	//if ((!bHomed)&&(iHoming==0)) {
	if (!bHomed) {
		iHoming = 1;
		}
	return OK;
}

/*!	\fn void Motors::ErrorCheck()
 *  \brief Checks the status and updates the alarm flag vector
*/
void Motors::ErrorCheck(){

    States stateMotorFlw,  stateMotorBlw,  stateMotorFrw, stateMotorBrw;
    Dzcante020l080::DriveStatus statusMotorFlw, statusMotorBlw, statusMotorFrw, statusMotorBrw;

    stateMotorFlw = motorFlw->GetState(); 
    stateMotorBlw = motorBlw->GetState(); 
    stateMotorFrw = motorFrw->GetState();
    stateMotorBrw = motorBrw->GetState();
    statusMotorFlw = motorFlw->GetStatus();
    statusMotorBlw = motorBlw->GetStatus(); 
    statusMotorFrw = motorFrw->GetStatus(); 
    statusMotorBrw = motorBrw->GetStatus();  

    // Checks CAN communication STATUS
    if(stateMotorFlw == EMERGENCY_STATE)
	vAlarms[DRIVER_ALARM_COMM_FLW] = true;
    else
	vAlarms[DRIVER_ALARM_COMM_FLW] = false;
    if(stateMotorBlw == EMERGENCY_STATE)
	vAlarms[DRIVER_ALARM_COMM_BLW] = true;
    else
	vAlarms[DRIVER_ALARM_COMM_BLW] = false;

    if(stateMotorFrw == EMERGENCY_STATE)
	vAlarms[DRIVER_ALARM_COMM_FRW] = true;
    else
	vAlarms[DRIVER_ALARM_COMM_FRW] = false;

    if(stateMotorBrw == EMERGENCY_STATE)
	vAlarms[DRIVER_ALARM_COMM_BRW] = true;
    else
	vAlarms[DRIVER_ALARM_COMM_BRW] = false;

    // Checks MotorDrives status
    if( statusMotorFlw == Dzcante020l080::FAULT )
	vAlarms[DRIVER_ALARM_STATUS_FLW] = true;
    else
	vAlarms[DRIVER_ALARM_STATUS_FLW] = false;

    if( statusMotorBlw == Dzcante020l080::FAULT )
	vAlarms[DRIVER_ALARM_STATUS_BLW] = true;
    else
	vAlarms[DRIVER_ALARM_STATUS_BLW] = false;

    if( statusMotorFrw == Dzcante020l080::FAULT )
	vAlarms[DRIVER_ALARM_STATUS_FRW] = true;
    else
	vAlarms[DRIVER_ALARM_STATUS_FRW] = false;

    if( statusMotorBrw == Dzcante020l080::FAULT )
	vAlarms[DRIVER_ALARM_STATUS_BRW] = true;
    else
	vAlarms[DRIVER_ALARM_STATUS_BRW] = false;

    // Checks Error CAN
    if(iState == FAILURE_STATE)
	vAlarms[DRIVER_ALARM_CAN] = true;
    else
	vAlarms[DRIVER_ALARM_CAN] = false;

    vAlarms[DRIVER_ALARM_EMERGENCY_STOP] = false;
    // Checks if the emergency stop has been pressed
    // if(!GetInput(I_EMERGENCY_STOP))	// Inverted input
    //    vAlarms[DRIVER_ALARM_EMERGENCY_STOP] = true;
    // else
    //    vAlarms[DRIVER_ALARM_EMERGENCY_STOP] = false;
    //
}

/*!	\fn vector<bool> Motors::GetAlarms
 *  \brief Gets the current state of alarms
*/
vector<bool> Motors::GetAlarms(){
	return vAlarms;
}

/*!	\fn void Motors::ModifyOdometry(Odometry odom)
 *  \brief Sets new odometry values
*/
void Motors::ModifyOdometry(Odometry odom){
    pthread_mutex_lock(&mutexOdometry);
        odomPosition = odom;
    pthread_mutex_unlock(&mutexOdometry);
}

/*!	\fn void Motors::ResetOdometry()
 *  \brief Resets internal odometry
*/
void Motors::ResetOdometry(){
    pthread_mutex_lock(&mutexOdometry);
        odomPosition.px = odomPosition.py = odomPosition.pa = odomPosition.v = odomPosition.w = 0.0;
    pthread_mutex_unlock(&mutexOdometry);
}

/*! \fn void Motors::SetOdometryAngle( double yaw )
*   \brief Set Odometry Angle
*/
void Motors::SetOdometryAngle( double yaw ){
    pthread_mutex_lock(&mutexOdometry);
        bYawSensor = true;
        odomPosition.pa = yaw;
    pthread_mutex_unlock(&mutexOdometry);
}

/*!	\fn Odometry Motors::GetOdometry()
 *  \brief Returns the current position from odometry
*/
Odometry Motors::GetOdometry(){
	Odometry aux;

	pthread_mutex_lock(&mutexOdometry);
		aux = odomPosition;
	pthread_mutex_unlock(&mutexOdometry);

    return aux;
}


/*!	\fn void Motors::UpdateOdometry()
 *	\brief Updates the values of the odometry
 *  Ackerman's odometry calculation (using motor speed and position of the motor direction)
*/
void Motors::UpdateOdometry(){
	Odometry odomAux;
        double fSamplePeriod;
	double linearSpeedMps, angularSpeedRads;
	double v_left_mps, v_right_mps;
	double fDistanceBetweenWheels = 0.75;  // Equivalent skid-steering distance
	double lab = KINEMATIC_PARAM_LA + KINEMATIC_PARAM_LB; 
  
    static double  a1[100], a2[100],a3[100],a4[100];
	pthread_mutex_lock(&mutexOdometry);
	
	if (bOmni){
		
        odomAux = odomPosition;

        // Real sampling period
        fSamplePeriod = 1.0 / threadData.dDesiredHz; //dRealHz;
        double frw1 = -motorFrw->GetMotorVelocity();  // "-"
        double flw2 = motorFlw->GetMotorVelocity();
        double blw3 = motorBlw->GetMotorVelocity();
        double brw4 = -motorBrw->GetMotorVelocity();
              
        //ROS_INFO("UpdateOdometry : 1=%5.2f 2=%5.2f 3=%5.2f 4=%5.2f", s1, flw2, blw3, brw4);
               
 
        // Avoid to integrate motor noise
        if(fabs(frw1) < 0.0001) frw1 = 0.0;
        if(fabs(flw2) < 0.0001) flw2 = 0.0;
        if(fabs(blw3) < 0.0001) blw3 = 0.0;
        if(fabs(brw4) < 0.0001) brw4 = 0.0;

        double R = 1.0;  // speeds already in [m/s] 
        double vx = (R / 4.0) * (frw1 + flw2 + blw3 + brw4);
	    double vy = (R / 4.0) * (frw1 - flw2 + blw3 - brw4);
	    double wr = (R / (4.0 * lab)) * (frw1 - flw2 - blw3 + brw4);
		
		// Compute Odometry
		angularSpeedRads = wr;
                odomAux.w = angularSpeedRads;
                linearSpeedMps = sqrt(vx*vx + vy*vy);
                odomAux.v = linearSpeedMps;
		
		if(!bYawSensor){
			odomAux.pa += odomAux.w * fSamplePeriod;
			radnorm(&odomAux.pa);

			// Velocities
			odomAux.vx = vx*cos(odomAux.pa) - vy*sin(odomAux.pa);
			odomAux.vy = vy*cos(odomAux.pa) + vx*sin(odomAux.pa);
		}else{
			// Velocities		
			odomAux.vx = vx*cos(odomAux.pa) - vy*sin(odomPosition.pa);
			odomAux.vy = vy*cos(odomAux.pa) + vx*sin(odomPosition.pa);
		}

                // Positions
		odomAux.px += odomAux.vx * fSamplePeriod;
		odomAux.py += odomAux.vy * fSamplePeriod;
		// Updates the value
	   	odomPosition = odomAux;
	 } else {
		
        odomAux = odomPosition;

		// Real sampling period
		fSamplePeriod = 1.0 / threadData.dDesiredHz; //dRealHz;
		v_left_mps =  (motorFlw->GetMotorVelocity() + motorBlw->GetMotorVelocity()) / 2.0;
		v_right_mps = -(motorFrw->GetMotorVelocity() + motorBrw->GetMotorVelocity()) / 2.0;

		// Avoid to integrate motor noise
		if(fabs(v_left_mps) < 0.001)
			v_left_mps = 0.0;
		if(fabs(v_right_mps) < 0.001)
			v_right_mps = 0.0;

		linearSpeedMps = (v_right_mps + v_left_mps) / 2.0;                         // m/s
		angularSpeedRads = (v_right_mps - v_left_mps) / fDistanceBetweenWheels;    //rad/s

		// Compute Odometry
		odomAux.w = angularSpeedRads;
		odomAux.v = linearSpeedMps;
		
		if(!bYawSensor){
			odomAux.pa += odomAux.w * fSamplePeriod;
			radnorm(&odomAux.pa);
			odomAux.vx = odomAux.v * cos(odomAux.pa);
			odomAux.vy = odomAux.v * sin(odomAux.pa);
		}else{
			// Velocities		
			odomAux.vx = odomAux.v * cos(odomPosition.pa); 
			odomAux.vy = odomAux.v * sin(odomPosition.pa);
		}
		
		//ROS_INFO("vLeft=%5.5f  vRight=%5.5f, w = %5.3f, pa = %5.3f, period = %5.3f secs", v_left_mps, v_right_mps, angularSpeedRads*180/Pi, odomAux.pa*180/Pi, fSamplePeriod);

		// Positions
		odomAux.px += odomAux.vx * fSamplePeriod;
		odomAux.py += odomAux.vy  * fSamplePeriod;
		// Updates the value
	   	odomPosition = odomAux;        
    }
    pthread_mutex_unlock(&mutexOdometry);
}

/*!	\fn void Motors::SetWheelDiameter(double diameter) 
 *	\brief Sets a new value for the diameter
*/
void Motors::SetWheelDiameter(double diameter){
	motorFlw->SetWheelDiameter(diameter);
	motorBlw->SetWheelDiameter(diameter);
	motorFrw->SetWheelDiameter(diameter);
	motorBrw->SetWheelDiameter(diameter);
	dRpmToMps = (diameter * Pi) / 60.0;
}

/*!	\fn double Motors::GetWheelDiameter()
 *	\brief Gets the value of the diameter
*/
double Motors::GetWheelDiameter(){
	return motorFlw->GetWheelDiameter();
}

/*!	\fn void Motors::GetConsumedCurrent(double *current_flw, double *current_blw, double *current_frw, double *current_brw )
 *	\brief Gets the current consumed current by the motors
*/
void Motors::GetConsumedCurrent(double *current_flw, double *current_blw, double *current_frw, double *current_brw ){
	*current_flw = motorFlw->GetCurrent();
	*current_blw = motorBlw->GetCurrent();
	*current_frw = motorFrw->GetCurrent();
	*current_brw = motorBrw->GetCurrent();
}

/*!	\fn double Motors::GetMotorFlwUpdateRate()
 *	\brief Gets the current update rate of the direction motor 
*/
double Motors::GetMotorFlwUpdateRate(){
	return	motorFlw->GetUpdateRate();
}

/*!	\fn double Motors::GetMotorBlwUpdateRate()
 *	\brief Gets the current update rate of the traction motor 
*/
double Motors::GetMotorBlwUpdateRate(){
	return	motorBlw->GetUpdateRate(); 
}

/*!	\fn double Motors::GetMotorFrwUpdateRate()
 *	\brief Gets the current update rate of the direction motor 
*/
double Motors::GetMotorFrwUpdateRate(){
	return	motorFrw->GetUpdateRate();
}

/*!	\fn double Motors::GetMotorBrwUpdateRate()
 *	\brief Gets the current update rate of the traction motor 
*/
double Motors::GetMotorBrwUpdateRate(){
	return	motorBrw->GetUpdateRate(); 
}

/*! \fn char *MotorDrive::GetCommunicationStatusString()
 * Get communication status like a string
*/
char *Motors::GetCommunicationStatusString(){
	return motorFlw->GetCommunicationStatusString();
}

/*!	\fn double Motors::GetMotorScissorPosition()
 *	\brief Gets the current position of the scissor mechanism motor
*/
double Motors::GetMotorScissorPosition(){
	if (motorScissor==NULL) return 0.0;
	return	(motorScissor->GetMotorPosition() - iScissorOriginPosition); 
}

/*!	\fn unsigned int Motors::GetScissorDigitalInputs()
 *	\brief Gets the digital inputs of the scissor mechanism 
*/
unsigned int Motors::GetMotorScissorDigitalInputs(){
	if (motorScissor==NULL) return 0;
	return motorScissor->GetDigitalInputs();
}

/*!     \fn unsigned int Motors::GetMotorFlwDigitalInputs()
 *      \brief Gets the digital inputs of the FLW driver 
*/
unsigned int Motors::GetMotorFlwDigitalInputs(){
        return motorFlw->GetDigitalInputs();
}


/*!     \fn bool Motors::IsYawSensor()
 *      \brief Returns whether or not it is using the yaw sensor (gyro or imu) 
*/
bool Motors::IsYawSensor(){
	return bYawSensor;
}

/*!     \fn void Motors::SetYawSensor(bool value)
 *      \brief Enables/disables the use of the yaw sensor (gyro or imu)
*/
void Motors::SetYawSensor(bool value){
	bYawSensor = value;
}


/*!     \fn bool Motors::InMotion()
 *      \brief returns true if the robot is in motion, false otherwise
*/
bool Motors::InMotion()
{
	bool e_stop = ((this->GetMotorFlwDigitalInputs() & DIGITAL_INPUT_ESTOP)!=0);
    bool zero_speed_ref = (dDesiredLinearSpeedX == 0) && (dDesiredLinearSpeedY == 0) && (dDesiredAngularSpeed == 0);
    bool inMotion = (!e_stop && !zero_speed_ref);
    return inMotion;	
}

//! Change Kinematic Mode
void Motors::KinematicMode(bool OmniMode){
	ROS_INFO("Motors::KinematicMode:%d",OmniMode);
	pthread_mutex_lock(&mutexOdometry);
	bOmni=OmniMode;
	pthread_mutex_unlock(&mutexOdometry);
}

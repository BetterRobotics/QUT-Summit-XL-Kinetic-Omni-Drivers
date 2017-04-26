/*! \class dzcante020l080
 *  \file dzcante020l080.cc
 *	\author Robotnik Automation S.L.L
 *	\version 1.0
 *	\date 2012
 *  \brief Class to manage the communication with the driver dzcante-020l080
 * (C) 2012 Robotnik Automation, SLL
 *  All rights reserved.
 */

#include "summit_xl_controller/Dzcante020l080.h"

const int Dzcante020l080::RPDO1        = 0x180;
const int Dzcante020l080::RPDO1_MSB    = 0x01;
const int Dzcante020l080::RPDO21       = 0x280;
const int Dzcante020l080::RPDO21_MSB   = 0x02;
const int Dzcante020l080::RPDO22       = 0x280;
const int Dzcante020l080::RPDO22_MSB   = 0x02;

const int Dzcante020l080::TPDO1        = 0x4A0;
const int Dzcante020l080::TPDO1_MSB    = 0x04;
const int Dzcante020l080::TPDO3        = 0x300;
const int Dzcante020l080::TPDO3_MSB    = 0x03;
const int Dzcante020l080::TPDO4        = 0x320;
const int Dzcante020l080::TPDO4_MSB    = 0x03;
const int Dzcante020l080::TPDO21       = 0x400;
const int Dzcante020l080::TPDO21_MSB   = 0x04;
const int Dzcante020l080::TPDO22       = 0x3F0;
const int Dzcante020l080::TPDO22_MSB   = 0x03;
const int Dzcante020l080::TPDO25       = 0x480;
const int Dzcante020l080::TPDO25_MSB   = 0x04;
const int Dzcante020l080::TPDO26       = 0x4C0;
const int Dzcante020l080::TPDO26_MSB   = 0x04;


/*! \fn Dzcante020l080::Dzcante020l080(PCan *can_device)
 * Constructor
*/
Dzcante020l080::Dzcante020l080(PCan *can_device):Component(10.0){
    // Change the name to the name of the derived class
    sComponentName.assign("Dzcante020l080");
    canDev = can_device;
}

/*! \fn Dzcante020l080::~Dzcante020l080()
 * Destructor
*/
Dzcante020l080::~Dzcante020l080(){

}

/*! \fn ReturnValue Dzcante020l080::Setup()
 * Configures and initializes the component
 * \return OK
 * \return INITIALIZED if the component is already intialized
 * \return ERROR
*/
ReturnValue Dzcante020l080::Setup(){

	// Checks if has been initialized
	if(bInitialized){
	   ROS_ERROR( "%s::Setup: Already initialized",sComponentName.c_str() );
	   return INITIALIZED;
	}

	///////////////////////////////////////////////////
	// Setups CAN device							 //
	///////////////////////////////////////////////////
	if(canDev == NULL){
          ROS_ERROR("%s::Setup: can device points to null",sComponentName.c_str());
	  return ERROR;
    	}
    
	if(canDev->Setup() == ERROR){
	  ROS_ERROR("%s::Setup: Error in can device setup",sComponentName.c_str());
	  return ERROR;
	  }

	bInitialized = true;
	return OK;
}

/*! \fn ReturnValue Dzcante020l080::Send(byte can_id, CANMessage type, AccessMode mode ,int param = 0)
 * Sends a specific CAN message to the desired device
 * \param can_id as byte, CAN ID of the device
 * \param type as CANMessage, type of message (CAN object) accepted by the device
 * \param mode as AccessMode, defines access mode of the message (READ / WRITE)
 * \param param as int, optional parameter to send with the message
 * \return OK
 * \return ERROR
 * \return NOT_INITIALIZED if the component has not been initialized
*/

ReturnValue Dzcante020l080::Send(byte can_id, CANMessage type, AccessMode mode ,int param = 0){
    TPCANMsg msg;
    byte b1 = 0, b2 = 0, b3 = 0, b4 = 0;

    if(!bInitialized){
		ROS_ERROR("%s::Send: Impossible to send because of it's not initialized", sComponentName.c_str());
		return NOT_INITIALIZED;
	}

    msg.ID = 0x600 + can_id;
    msg.LEN = 0x08;         //Message size(8 bytes)
    msg.MSGTYPE = MSGTYPE_STANDARD;
    
    // Command
    if(mode == READ)
        msg.DATA[0]=0x40;       //Command -> 40h
    else
        msg.DATA[0]=0x22;       //Command -> 22h
    // CAN Object
    switch(type){
        case ENABLE_OP_MSG:
            msg.DATA[0]=0x22;
            msg.DATA[1]=0x40;       //Object Index(LSB)
            msg.DATA[2]=0x60;       //Object Index(MSB)
            msg.DATA[3]=0x00;       //Sub-Index
            msg.DATA[4]=0x0F;       //Byte 5 LSB
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8 MSB
        break;
        case RESET_MSG:
            msg.DATA[0]=0x22;
            msg.DATA[1]=0x40;       //Object Index(LSB)
            msg.DATA[2]=0x60;       //Object Index(MSB)
            msg.DATA[3]=0x00;       //Sub-Index
            msg.DATA[4]=0x80;       //Byte 5 LSB
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8 MSB
        break;
        case SHUTDOWN_MSG:
            msg.DATA[0]=0x22;
            msg.DATA[1]=0x40;       //Object Index(LSB)
            msg.DATA[2]=0x60;       //Object Index(MSB)
            msg.DATA[3]=0x00;       //Sub-Index
            msg.DATA[4]=0x06;       //Byte 5 LSB
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8 MSB
        break;
        case SWITCH_ON_MSG:
            msg.DATA[0]=0x22;
            msg.DATA[1]=0x40;       //Object Index(LSB)
            msg.DATA[2]=0x60;       //Object Index(MSB)
            msg.DATA[3]=0x00;       //Sub-Index
            msg.DATA[4]=0x07;       //Byte 5 LSB
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8 MSB
        break;
        case DISABLE_VOLT_MSG:
            msg.DATA[0]=0x22;
            msg.DATA[1]=0x40;       //Object Index(LSB)
            msg.DATA[2]=0x60;       //Object Index(MSB)
            msg.DATA[3]=0x00;       //Sub-Index
            msg.DATA[4]=0x0D;       //Byte 5 LSB
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8 MSB
        break;
        case QUICK_STOP_MSG:
            msg.DATA[0]=0x22;
            msg.DATA[1]=0x40;       //Object Index(LSB)
            msg.DATA[2]=0x60;       //Object Index(MSB)
            msg.DATA[3]=0x00;       //Sub-Index
            msg.DATA[4]=0x02;       //Byte 5 LSB
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8 MSB
        break;
        case DIGITAL_OUTPUTS_MSG:   // User bit msg 
            msg.DATA[1]=0x01;       //Object Index(LSB)
            msg.DATA[2]=0x20;       //Object Index(MSB)
            msg.DATA[3]=0x03;       //Sub-Index
            msg.DATA[4]=(byte)param;//Byte 5
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8
        break;
        case DIGITAL_OUTPUT_UB1:   // User bit msg 
            msg.DATA[1]=0x5A;       //Object Index(LSB)
            msg.DATA[2]=0x20;       //Object Index(MSB)
            msg.DATA[3]=0x40;       //Sub-Index
            msg.DATA[4]=0x01;       //Byte 5 digital output assigned to usr bit 1
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8
        break;
        case DIGITAL_OUTPUT_UB2:   // User bit msg 
            msg.DATA[1]=0x5A;       //Object Index(LSB)
            msg.DATA[2]=0x20;       //Object Index(MSB)
            msg.DATA[3]=0x41;       //Sub-Index
            msg.DATA[4]=0x02;       //Byte 5 digital output assigned to usr bit 2
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8
        break;
        case DIGITAL_OUTPUT_UB3:   // User bit msg 
            msg.DATA[1]=0x5A;       //Object Index(LSB)
            msg.DATA[2]=0x20;       //Object Index(MSB)
            msg.DATA[3]=0x42;       //Sub-Index
            msg.DATA[4]=0x04;       //Byte 5 digital output assigned to usr bit 3
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8
        break;
        case DIGITAL_INPUTS_MSG:
            msg.DATA[1]=0x23;       //Object Index(LSB)
            msg.DATA[2]=0x20;       //Object Index(MSB)
            msg.DATA[3]=0x01;       //Sub-Index
            msg.DATA[4]=0x00;       //Byte 5
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8
        break;
        case ANALOG_INPUTS_MSG:
            msg.DATA[1]=0x1A;       //Object Index(LSB)
            msg.DATA[2]=0x20;       //Object Index(MSB)
            msg.DATA[3]=(byte)param;//Sub-Index (Number of the input)
            msg.DATA[4]=0x00;       //Byte 5
            msg.DATA[5]=0x00;       //Byte 6
            msg.DATA[6]=0x00;       //Byte 7
            msg.DATA[7]=0x00;       //Byte 8
        break;
        case START_COMM_MSG:
            msg.ID = 0x00;
            msg.LEN = 0x02;         //Tamaño del mensaje (2 bytes)
            msg.DATA[0]=0x01;       //mode
            msg.DATA[1]= can_id;    //node
            msg.DATA[2]=0;
            msg.DATA[3]=0;
            msg.DATA[4]=0;
            msg.DATA[5]=0;
            msg.DATA[6]=0;
            msg.DATA[7]=0;
        break;
	case STOP_COMM_MSG:
            msg.ID = 0x00;
            msg.LEN = 0x02;         //Tamaño del mensaje (2 bytes)
            msg.DATA[0]=0x02;       //mode
            msg.DATA[1]= can_id;    //node
            msg.DATA[2]=0;
            msg.DATA[3]=0;
            msg.DATA[4]=0;
            msg.DATA[5]=0;
            msg.DATA[6]=0;
            msg.DATA[7]=0;
        break;
        case RESET_COMM_MSG:
            msg.ID = 0x00;
            msg.LEN = 0x02;         //Tamaño del mensaje (2 bytes)
            msg.DATA[0]=0x82;       //mode
            msg.DATA[1]= can_id;    //node
            msg.DATA[2]=0;
            msg.DATA[3]=0;
            msg.DATA[4]=0;
            msg.DATA[5]=0;
            msg.DATA[6]=0;
            msg.DATA[7]=0;
        break;
		case RESET_NODE_MSG:
            msg.ID = 0x00;
            msg.LEN = 0x02;         //Tamaño del mensaje (2 bytes)
            msg.DATA[0]=0x81;       //mode
            msg.DATA[1]= can_id;    //node
            msg.DATA[2]=0;
            msg.DATA[3]=0;
            msg.DATA[4]=0;
            msg.DATA[5]=0;
            msg.DATA[6]=0;
            msg.DATA[7]=0;
        break;
	case PREOPERATIONAL_COMM_MSG:
            msg.ID = 0x00;
            msg.LEN = 0x02;         	// Message size (2 bytes)
            msg.DATA[0]=0x80;       	// mode
            msg.DATA[1]= can_id;    	// node
            msg.DATA[2]=0;
            msg.DATA[3]=0;
            msg.DATA[4]=0;
            msg.DATA[5]=0;
            msg.DATA[6]=0;
            msg.DATA[7]=0;
        break;
        case NODEGUARD_MSG:    
            msg.ID = 0x700 + can_id;
            msg.MSGTYPE = MSGTYPE_RTR;   // 
            msg.LEN = 0x08;              // 
        break;
	case HEARTBEAT_MSG:
            msg.ID = 0x700;              //+ can_id;
            msg.LEN = 0x01;              // 
	    msg.DATA[0]=0x00;
            msg.DATA[1]=0x0;
            msg.DATA[2]=0x0;
            msg.DATA[3]=0x0;
            msg.DATA[4]=0x0;
            msg.DATA[5]=0x0;
            msg.DATA[6]=0x0;
            msg.DATA[7]=0x0;
        break;
        case SYNC_MSG:
            msg.ID = 0x80;
            msg.LEN = 0x00;
        break;
        case POSITION_SDO_MSG:
            if(mode == WRITE){
                b1 = param & 0xFF;
                b2 = (param>>8) & 0xFF;
                b3 = (param>>16) & 0xFF;
                b4 = (param>>24) & 0xFF;
            }
            msg.DATA[1]=0x7A;   //Object Index(LSB)
            msg.DATA[2]=0x60;   //Object Index(MSB)
            msg.DATA[3]=0x00;   //Sub-Index
            msg.DATA[4]=b1;     //Byte 5 LSB
            msg.DATA[5]=b2;     //Byte 6
            msg.DATA[6]=b3;     //Byte 7
            msg.DATA[7]=b4;     //Byte 8 MSB

        break;
        case POSITION_PDO_MSG:
            b1 = param & 0xFF;
            b2 = (param>>8) & 0xFF;
            b3 = (param>>16) & 0xFF;
            b4 = (param>>24) & 0xFF;

            msg.ID = RPDO21 + can_id;
            msg.LEN = 0x04;     // Size of message (4 bytes)
            msg.DATA[0]=b1;     //Command -> 22h
            msg.DATA[1]=b2;     //Object Index(LSB)
            msg.DATA[2]=b3;     //Object Index(MSB)
            msg.DATA[3]=b4;     //Sub-Index
            msg.DATA[4]=0x00;   //Byte 5 LSB
            msg.DATA[5]=0x00;   //Byte 6
            msg.DATA[6]=0x00;   //Byte 7
            msg.DATA[7]=0x00;   //Byte 8 MSB
        break;
        case ACTUAL_POSITION_SDO_MSG:
            msg.DATA[1]=0x64;   //Object Index(LSB)
            msg.DATA[2]=0x60;   //Object Index(MSB)
            msg.DATA[3]=0x00;   //Sub-Index
            msg.DATA[4]=0;     //Byte 5 LSB
            msg.DATA[5]=0;     //Byte 6
            msg.DATA[6]=0;     //Byte 7
            msg.DATA[7]=0;     //Byte 8 MSB
        break;
        case VELOCITY_SDO_MSG:
            if(mode == WRITE){
                b1 = param & 0xFF;
                b2 = (param>>8) & 0xFF;
                b3 = (param>>16) & 0xFF;
                b4 = (param>>24) & 0xFF;
            }
            msg.DATA[1]=0xff;   //Object Index(LSB)
            msg.DATA[2]=0x60;   //Object Index(MSB)
            msg.DATA[3]=0x00;   //Sub-Index
            msg.DATA[4]=b1;     //Byte 5 LSB
            msg.DATA[5]=b2;     //Byte 6
            msg.DATA[6]=b3;     //Byte 7
            msg.DATA[7]=b4;     //Byte 8 MSB

        break;
        case VELOCITY_PDO_MSG:
            b1 = param & 0xFF;
            b2 = (param>>8) & 0xFF;
            b3 = (param>>16) & 0xFF;
            b4 = (param>>24) & 0xFF;

            msg.ID = RPDO22 + can_id;
            msg.LEN = 0x04;     // Size of message (4 bytes)
            msg.DATA[0]=b1;
            msg.DATA[1]=b2;
            msg.DATA[2]=b3;
            msg.DATA[3]=b4;
            msg.DATA[4]=0x00;
            msg.DATA[5]=0x00;
            msg.DATA[6]=0x00;
            msg.DATA[7]=0x00;
        break;
        case MODE_OF_OPERATION_MSG:
            msg.DATA[1]=0x60;       // Object Index(LSB)
            msg.DATA[2]=0x60;       // Object Index(MSB)
            msg.DATA[3]=0x00;       // SubIndex
            msg.DATA[4]=(byte)param;// Mode of operation (Position, velocity, home, ...)
            msg.DATA[5]=0x00;
            msg.DATA[6]=0x00;
            msg.DATA[7]=0x00;
        break;
        case HOME_OFFSET_MSG:
            if(mode == WRITE){
                b1 = param & 0xFF;
                b2 = (param>>8) & 0xFF;
                b3 = (param>>16) & 0xFF;
                b4 = (param>>24) & 0xFF;
            }
            msg.DATA[1]=0x7C;       // Object Index(LSB)
            msg.DATA[2]=0x60;       // Object Index(MSB)
            msg.DATA[3]=0x00;       // SubIndex
            msg.DATA[4]=b1;         // 1st byte with the value (LSB)
            msg.DATA[5]=b2;         // 2nd byte with the value
            msg.DATA[6]=b3;         // 3rd byte with the value
            msg.DATA[7]=b4;         // 4th byte with the value (MSB)
        break;
        case HOME_METHOD_MSG:
            msg.DATA[1]=0x98;       //Object Index(LSB)
            msg.DATA[2]=0x60;       //Object Index(MSB)
            msg.DATA[3]=0x00;       // SubIndex
            msg.DATA[4]=(byte)param;// Homing method
            msg.DATA[5]=0x00;
            msg.DATA[6]=0x00;
            msg.DATA[7]=0x00;
        break;
        case HOME_SPEED1_MSG:   // Speed for the first stage of Homing algorithms
            if(mode == WRITE){  // Units: counts/s, Type: Unsigned32, Conversion: 2^17/KS (20.000)
                b1 = param & 0xFF;
                b2 = (param>>8) & 0xFF;
                b3 = (param>>16) & 0xFF;
                b4 = (param>>24) & 0xFF;
            }
            msg.DATA[1]=0x99;       // Object Index(LSB)
            msg.DATA[2]=0x60;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // SubIndex
            msg.DATA[4]=b1;         // 1st byte with the value (LSB)
            msg.DATA[5]=b2;         // 2nd byte with the value
            msg.DATA[6]=b3;         // 3rd byte with the value
            msg.DATA[7]=b4;         // 4th byte with the value (MSB)

        break;
        case HOME_SPEED2_MSG:   // Speed during the search for zero
            if(mode == WRITE){  // Units: counts/s, Type: Unsigned32, Conversion: 2^17/KS (20.000)
                b1 = param & 0xFF;
                b2 = (param>>8) & 0xFF;
                b3 = (param>>16) & 0xFF;
                b4 = (param>>24) & 0xFF;
            }
            msg.DATA[1]=0x99;       // Object Index(LSB)
            msg.DATA[2]=0x60;       // Object Index(MSB)
            msg.DATA[3]=0x02;       // SubIndex
            msg.DATA[4]=b1;         // 1st byte with the value (LSB)
            msg.DATA[5]=b2;         // 2nd byte with the value
            msg.DATA[6]=b3;         // 3rd byte with the value
            msg.DATA[7]=b4;         // 4th byte with the value (MSB)

        break;
        case START_HOME_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x40;       // Object Index(LSB)
            msg.DATA[2]=0x60;       // Object Index(MSB)
            msg.DATA[3]=0x00;       // Sub-Index
            msg.DATA[4]=0x1F;       // Byte 5
            msg.DATA[5]=0x00;       // Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
        case STOP_HOME_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x40;       // Object Index(LSB)
            msg.DATA[2]=0x60;       // Object Index(MSB)
            msg.DATA[3]=0x00;       // Sub-Index
            msg.DATA[4]=0x0F;       // Byte 5
            msg.DATA[5]=0x00;       // Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
        case CONTROL_WORD_MSG:
            if(mode == WRITE){
                b1 = param & 0xFF;
                b2 = (param>>8) & 0xFF;
                b3 = (param>>16) & 0xFF;
                b4 = (param>>24) & 0xFF;
            }
            msg.DATA[1]=0x41;       // Object Index(LSB)
            msg.DATA[2]=0x60;       // Object Index(MSB)
            msg.DATA[3]=0x00;       // Sub-Index
            msg.DATA[4]=b1;       // Byte 5
            msg.DATA[5]=b2;       // Byte 6
            msg.DATA[6]=b3;       // Byte 7
            msg.DATA[7]=b4;       // Byte 8
        break;
        case CONF_RPDO1_1_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x00;       // Object Index(LSB)
            msg.DATA[2]=0x14;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // Sub-index 1 -> COB-ID = Configurable, Enable, Allow RTRs
            msg.DATA[4]=(RPDO1 + can_id)&0xFF;	// COB-ID LSB
			msg.DATA[5]=RPDO1_MSB;       		// COB-ID MSB
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
		case CONF_RPDO1_2_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x00;       // Object Index(LSB)
            msg.DATA[2]=0x14;       // Object Index(MSB)
            msg.DATA[3]=0x02;       // Sub-Index 2-> Transmission type
            msg.DATA[4]=(byte)param;// Transmission type
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;	
		case CONF_RPDO21_1_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x14;       // Object Index(LSB)
            msg.DATA[2]=0x14;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // Sub-index 1 -> COB-ID = Configurable, Enable, Allow RTRs
            msg.DATA[4]=(RPDO21 + can_id)&0xFF;	// COB-ID LSB
			msg.DATA[5]=RPDO21_MSB;       		// COB-ID MSB
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
		case CONF_RPDO21_2_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x14;       // Object Index(LSB)
            msg.DATA[2]=0x14;       // Object Index(MSB)
            msg.DATA[3]=0x02;       // Sub-Index 2-> Transmission type
            msg.DATA[4]=(byte)param;// Transmission type
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
		case CONF_RPDO22_1_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x15;       // Object Index(LSB)
            msg.DATA[2]=0x14;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // Sub-index 1 -> COB-ID = Configurable, Enable, Allow RTRs
            msg.DATA[4]=(RPDO22 + can_id)&0xFF;	// COB-ID LSB
			msg.DATA[5]=RPDO22_MSB;       		// COB-ID MSB
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
		case CONF_RPDO22_2_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x15;       // Object Index(LSB)
            msg.DATA[2]=0x14;       // Object Index(MSB)
            msg.DATA[3]=0x02;       // Sub-Index 2-> Transmission type
            msg.DATA[4]=(byte)param;// Transmission type
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
			
		case CONF_TPDO1_1_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x00;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // Sub-index 1 -> COB-ID = Configurable, Enable, Allow RTRs
            msg.DATA[4]=(TPDO1 + can_id)&0xFF;	// COB-ID LSB
			msg.DATA[5]=TPDO1_MSB;       		// COB-ID MSB
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=(byte)param;// Byte 8 (enable / disable the message)
        break;
		case CONF_TPDO1_2_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x00;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x02;       // Sub-Index 2-> Transmission type
            msg.DATA[4]=(byte)param;// Transmission type
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
		case CONF_TPDO3_1_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x02;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // Sub-index 1 -> COB-ID = Configurable, Enable, Allow RTRs
            msg.DATA[4]=(TPDO3 + can_id)&0xFF;	// COB-ID LSB
			msg.DATA[5]=TPDO3_MSB;       		// COB-ID MSB
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=(byte)param;// Byte 8 (enable / disable the message)
        break;
		case CONF_TPDO3_2_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x02;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x02;       // Sub-Index 2-> Transmission type
            msg.DATA[4]=(byte)param;// Transmission type
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
		case CONF_TPDO4_1_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x03;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // Sub-index 1 -> COB-ID = Configurable, Enable, Allow RTRs
            msg.DATA[4]=(TPDO4 + can_id)&0xFF;	// COB-ID LSB
			msg.DATA[5]=TPDO4_MSB;       		// COB-ID MSB
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=(byte)param;// Byte 8 (enable / disable the message)
        break;
		case CONF_TPDO4_2_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x03;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x02;       // Sub-Index 2-> Transmission type
            msg.DATA[4]=(byte)param;// Transmission type
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;       // Byte 8
        break;
		case CONF_TPDO21_1_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x14;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // Sub-index 1 -> COB-ID = Configurable, Enable, Allow RTRs
            msg.DATA[4]=(TPDO21 + can_id)&0xFF;	// COB-ID LSB
			msg.DATA[5]=TPDO21_MSB;       		// COB-ID MSB
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=(byte)param;// Byte 8 (enable / disable the message)
        break;
		case CONF_TPDO21_2_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x14;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x02;       // Sub-Index 2-> Transmission type
            msg.DATA[4]=(byte)param;// Transmission type
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;		// Byte 8 
        break;
		case CONF_TPDO22_1_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x15;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // Sub-index 1 -> COB-ID = Configurable, Enable, Allow RTRs
            msg.DATA[4]=(TPDO22 + can_id)&0xFF;	// COB-ID LSB
			msg.DATA[5]=TPDO22_MSB;       		// COB-ID MSB
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=(byte)param;// Byte 8 (enable / disable the message)
			//printf("Send: [%x %x %x %x %x %x %x %x]\n", msg.DATA[0], msg.DATA[1], msg.DATA[2],msg.DATA[3],
			//       msg.DATA[4],msg.DATA[5],msg.DATA[6],msg.DATA[7]);
			
        break;
		case CONF_TPDO22_2_MSG:
            msg.DATA[0]=0x22;       // Always write mode
            msg.DATA[1]=0x15;       // Object Index(LSB)
            msg.DATA[2]=0x18;       // Object Index(MSB)
            msg.DATA[3]=0x02;       // Sub-Index 2-> Transmission type
            msg.DATA[4]=(byte)param;// Transmission type
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;		// Byte 8 
        break;
		case DRIVE_STATUS_MSG:
            msg.DATA[0]=0x40;       // Always read mode
            msg.DATA[1]=0x02;       // Object Index(LSB)
            msg.DATA[2]=0x20;       // Object Index(MSB)
            msg.DATA[3]=(byte)param;// Sub-Index-> Type of drive status (1: Status Bridge, 2: Protection Status,  3: System Protection Status, 4: System Status 1, 5: System status 2, 6: System status 3)
            msg.DATA[4]=0x00;		// Byte 4
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;		// Byte 8 
        break;    
		case GUARD_TIME_MSG:
			if(mode == WRITE){
                b1 = param & 0xFF;
                b2 = (param>>8) & 0xFF;
            }
			msg.DATA[1]=0x0C;       // Object Index(LSB)
            msg.DATA[2]=0x10;       // Object Index(MSB)
            msg.DATA[3]=0x00;		// Sub-Index 
            msg.DATA[4]=b1;			// Byte 4 (LSB)
            msg.DATA[5]=b2;			// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;		// Byte 8 (LSB)
		break;
		case LIFE_TIME_FACTOR_MSG:
			msg.DATA[1]=0x0D;       // Object Index(LSB)
            msg.DATA[2]=0x10;       // Object Index(MSB)
            msg.DATA[3]=0x00;		// Sub-Index
            msg.DATA[4]=(byte)param;// Byte 4
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;		// Byte 8 
		break;
		case EVENT_ACTION_MSG:
			msg.DATA[1]=0x65;       // Object Index(LSB)
            msg.DATA[2]=0x20;       // Object Index(MSB)
            msg.DATA[3]=0x21;		// Sub-Index (21h Communication Error)
            msg.DATA[4]=(byte)param;// Byte 4 (Value for the action)
            msg.DATA[5]=0x00;		// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;		// Byte 8 
		break;
		case EVENT_RECOVERY_TIME_MSG:
			if(mode == WRITE){
                b1 = param & 0xFF;
                b2 = (param>>8) & 0xFF;
            }
			msg.DATA[1]=0x66;       // Object Index(LSB)
            msg.DATA[2]=0x20;       // Object Index(MSB)
            msg.DATA[3]=0x21;		// Sub-Index (21h Communication Error)
            msg.DATA[4]=b1;			// Byte 4 (Value for the action)
            msg.DATA[5]=b2;			// Byte 6
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;		// Byte 8 
		break;
		case HEARTBEAT_CONSUMER_MSG:
            if(mode == WRITE){
                b1 = param & 0xFF;
                b2 = (param>>8) & 0xFF;
                b3 = (param>>16) & 0xFF;
                b4 = (param>>24) & 0xFF;
            }
            msg.DATA[1]=0x16;       // Object Index(LSB)
            msg.DATA[2]=0x10;       // Object Index(MSB)
            msg.DATA[3]=0x01;       // Sub-Index
            msg.DATA[4]=b1;       // Byte 5
            msg.DATA[5]=b2;       // Byte 6
            msg.DATA[6]=b3;       // Byte 7
            msg.DATA[7]=b4;       // Byte 8
        break;
	case ACTUAL_CURRENT_SDO_MSG:            
            msg.DATA[1]=0x77;       // Object Index(LSB)
            msg.DATA[2]=0x60;       // Object Index(MSB)
            msg.DATA[3]=0x00;       // Sub-Index
            msg.DATA[4]=b1;       // Byte 5
            msg.DATA[5]=b2;       // Byte 6
            msg.DATA[6]=b3;       // Byte 7
            msg.DATA[7]=b4;       // Byte 8
        break;
        case DC_BUS_SDO_MSG:
	    msg.DATA[1]=0x0F;     // Object Index(LSB)
            msg.DATA[2]=0x20;     // Object Index(MSB)
            msg.DATA[3]=0x01;     // Sub-Index
            msg.DATA[4]=0x00;     // Byte 5
            msg.DATA[5]=0x00;     // Byte 6
            msg.DATA[6]=0x00;     // Byte 7
            msg.DATA[7]=0x00;     // Byte 8
        break;
        
				case CONF_SDO_PEAK_CURRENT_LIMIT_MSG:  // Contains a value corresponding to the peak current limit set in the drive.
						b1 = param & 0xFF;			// LSB	
						b2 = (param>>8) & 0xFF;	// MSB
						//b3 = (param>>16) & 0xFF;
						//b4 = (param>>24) & 0xFF;
				
            msg.DATA[1]=0x34;       // Object Index(LSB)
            msg.DATA[2]=0x20;       // Object Index(MSB)
            msg.DATA[3]=0x04;       // Sub-Index 4 -> Peak Current Limit
            msg.DATA[4]=b1;					// Byte 5  LSB of desired current
            msg.DATA[5]=b2;					// Byte 6	 MSB of desired current
            msg.DATA[6]=0x00;       // Byte 7
            msg.DATA[7]=0x00;				// Byte 8 
				break;
  
	default:
            ROS_ERROR("%s::Send: Unknown message", sComponentName.c_str());
            return ERROR;
        break;

    }

    return canDev->Send(&msg);
}

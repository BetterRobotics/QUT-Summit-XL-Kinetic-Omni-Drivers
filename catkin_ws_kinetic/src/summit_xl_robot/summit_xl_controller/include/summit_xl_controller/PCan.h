/*! \class PCan
 *  \file PCan.h
 *	\author Robotnik Automation S.L.L
 *	\version 1.0
 *	\date 2010
 *  \brief Class to manage the CAN communication using a PEAK CAN device and the CANOpen protocol
 * (C) 2012 Robotnik Automation, SLL
 *  All rights reserved.
 */

#ifndef __PCAN_H
	#define __PCAN_H

#include "summit_xl_controller/Component.h"
#include "summit_xl_controller/pcan.h"
#include "summit_xl_controller/libpcan.h" 

//#define DEFAULT_NODE "/dev/pcanusb0"
#define DEFAULT_NODE "/dev/pcan32"

//extern HANDLE h;
typedef unsigned char byte;

//! Internal communication status (CANOpen)
enum CommunicationStatus{
    UNKNOWN,
    PRE_OPERATIONAL,
    OPERATIONAL,
    STOPPED,
    FAULT
};
//! Types of NMT messages (CANOpen)
enum NMTMessage{
    START_NODE,
    STOP_NODE,
    PREOPERATIONAL_NODE,
    RESET_NODE,
    RESET_COMMUNICATION
};
//! Mode of access to the CAN object
enum AccessMode{
    READ,
    WRITE
};



// Class ESDCan to communicate with an ESDCAN device
class PCan:public Component{

	private:
    		//! CAN device handle
		HANDLE h;
		//! Mutex to manage the access to the device
		pthread_mutex_t mutexCAN;
	    	//! Baud rate used in the communication
		uint16_t wBTR0BTR1;
		//! Description of the device status
		string sStatus;
		//! Version string
		char txt[VERSIONSTRING_LEN];
		//! Device
		string sDevice;

	public:
    		//! constructor
		PCan(uint16_t baudrate);
		//! constructor
		PCan(string dev, uint16_t baudrate);
		//! Destructor
		virtual ~PCan();
		//! Sends CAN messages
		ReturnValue Send(TPCANMsg *tpcmsg);
		//! Read CAN messages
		ReturnValue Read(TPCANRdMsg *tpcmsg);
		//! Read Diagnostics of the PCan board
		ReturnValue ReadDiagnostics();


	protected:
		//! Open device to be used 
		virtual ReturnValue Open();
		//! Closes used devices
	        virtual ReturnValue Close();
		//! Configures devices and performance of the component
		virtual ReturnValue Configure();
};

#endif




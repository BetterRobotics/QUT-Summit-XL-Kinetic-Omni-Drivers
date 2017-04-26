/*! \class PCan
 *  \file PCan.cc
 *	\author Robotnik Automation S.L.L
 *	\version 1.0
 *	\date 2012
 *  \brief Class to manage the CAN communication using an PEAK CAN device and the CANOpen protocol
 * (C) 2012 Robotnik Automation, SLL
 *  All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   // exit
#include <signal.h>
#include <string.h>
#include <stdlib.h>   // strtoul
#include <fcntl.h>    // O_RDWR
#include <unistd.h>

#include <libpcan.h>
#include <ctype.h>

#include "summit_xl_controller/PCan.h"

//****************************************************************************
// CODE

/*! \fn PCan::PCan(NetChannel net_channel, BaudRate baudrate)
 	* Constructor by default
    \param net_channel as int, CAN channel
    \param baudrate as int, baudrate for the communication
*/
PCan::PCan(uint16_t baudrate):Component(10.0){
	// Cambiamos el nombre de la clase al de la clase derivada
	sComponentName.assign("PCan");
	wBTR0BTR1 = baudrate;
	//iSentMsgs = iReadMsgs = 0;
	sDevice.assign(DEFAULT_NODE);
	// mutex intitialization
	pthread_mutex_init(&mutexCAN, NULL);
};

/*! \fn PCan::PCan(uint16_t baudrate, const char *dev)
 	* Constructor by default
    \param dev as char *, name of the CAN device
    \param baudrate as int, baudrate for the communication
*/
PCan::PCan(string dev, uint16_t baudrate):Component(10.0){
	// Cambiamos el nombre de la clase al de la clase derivada
	sComponentName.assign("PCan");
	wBTR0BTR1 = baudrate;
	//iSentMsgs = iReadMsgs = 0;
	sDevice = dev;
	// mutex intitialization
	pthread_mutex_init(&mutexCAN, NULL);
};


/*! \fn PCan::~PCan()
  * Destructor by default
*/
PCan::~PCan(){
        pthread_mutex_destroy(&mutexCAN);
}

/*! \fn ReturnValue PCan::Open()
 * Open device to be used
 * \return OK
 * \return ERROR
*/
ReturnValue PCan::Open(){

  pthread_mutex_lock(&mutexCAN);
  // open CAN port
  //const char *szDevNode = DEFAULT_NODE;
  // O_NONBLOCK - non blocking read 
  // O_RDWR - blocking read - function returns only if there is something in the buffer to read
  h = LINUX_CAN_Open(sDevice.c_str(), O_RDWR | O_NONBLOCK);
  if (!h) {
	ROS_ERROR("PCan::Open: can't open %s\n", sDevice.c_str());
	pthread_mutex_unlock(&mutexCAN);
	return ERROR;
    	}
  // clear status
  CAN_Status(h);
  // get version info
  errno = CAN_VersionInfo(h, txt);
  if (!errno) {
    ROS_INFO("PCan::Open: driver version = %s\n", txt);
    }
  else {
    ROS_ERROR("PCan::Open: CAN_VersionInfo() failed");
    pthread_mutex_unlock(&mutexCAN);
    return ERROR;
    }

  // Reset send and receive queues
  //if (CAN_ResetClient() != CAN_ERR_OK)
  
  pthread_mutex_unlock(&mutexCAN);
  ROS_INFO("PCan::Open: Opened successfully");
  return OK;
}


/*! \fn ReturnValue PCan::Configure()
 * Configures devices and performance of the component
 *  - Configures Baudrate
 * \return OK
 * \return ERROR if the configuration process fails
*/
ReturnValue PCan::Configure(){

  pthread_mutex_lock(&mutexCAN);

  // init to a user defined bit rate
  errno = CAN_Init(h, wBTR0BTR1, CAN_INIT_TYPE_ST); // _ST:standard frames, _EX:extended frames 
  if (errno) {
    ROS_ERROR("PCan::Configure: CAN_Init() failed");
    pthread_mutex_unlock(&mutexCAN);
    return ERROR;
    }
  
  // In ESD version IDs were added here !
  pthread_mutex_unlock(&mutexCAN);
  ROS_INFO("PCan::Configure: Configured successfully");
  sStatus.assign("OK");
  return OK;
}

/*! \fn ReturnValue PCan::Close()
 * Closes used devices
 * \return OK
 * \return ERROR
*/
ReturnValue PCan::Close(){

  if (h)
  {
    CAN_Close(h);
  }
  ROS_INFO("PCan:close finished.");
  sStatus.assign("CLOSED");
  pthread_mutex_unlock(&mutexCAN);
  return OK;
}

/*! \fn ReturnValue PCan::Send(TPCANMsg *cmsg)
 * Sends CAN messages
 * \param cmsg as TPCANMsg*, pointer to data buffer of messages
 * \param len as int*, IN: number of messages to be transmitted
 *                     OUT: number of transmitted messages
 * \return OK
 * \return ERROR
*/
ReturnValue PCan::Send(TPCANMsg *tpcmsg){

    static bool bPrintSend = false;
    if(!bInitialized){
	if(!bPrintSend){
	  ROS_ERROR("%s::Read: Impossible to read because of it's not initialized", sComponentName.c_str());
	  bPrintSend = true;
	  }
	return NOT_INITIALIZED;
        }

    pthread_mutex_lock(&mutexCAN);

// Write the message to the CAN bus
//    if (errno = CAN_Write( h, tpcmsg ) )
//        {
//          ROS_ERROR("PCan::Send error in CAN_Write() %d ", errno );
//          pthread_mutex_unlock(&mutexCAN);
//          return ERROR;
//        }

     // Write the message to the CAN bus
     CAN_Write( h, tpcmsg );
     int iRet = CAN_Status(h);
     if(iRet < 0)
          {
	  // 
          int err = nGetLastError();
          ROS_ERROR("PCan::Send error in CAN_Write() errno=%d iRet=%d nGetLastError=%d", errno, iRet, err );
	  pthread_mutex_unlock(&mutexCAN);
          return ERROR;
          }
          
     // ROS_INFO("PCan::Send WRITE OK !!!!!!!!!!!!!!! ");

     // Possible wait between consecutive sends
     pthread_mutex_unlock(&mutexCAN);
     bPrintSend = false;
     return OK;
}



/*! \fn ReturnValue PCan::Read(TPCANMsg *tpcmsg)
 * Read CAN messages
 * \param tpcmsg as TPCANRdMsg*, pointer to data buffer of messages
 * \param len as int*, IN: size of the TPCANRdMsg buffer
 *                     OUT: number of read messages
 * \return OK
 * \return ERROR
*/
ReturnValue PCan::Read(TPCANRdMsg *tpcmsg){

    int last_err = 0;

    if(!bInitialized){
	ROS_INFO("%s::Read: Impossible to read because of it's not initialized", sComponentName.c_str());
	return NOT_INITIALIZED;
	}

    pthread_mutex_lock(&mutexCAN);

    int iRet = LINUX_CAN_Read(h, tpcmsg);
    if (iRet == CAN_ERR_OK)  // Read OK
      {
        if (tpcmsg->Msg.MSGTYPE == MSGTYPE_STANDARD) {
		pthread_mutex_unlock(&mutexCAN);
        	return OK;
		}
	else {
		pthread_mutex_unlock(&mutexCAN);		
		return NOT_ERROR;
	     }
      }
    else if(tpcmsg->Msg.MSGTYPE == MSGTYPE_STATUS)
         {  
	 if (iRet < 0) {
		 last_err = nGetLastError();
		 ROS_ERROR("PCan::Read: error in LINUX_CAN_Read() - MSGTYPE_STATUS - err=%d", last_err);
	         pthread_mutex_unlock(&mutexCAN);
		 return ERROR;                 
		 }
         if (iRet & CAN_ERR_QRCVEMPTY)
                 {
                 // Error (Don't output error of empty queue) (not an error)              
		 // ROS_INFO((char *) "PCan::Read: empty queue ");
	         pthread_mutex_unlock(&mutexCAN); 
// TODO add input in ReturnValue Component.h ??
		 return NOT_ERROR; // Buffer empty 
                 }
         }

    // Este caso no esta claro : last_err da 11, iRet -1 y son tramas de longitud 4, todo a 0
    //  id=1, len=4, data[ 0 0 0 0 0 0 0 0 ]
    if (iRet & CAN_ERR_QRCVEMPTY) {
        pthread_mutex_unlock(&mutexCAN);  
        return NOT_ERROR;   
        }

    last_err = nGetLastError();
    ROS_ERROR("PCan::Read: error in LINUX_CAN_Read, iRet=%d  err=%d", iRet, last_err);       
    // For DEBUG
    ReadDiagnostics(); 
    pthread_mutex_unlock(&mutexCAN);
    return ERROR;


/*
   // check if a message is pending, if not wait for a period and try again and return
   int pendread, pendwrite;
   int iRet = LINUX_CAN_Extended_Status(h, &pendread, &pendwrite);   
   if (iRet < 0) {
	pthread_mutex_unlock(&mutexCAN);
        return ERROR;       
       }
   // if there is a message pending, read it
   if(pendread) {
        iRet = LINUX_CAN_Read(h, tpcmsg);
    	if (iRet == CAN_ERR_OK) { // Read OK
	    pthread_mutex_unlock(&mutexCAN);
	    return OK;
	    }
        else if (tpcmsg->Msg.MSGTYPE & MSGTYPE_STATUS) {
	    pthread_mutex_unlock(&mutexCAN);
	    return NOT_ERROR;
	    }
 	}
   // if not, just return with no error
   else  {
	pthread_mutex_unlock(&mutexCAN);
	return NOT_ERROR;
         }
*/
}

/*! \fn ReturnValue PCan::ReadDiagnostics()
 * Call diagnostics function of the CAN device
 *     OUT: number of read messages
 * \return OK
 * \return ERROR
*/
ReturnValue PCan::ReadDiagnostics()
{
  int err;
  TPDIAG diag;
  
  err = LINUX_CAN_Statistics(h, &diag);
  if (err) {
    ROS_ERROR("PCan::LogDiagnostics: can't read diagnostics, error=%d", err);
    return ERROR;
    }
  else {
    ROS_INFO("*****************************************");
    ROS_INFO("Serial Number = 0x%08x  Device Number = %d", diag.dwBase, diag.wIrqLevel);
    ROS_INFO("reads=%d,  writes=%d", diag.dwReadCounter, diag.dwWriteCounter);
    ROS_INFO("errors=%d,  last CAN status = 0x%04x", diag.dwErrorCounter, diag.wErrorFlag);
    // diag.nLastError;
    // diag.nOpenPaths;
    // diag.szVersionString;    
    }  
  return OK;
}


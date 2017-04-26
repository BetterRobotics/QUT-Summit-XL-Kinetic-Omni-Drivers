// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');
let MotorStatus = require('./MotorStatus.js');

//-----------------------------------------------------------

class MotorsStatus {
  constructor() {
    this.flwStatus = new MotorStatus();
    this.blwStatus = new MotorStatus();
    this.frwStatus = new MotorStatus();
    this.brwStatus = new MotorStatus();
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type MotorsStatus
    // Serialize message field [flwStatus]
    bufferInfo = MotorStatus.serialize(obj.flwStatus, bufferInfo);
    // Serialize message field [blwStatus]
    bufferInfo = MotorStatus.serialize(obj.blwStatus, bufferInfo);
    // Serialize message field [frwStatus]
    bufferInfo = MotorStatus.serialize(obj.frwStatus, bufferInfo);
    // Serialize message field [brwStatus]
    bufferInfo = MotorStatus.serialize(obj.brwStatus, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type MotorsStatus
    let tmp;
    let len;
    let data = new MotorsStatus();
    // Deserialize message field [flwStatus]
    tmp = MotorStatus.deserialize(buffer);
    data.flwStatus = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [blwStatus]
    tmp = MotorStatus.deserialize(buffer);
    data.blwStatus = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [frwStatus]
    tmp = MotorStatus.deserialize(buffer);
    data.frwStatus = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [brwStatus]
    tmp = MotorStatus.deserialize(buffer);
    data.brwStatus = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/MotorsStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2196337708357903c08b92eeb4a057f9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    MotorStatus flwStatus
    MotorStatus blwStatus
    MotorStatus frwStatus
    MotorStatus brwStatus
    
    
    ================================================================================
    MSG: robotnik_msgs/MotorStatus
    string state
    string status
    string statusword
    string driveflags
    
    `;
  }

};

module.exports = MotorsStatus;

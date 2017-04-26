// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');
let MotorStatus = require('./MotorStatus.js');

//-----------------------------------------------------------

class MotorsStatusDifferential {
  constructor() {
    this.lwStatus = new MotorStatus();
    this.rwStatus = new MotorStatus();
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type MotorsStatusDifferential
    // Serialize message field [lwStatus]
    bufferInfo = MotorStatus.serialize(obj.lwStatus, bufferInfo);
    // Serialize message field [rwStatus]
    bufferInfo = MotorStatus.serialize(obj.rwStatus, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type MotorsStatusDifferential
    let tmp;
    let len;
    let data = new MotorsStatusDifferential();
    // Deserialize message field [lwStatus]
    tmp = MotorStatus.deserialize(buffer);
    data.lwStatus = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [rwStatus]
    tmp = MotorStatus.deserialize(buffer);
    data.rwStatus = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/MotorsStatusDifferential';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f8b06b08fb9eab82b3a6155a19c6765d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    MotorStatus lwStatus
    MotorStatus rwStatus
    
    
    ================================================================================
    MSG: robotnik_msgs/MotorStatus
    string state
    string status
    string statusword
    string driveflags
    
    `;
  }

};

module.exports = MotorsStatusDifferential;

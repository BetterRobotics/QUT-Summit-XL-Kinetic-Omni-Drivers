// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class MotorStatus {
  constructor() {
    this.state = '';
    this.status = '';
    this.statusword = '';
    this.driveflags = '';
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type MotorStatus
    // Serialize message field [state]
    bufferInfo = _serializer.string(obj.state, bufferInfo);
    // Serialize message field [status]
    bufferInfo = _serializer.string(obj.status, bufferInfo);
    // Serialize message field [statusword]
    bufferInfo = _serializer.string(obj.statusword, bufferInfo);
    // Serialize message field [driveflags]
    bufferInfo = _serializer.string(obj.driveflags, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type MotorStatus
    let tmp;
    let len;
    let data = new MotorStatus();
    // Deserialize message field [state]
    tmp = _deserializer.string(buffer);
    data.state = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [status]
    tmp = _deserializer.string(buffer);
    data.status = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [statusword]
    tmp = _deserializer.string(buffer);
    data.statusword = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [driveflags]
    tmp = _deserializer.string(buffer);
    data.driveflags = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/MotorStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bf902392cd07d79e1d1294bfae19e58e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string state
    string status
    string statusword
    string driveflags
    
    `;
  }

};

module.exports = MotorStatus;

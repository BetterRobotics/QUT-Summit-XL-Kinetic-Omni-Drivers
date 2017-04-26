// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');
let AlarmSensor = require('./AlarmSensor.js');

//-----------------------------------------------------------

class Alarms {
  constructor() {
    this.alarms = [];
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type Alarms
    // Serialize the length for message field [alarms]
    bufferInfo = _serializer.uint32(obj.alarms.length, bufferInfo);
    // Serialize message field [alarms]
    obj.alarms.forEach((val) => {
      bufferInfo = AlarmSensor.serialize(val, bufferInfo);
    });
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type Alarms
    let tmp;
    let len;
    let data = new Alarms();
    // Deserialize array length for message field [alarms]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [alarms]
    data.alarms = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = AlarmSensor.deserialize(buffer);
      data.alarms[i] = tmp.data;
      buffer = tmp.buffer;
    }
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/Alarms';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '83113d787282f31e7cff7eb72a2096c0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    AlarmSensor[] alarms
    
    ================================================================================
    MSG: robotnik_msgs/AlarmSensor
    int8 id
    string description
    string message
    
    
    `;
  }

};

module.exports = Alarms;

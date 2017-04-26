// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class BatteryStatus {
  constructor() {
    this.level = 0.0;
    this.time_remaining = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type BatteryStatus
    // Serialize message field [level]
    bufferInfo = _serializer.float32(obj.level, bufferInfo);
    // Serialize message field [time_remaining]
    bufferInfo = _serializer.uint32(obj.time_remaining, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type BatteryStatus
    let tmp;
    let len;
    let data = new BatteryStatus();
    // Deserialize message field [level]
    tmp = _deserializer.float32(buffer);
    data.level = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [time_remaining]
    tmp = _deserializer.uint32(buffer);
    data.time_remaining = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/BatteryStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '97f2ff224c7220de9e3b44df5993c0f6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 level			# in %
    uint32 time_remaining		# in minutes
    
    `;
  }

};

module.exports = BatteryStatus;

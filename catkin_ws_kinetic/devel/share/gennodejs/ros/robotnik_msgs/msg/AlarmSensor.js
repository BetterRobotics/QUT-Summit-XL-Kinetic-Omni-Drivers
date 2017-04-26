// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class AlarmSensor {
  constructor() {
    this.id = 0;
    this.description = '';
    this.message = '';
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type AlarmSensor
    // Serialize message field [id]
    bufferInfo = _serializer.int8(obj.id, bufferInfo);
    // Serialize message field [description]
    bufferInfo = _serializer.string(obj.description, bufferInfo);
    // Serialize message field [message]
    bufferInfo = _serializer.string(obj.message, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type AlarmSensor
    let tmp;
    let len;
    let data = new AlarmSensor();
    // Deserialize message field [id]
    tmp = _deserializer.int8(buffer);
    data.id = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [description]
    tmp = _deserializer.string(buffer);
    data.description = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [message]
    tmp = _deserializer.string(buffer);
    data.message = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/AlarmSensor';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5dae51bccfcc658f2dc0fff5ec79cb7a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 id
    string description
    string message
    
    
    `;
  }

};

module.exports = AlarmSensor;

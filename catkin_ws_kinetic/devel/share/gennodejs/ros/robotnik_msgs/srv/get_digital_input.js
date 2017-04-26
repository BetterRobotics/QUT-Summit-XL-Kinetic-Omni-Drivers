// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class get_digital_inputRequest {
  constructor() {
    this.input = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type get_digital_inputRequest
    // Serialize message field [input]
    bufferInfo = _serializer.int8(obj.input, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type get_digital_inputRequest
    let tmp;
    let len;
    let data = new get_digital_inputRequest();
    // Deserialize message field [input]
    tmp = _deserializer.int8(buffer);
    data.input = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/get_digital_inputRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1491ea77b99fb7b24d088237597e6386';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 input
    
    `;
  }

};

class get_digital_inputResponse {
  constructor() {
    this.value = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type get_digital_inputResponse
    // Serialize message field [value]
    bufferInfo = _serializer.bool(obj.value, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type get_digital_inputResponse
    let tmp;
    let len;
    let data = new get_digital_inputResponse();
    // Deserialize message field [value]
    tmp = _deserializer.bool(buffer);
    data.value = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/get_digital_inputResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e431d687bf4b2c65fbd94b12ae0cb5d9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool value
    
    
    `;
  }

};

module.exports = {
  Request: get_digital_inputRequest,
  Response: get_digital_inputResponse
};

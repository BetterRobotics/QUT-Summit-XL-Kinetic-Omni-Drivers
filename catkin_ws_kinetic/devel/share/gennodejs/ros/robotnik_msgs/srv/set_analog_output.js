// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class set_analog_outputRequest {
  constructor() {
    this.output = 0;
    this.value = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_analog_outputRequest
    // Serialize message field [output]
    bufferInfo = _serializer.int8(obj.output, bufferInfo);
    // Serialize message field [value]
    bufferInfo = _serializer.float32(obj.value, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_analog_outputRequest
    let tmp;
    let len;
    let data = new set_analog_outputRequest();
    // Deserialize message field [output]
    tmp = _deserializer.int8(buffer);
    data.output = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [value]
    tmp = _deserializer.float32(buffer);
    data.value = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/set_analog_outputRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '23963a89f1eb75051be813e2ad92b196';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 output
    float32 value
    
    `;
  }

};

class set_analog_outputResponse {
  constructor() {
    this.ret = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_analog_outputResponse
    // Serialize message field [ret]
    bufferInfo = _serializer.bool(obj.ret, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_analog_outputResponse
    let tmp;
    let len;
    let data = new set_analog_outputResponse();
    // Deserialize message field [ret]
    tmp = _deserializer.bool(buffer);
    data.ret = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/set_analog_outputResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e2cc9e9d8c464550830df49c160979ad';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool ret
    
    
    `;
  }

};

module.exports = {
  Request: set_analog_outputRequest,
  Response: set_analog_outputResponse
};

// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class set_digital_outputRequest {
  constructor() {
    this.output = 0;
    this.value = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_digital_outputRequest
    // Serialize message field [output]
    bufferInfo = _serializer.int8(obj.output, bufferInfo);
    // Serialize message field [value]
    bufferInfo = _serializer.bool(obj.value, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_digital_outputRequest
    let tmp;
    let len;
    let data = new set_digital_outputRequest();
    // Deserialize message field [output]
    tmp = _deserializer.int8(buffer);
    data.output = tmp.data;
    buffer = tmp.buffer;
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
    return 'robotnik_msgs/set_digital_outputRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e1dc4e43688f0a8d32bc10e72fd189d2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 output
    bool value
    
    `;
  }

};

class set_digital_outputResponse {
  constructor() {
    this.ret = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_digital_outputResponse
    // Serialize message field [ret]
    bufferInfo = _serializer.bool(obj.ret, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_digital_outputResponse
    let tmp;
    let len;
    let data = new set_digital_outputResponse();
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
    return 'robotnik_msgs/set_digital_outputResponse';
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
  Request: set_digital_outputRequest,
  Response: set_digital_outputResponse
};

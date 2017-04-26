// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class set_float_valueRequest {
  constructor() {
    this.value = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_float_valueRequest
    // Serialize message field [value]
    bufferInfo = _serializer.float32(obj.value, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_float_valueRequest
    let tmp;
    let len;
    let data = new set_float_valueRequest();
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
    return 'robotnik_msgs/set_float_valueRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0aca93dcf6d857f0e5a0dc6be1eaa9fb';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 value
    
    `;
  }

};

class set_float_valueResponse {
  constructor() {
    this.ret = false;
    this.errorMessage = new std_msgs.msg.String();
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_float_valueResponse
    // Serialize message field [ret]
    bufferInfo = _serializer.bool(obj.ret, bufferInfo);
    // Serialize message field [errorMessage]
    bufferInfo = std_msgs.msg.String.serialize(obj.errorMessage, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_float_valueResponse
    let tmp;
    let len;
    let data = new set_float_valueResponse();
    // Deserialize message field [ret]
    tmp = _deserializer.bool(buffer);
    data.ret = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [errorMessage]
    tmp = std_msgs.msg.String.deserialize(buffer);
    data.errorMessage = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/set_float_valueResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b607fdf6f13faab17a8c316347e7f65b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool ret
    std_msgs/String errorMessage
    
    
    ================================================================================
    MSG: std_msgs/String
    string data
    
    `;
  }

};

module.exports = {
  Request: set_float_valueRequest,
  Response: set_float_valueResponse
};

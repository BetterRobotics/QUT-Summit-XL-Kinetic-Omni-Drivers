// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class set_heightRequest {
  constructor() {
    this.height = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_heightRequest
    // Serialize message field [height]
    bufferInfo = _serializer.float32(obj.height, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_heightRequest
    let tmp;
    let len;
    let data = new set_heightRequest();
    // Deserialize message field [height]
    tmp = _deserializer.float32(buffer);
    data.height = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/set_heightRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '384d8dd5cbcb4f6e145e6b246fa635b2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    float32 height
    
    `;
  }

};

class set_heightResponse {
  constructor() {
    this.ret = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_heightResponse
    // Serialize message field [ret]
    bufferInfo = _serializer.bool(obj.ret, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_heightResponse
    let tmp;
    let len;
    let data = new set_heightResponse();
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
    return 'robotnik_msgs/set_heightResponse';
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
  Request: set_heightRequest,
  Response: set_heightResponse
};

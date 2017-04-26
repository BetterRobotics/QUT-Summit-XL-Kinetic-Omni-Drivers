// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class set_modeRequest {
  constructor() {
    this.mode = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_modeRequest
    // Serialize message field [mode]
    bufferInfo = _serializer.int8(obj.mode, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_modeRequest
    let tmp;
    let len;
    let data = new set_modeRequest();
    // Deserialize message field [mode]
    tmp = _deserializer.int8(buffer);
    data.mode = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/set_modeRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '418c02483a8ca57215fb7b31c5c87234';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    int8 mode
    
    `;
  }

};

class set_modeResponse {
  constructor() {
    this.ret = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_modeResponse
    // Serialize message field [ret]
    bufferInfo = _serializer.bool(obj.ret, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_modeResponse
    let tmp;
    let len;
    let data = new set_modeResponse();
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
    return 'robotnik_msgs/set_modeResponse';
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
  Request: set_modeRequest,
  Response: set_modeResponse
};

// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class get_modeRequest {
  constructor() {
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type get_modeRequest
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type get_modeRequest
    let tmp;
    let len;
    let data = new get_modeRequest();
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/get_modeRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    `;
  }

};

class get_modeResponse {
  constructor() {
    this.mode = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type get_modeResponse
    // Serialize message field [mode]
    bufferInfo = _serializer.int8(obj.mode, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type get_modeResponse
    let tmp;
    let len;
    let data = new get_modeResponse();
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
    return 'robotnik_msgs/get_modeResponse';
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

module.exports = {
  Request: get_modeRequest,
  Response: get_modeResponse
};

// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class homeRequest {
  constructor() {
    this.request = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type homeRequest
    // Serialize message field [request]
    bufferInfo = _serializer.bool(obj.request, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type homeRequest
    let tmp;
    let len;
    let data = new homeRequest();
    // Deserialize message field [request]
    tmp = _deserializer.bool(buffer);
    data.request = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/homeRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6f7e5ad6ab0ddf42c5727a195315a470';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    bool request
    
    `;
  }

};

class homeResponse {
  constructor() {
    this.ret = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type homeResponse
    // Serialize message field [ret]
    bufferInfo = _serializer.bool(obj.ret, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type homeResponse
    let tmp;
    let len;
    let data = new homeResponse();
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
    return 'robotnik_msgs/homeResponse';
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
  Request: homeRequest,
  Response: homeResponse
};

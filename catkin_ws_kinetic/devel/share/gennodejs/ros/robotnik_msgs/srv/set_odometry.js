// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class set_odometryRequest {
  constructor() {
    this.x = 0.0;
    this.y = 0.0;
    this.z = 0.0;
    this.orientation = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_odometryRequest
    // Serialize message field [x]
    bufferInfo = _serializer.float32(obj.x, bufferInfo);
    // Serialize message field [y]
    bufferInfo = _serializer.float32(obj.y, bufferInfo);
    // Serialize message field [z]
    bufferInfo = _serializer.float32(obj.z, bufferInfo);
    // Serialize message field [orientation]
    bufferInfo = _serializer.float32(obj.orientation, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_odometryRequest
    let tmp;
    let len;
    let data = new set_odometryRequest();
    // Deserialize message field [x]
    tmp = _deserializer.float32(buffer);
    data.x = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [y]
    tmp = _deserializer.float32(buffer);
    data.y = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [z]
    tmp = _deserializer.float32(buffer);
    data.z = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [orientation]
    tmp = _deserializer.float32(buffer);
    data.orientation = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/set_odometryRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b9cc91561ab081df3c838809b2058a1b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    float32 x
    
    float32 y
    
    float32 z
    
    float32 orientation
    
    `;
  }

};

class set_odometryResponse {
  constructor() {
    this.ret = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_odometryResponse
    // Serialize message field [ret]
    bufferInfo = _serializer.bool(obj.ret, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_odometryResponse
    let tmp;
    let len;
    let data = new set_odometryResponse();
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
    return 'robotnik_msgs/set_odometryResponse';
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
  Request: set_odometryRequest,
  Response: set_odometryResponse
};

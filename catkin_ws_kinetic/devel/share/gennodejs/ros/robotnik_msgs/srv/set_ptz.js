// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class set_ptzRequest {
  constructor() {
    this.pan = 0.0;
    this.tilt = 0.0;
    this.zoom = 0.0;
    this.relative = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_ptzRequest
    // Serialize message field [pan]
    bufferInfo = _serializer.float32(obj.pan, bufferInfo);
    // Serialize message field [tilt]
    bufferInfo = _serializer.float32(obj.tilt, bufferInfo);
    // Serialize message field [zoom]
    bufferInfo = _serializer.float32(obj.zoom, bufferInfo);
    // Serialize message field [relative]
    bufferInfo = _serializer.bool(obj.relative, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_ptzRequest
    let tmp;
    let len;
    let data = new set_ptzRequest();
    // Deserialize message field [pan]
    tmp = _deserializer.float32(buffer);
    data.pan = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [tilt]
    tmp = _deserializer.float32(buffer);
    data.tilt = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [zoom]
    tmp = _deserializer.float32(buffer);
    data.zoom = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [relative]
    tmp = _deserializer.bool(buffer);
    data.relative = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/set_ptzRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '84c4d3942670b5782592e834a63c50ba';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    float32 pan
    
    float32 tilt
    
    float32 zoom
    
    bool relative
    
    `;
  }

};

class set_ptzResponse {
  constructor() {
    this.ret = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type set_ptzResponse
    // Serialize message field [ret]
    bufferInfo = _serializer.bool(obj.ret, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type set_ptzResponse
    let tmp;
    let len;
    let data = new set_ptzResponse();
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
    return 'robotnik_msgs/set_ptzResponse';
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
  Request: set_ptzRequest,
  Response: set_ptzResponse
};

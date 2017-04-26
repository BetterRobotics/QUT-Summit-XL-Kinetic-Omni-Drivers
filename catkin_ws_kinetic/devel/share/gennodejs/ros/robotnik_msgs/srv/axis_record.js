// Auto-generated. Do not edit!

// (in-package robotnik_msgs.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class axis_recordRequest {
  constructor() {
    this.action = 0;
    this.directory = '';
    this.profile = '';
    this.id = '';
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type axis_recordRequest
    // Serialize message field [action]
    bufferInfo = _serializer.int8(obj.action, bufferInfo);
    // Serialize message field [directory]
    bufferInfo = _serializer.string(obj.directory, bufferInfo);
    // Serialize message field [profile]
    bufferInfo = _serializer.string(obj.profile, bufferInfo);
    // Serialize message field [id]
    bufferInfo = _serializer.string(obj.id, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type axis_recordRequest
    let tmp;
    let len;
    let data = new axis_recordRequest();
    // Deserialize message field [action]
    tmp = _deserializer.int8(buffer);
    data.action = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [directory]
    tmp = _deserializer.string(buffer);
    data.directory = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [profile]
    tmp = _deserializer.string(buffer);
    data.profile = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [id]
    tmp = _deserializer.string(buffer);
    data.id = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'robotnik_msgs/axis_recordRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '39a90fb80eeb30fd1922ed05ed1384be';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    
    int8 action
    
    string directory
    
    string profile
    
    string id
    
    `;
  }

};

class axis_recordResponse {
  constructor() {
    this.ret = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type axis_recordResponse
    // Serialize message field [ret]
    bufferInfo = _serializer.bool(obj.ret, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type axis_recordResponse
    let tmp;
    let len;
    let data = new axis_recordResponse();
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
    return 'robotnik_msgs/axis_recordResponse';
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
  Request: axis_recordRequest,
  Response: axis_recordResponse
};

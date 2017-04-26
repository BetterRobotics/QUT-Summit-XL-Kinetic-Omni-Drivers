// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class encoders {
  constructor() {
    this.type = [];
    this.counts = [];
    this.vel = [];
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type encoders
    // Serialize the length for message field [type]
    bufferInfo = _serializer.uint32(obj.type.length, bufferInfo);
    // Serialize message field [type]
    obj.type.forEach((val) => {
      bufferInfo = _serializer.string(val, bufferInfo);
    });
    // Serialize the length for message field [counts]
    bufferInfo = _serializer.uint32(obj.counts.length, bufferInfo);
    // Serialize message field [counts]
    obj.counts.forEach((val) => {
      bufferInfo = _serializer.int32(val, bufferInfo);
    });
    // Serialize the length for message field [vel]
    bufferInfo = _serializer.uint32(obj.vel.length, bufferInfo);
    // Serialize message field [vel]
    obj.vel.forEach((val) => {
      bufferInfo = _serializer.int32(val, bufferInfo);
    });
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type encoders
    let tmp;
    let len;
    let data = new encoders();
    // Deserialize array length for message field [type]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [type]
    data.type = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.string(buffer);
      data.type[i] = tmp.data;
      buffer = tmp.buffer;
    }
    // Deserialize array length for message field [counts]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [counts]
    data.counts = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.int32(buffer);
      data.counts[i] = tmp.data;
      buffer = tmp.buffer;
    }
    // Deserialize array length for message field [vel]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [vel]
    data.vel = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.int32(buffer);
      data.vel[i] = tmp.data;
      buffer = tmp.buffer;
    }
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/encoders';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b5def35e667417de284b17ffe2083938';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # 0-> right incremental, 1-> left incremental, 2-> steer absolute
    string[] type
    int32[] counts
    int32[] vel
    
    `;
  }

};

module.exports = encoders;

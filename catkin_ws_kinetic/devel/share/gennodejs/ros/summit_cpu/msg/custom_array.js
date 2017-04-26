// Auto-generated. Do not edit!

// (in-package summit_cpu.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class custom_array {
  constructor() {
    this.data = [];
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type custom_array
    // Serialize the length for message field [data]
    bufferInfo = _serializer.uint32(obj.data.length, bufferInfo);
    // Serialize message field [data]
    obj.data.forEach((val) => {
      bufferInfo = _serializer.float32(val, bufferInfo);
    });
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type custom_array
    let tmp;
    let len;
    let data = new custom_array();
    // Deserialize array length for message field [data]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [data]
    data.data = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.float32(buffer);
      data.data[i] = tmp.data;
      buffer = tmp.buffer;
    }
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'summit_cpu/custom_array';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '420cd38b6b071cd49f2970c3e2cee511';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32[] data
    
    `;
  }

};

module.exports = custom_array;

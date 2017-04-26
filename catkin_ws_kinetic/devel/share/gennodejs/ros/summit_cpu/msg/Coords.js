// Auto-generated. Do not edit!

// (in-package summit_cpu.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class Coords {
  constructor() {
    this.personpresent = false;
    this.x = 0.0;
    this.y = 0.0;
    this.z = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type Coords
    // Serialize message field [personpresent]
    bufferInfo = _serializer.bool(obj.personpresent, bufferInfo);
    // Serialize message field [x]
    bufferInfo = _serializer.float32(obj.x, bufferInfo);
    // Serialize message field [y]
    bufferInfo = _serializer.float32(obj.y, bufferInfo);
    // Serialize message field [z]
    bufferInfo = _serializer.float32(obj.z, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type Coords
    let tmp;
    let len;
    let data = new Coords();
    // Deserialize message field [personpresent]
    tmp = _deserializer.bool(buffer);
    data.personpresent = tmp.data;
    buffer = tmp.buffer;
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
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'summit_cpu/Coords';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ea3ef746517c119e7907675c643db99a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool personpresent
    float32 x
    float32 y
    float32 z
    
    `;
  }

};

module.exports = Coords;

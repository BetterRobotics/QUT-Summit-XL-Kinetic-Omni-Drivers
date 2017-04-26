// Auto-generated. Do not edit!

// (in-package summit_xl_controller.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class LimitSwitches {
  constructor() {
    this.up = false;
    this.down = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type LimitSwitches
    // Serialize message field [up]
    bufferInfo = _serializer.bool(obj.up, bufferInfo);
    // Serialize message field [down]
    bufferInfo = _serializer.bool(obj.down, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type LimitSwitches
    let tmp;
    let len;
    let data = new LimitSwitches();
    // Deserialize message field [up]
    tmp = _deserializer.bool(buffer);
    data.up = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [down]
    tmp = _deserializer.bool(buffer);
    data.down = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'summit_xl_controller/LimitSwitches';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3d014920df9acd91aa1e77d852f832f5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool up
    bool down
    
    `;
  }

};

module.exports = LimitSwitches;

// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class ptz {
  constructor() {
    this.pan = 0.0;
    this.tilt = 0.0;
    this.zoom = 0.0;
    this.relative = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type ptz
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
    //deserializes a message object of type ptz
    let tmp;
    let len;
    let data = new ptz();
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
    // Returns string type for a message object
    return 'robotnik_msgs/ptz';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '84c4d3942670b5782592e834a63c50ba';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # PAN value
    float32 pan
    # Tilt value
    float32 tilt
    # Zoom value
    float32 zoom
    # Flag for relative  movements
    bool relative
    
    
    `;
  }

};

module.exports = ptz;

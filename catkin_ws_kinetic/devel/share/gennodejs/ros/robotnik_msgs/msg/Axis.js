// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class Axis {
  constructor() {
    this.pan = 0.0;
    this.tilt = 0.0;
    this.zoom = 0.0;
    this.focus = 0.0;
    this.brightness = 0.0;
    this.iris = 0.0;
    this.autofocus = false;
    this.autoiris = false;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type Axis
    // Serialize message field [pan]
    bufferInfo = _serializer.float32(obj.pan, bufferInfo);
    // Serialize message field [tilt]
    bufferInfo = _serializer.float32(obj.tilt, bufferInfo);
    // Serialize message field [zoom]
    bufferInfo = _serializer.float32(obj.zoom, bufferInfo);
    // Serialize message field [focus]
    bufferInfo = _serializer.float32(obj.focus, bufferInfo);
    // Serialize message field [brightness]
    bufferInfo = _serializer.float32(obj.brightness, bufferInfo);
    // Serialize message field [iris]
    bufferInfo = _serializer.float32(obj.iris, bufferInfo);
    // Serialize message field [autofocus]
    bufferInfo = _serializer.bool(obj.autofocus, bufferInfo);
    // Serialize message field [autoiris]
    bufferInfo = _serializer.bool(obj.autoiris, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type Axis
    let tmp;
    let len;
    let data = new Axis();
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
    // Deserialize message field [focus]
    tmp = _deserializer.float32(buffer);
    data.focus = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [brightness]
    tmp = _deserializer.float32(buffer);
    data.brightness = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [iris]
    tmp = _deserializer.float32(buffer);
    data.iris = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [autofocus]
    tmp = _deserializer.bool(buffer);
    data.autofocus = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [autoiris]
    tmp = _deserializer.bool(buffer);
    data.autoiris = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/Axis';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e5a99fe291a5635d3f85f17b629d8088';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 pan
    float32 tilt
    float32 zoom
    float32 focus
    float32 brightness
    float32 iris
    bool autofocus
    bool autoiris
    
    `;
  }

};

module.exports = Axis;

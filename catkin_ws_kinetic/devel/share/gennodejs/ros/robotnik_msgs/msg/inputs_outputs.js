// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class inputs_outputs {
  constructor() {
    this.digital_inputs = [];
    this.digital_outputs = [];
    this.analog_inputs = [];
    this.analog_outputs = [];
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type inputs_outputs
    // Serialize the length for message field [digital_inputs]
    bufferInfo = _serializer.uint32(obj.digital_inputs.length, bufferInfo);
    // Serialize message field [digital_inputs]
    obj.digital_inputs.forEach((val) => {
      bufferInfo = _serializer.bool(val, bufferInfo);
    });
    // Serialize the length for message field [digital_outputs]
    bufferInfo = _serializer.uint32(obj.digital_outputs.length, bufferInfo);
    // Serialize message field [digital_outputs]
    obj.digital_outputs.forEach((val) => {
      bufferInfo = _serializer.bool(val, bufferInfo);
    });
    // Serialize the length for message field [analog_inputs]
    bufferInfo = _serializer.uint32(obj.analog_inputs.length, bufferInfo);
    // Serialize message field [analog_inputs]
    obj.analog_inputs.forEach((val) => {
      bufferInfo = _serializer.float32(val, bufferInfo);
    });
    // Serialize the length for message field [analog_outputs]
    bufferInfo = _serializer.uint32(obj.analog_outputs.length, bufferInfo);
    // Serialize message field [analog_outputs]
    obj.analog_outputs.forEach((val) => {
      bufferInfo = _serializer.float32(val, bufferInfo);
    });
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type inputs_outputs
    let tmp;
    let len;
    let data = new inputs_outputs();
    // Deserialize array length for message field [digital_inputs]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [digital_inputs]
    data.digital_inputs = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.bool(buffer);
      data.digital_inputs[i] = tmp.data;
      buffer = tmp.buffer;
    }
    // Deserialize array length for message field [digital_outputs]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [digital_outputs]
    data.digital_outputs = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.bool(buffer);
      data.digital_outputs[i] = tmp.data;
      buffer = tmp.buffer;
    }
    // Deserialize array length for message field [analog_inputs]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [analog_inputs]
    data.analog_inputs = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.float32(buffer);
      data.analog_inputs[i] = tmp.data;
      buffer = tmp.buffer;
    }
    // Deserialize array length for message field [analog_outputs]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [analog_outputs]
    data.analog_outputs = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.float32(buffer);
      data.analog_outputs[i] = tmp.data;
      buffer = tmp.buffer;
    }
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/inputs_outputs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '219be75bd56b8ebdca0dfa526c3803be';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool[] digital_inputs
    bool[] digital_outputs
    float32[] analog_inputs
    float32[] analog_outputs
    
    `;
  }

};

module.exports = inputs_outputs;

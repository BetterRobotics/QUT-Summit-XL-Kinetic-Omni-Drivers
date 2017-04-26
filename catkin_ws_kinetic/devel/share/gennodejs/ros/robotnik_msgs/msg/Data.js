// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class Data {
  constructor() {
    this.interface = '';
    this.bytes_sent = 0.0;
    this.bytes_received = 0.0;
    this.units_sent = '';
    this.units_received = '';
    this.packages_sent = 0;
    this.packages_received = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type Data
    // Serialize message field [interface]
    bufferInfo = _serializer.string(obj.interface, bufferInfo);
    // Serialize message field [bytes_sent]
    bufferInfo = _serializer.float32(obj.bytes_sent, bufferInfo);
    // Serialize message field [bytes_received]
    bufferInfo = _serializer.float32(obj.bytes_received, bufferInfo);
    // Serialize message field [units_sent]
    bufferInfo = _serializer.string(obj.units_sent, bufferInfo);
    // Serialize message field [units_received]
    bufferInfo = _serializer.string(obj.units_received, bufferInfo);
    // Serialize message field [packages_sent]
    bufferInfo = _serializer.int32(obj.packages_sent, bufferInfo);
    // Serialize message field [packages_received]
    bufferInfo = _serializer.int32(obj.packages_received, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type Data
    let tmp;
    let len;
    let data = new Data();
    // Deserialize message field [interface]
    tmp = _deserializer.string(buffer);
    data.interface = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [bytes_sent]
    tmp = _deserializer.float32(buffer);
    data.bytes_sent = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [bytes_received]
    tmp = _deserializer.float32(buffer);
    data.bytes_received = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [units_sent]
    tmp = _deserializer.string(buffer);
    data.units_sent = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [units_received]
    tmp = _deserializer.string(buffer);
    data.units_received = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [packages_sent]
    tmp = _deserializer.int32(buffer);
    data.packages_sent = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [packages_received]
    tmp = _deserializer.int32(buffer);
    data.packages_received = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/Data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'beae478f52d7795f673d8edc9e4295a2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string interface
    float32 bytes_sent
    float32 bytes_received
    string units_sent
    string units_received
    int32 packages_sent
    int32 packages_received
    
    
    `;
  }

};

module.exports = Data;

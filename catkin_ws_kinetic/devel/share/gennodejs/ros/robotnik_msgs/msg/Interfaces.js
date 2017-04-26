// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');
let Data = require('./Data.js');

//-----------------------------------------------------------

class Interfaces {
  constructor() {
    this.total = new Data();
    this.interfaces = [];
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type Interfaces
    // Serialize message field [total]
    bufferInfo = Data.serialize(obj.total, bufferInfo);
    // Serialize the length for message field [interfaces]
    bufferInfo = _serializer.uint32(obj.interfaces.length, bufferInfo);
    // Serialize message field [interfaces]
    obj.interfaces.forEach((val) => {
      bufferInfo = Data.serialize(val, bufferInfo);
    });
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type Interfaces
    let tmp;
    let len;
    let data = new Interfaces();
    // Deserialize message field [total]
    tmp = Data.deserialize(buffer);
    data.total = tmp.data;
    buffer = tmp.buffer;
    // Deserialize array length for message field [interfaces]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [interfaces]
    data.interfaces = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = Data.deserialize(buffer);
      data.interfaces[i] = tmp.data;
      buffer = tmp.buffer;
    }
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/Interfaces';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2cae798f4cdadfdb2326b84ac55dc3ea';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Contains the total number of bytes and pkts
    Data total
    # Contains information of every interface
    Data[] interfaces
    
    
    ================================================================================
    MSG: robotnik_msgs/Data
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

module.exports = Interfaces;

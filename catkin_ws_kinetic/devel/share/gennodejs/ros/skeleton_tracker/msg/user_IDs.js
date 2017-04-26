// Auto-generated. Do not edit!

// (in-package skeleton_tracker.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class user_IDs {
  constructor() {
    this.users = [];
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type user_IDs
    // Serialize the length for message field [users]
    bufferInfo = _serializer.uint32(obj.users.length, bufferInfo);
    // Serialize message field [users]
    bufferInfo.buffer.push(obj.users);
    bufferInfo.length += obj.users.length;
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type user_IDs
    let tmp;
    let len;
    let data = new user_IDs();
    // Deserialize array length for message field [users]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [users]
    data.users = buffer.slice(0, len);
    buffer =  buffer.slice(len);
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'skeleton_tracker/user_IDs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0370fea64fb82134b7a78a66cb25797c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8[] users
    `;
  }

};

module.exports = user_IDs;

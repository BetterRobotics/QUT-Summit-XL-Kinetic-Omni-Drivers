// Auto-generated. Do not edit!

// (in-package summit_xl_web.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class RecordVideoRequest {
  constructor() {
    this.startRecording = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type RecordVideoRequest
    // Serialize message field [startRecording]
    bufferInfo = _serializer.int16(obj.startRecording, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type RecordVideoRequest
    let tmp;
    let len;
    let data = new RecordVideoRequest();
    // Deserialize message field [startRecording]
    tmp = _deserializer.int16(buffer);
    data.startRecording = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'summit_xl_web/RecordVideoRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8ea5cfe0d00a46593d72b2f1e782e82f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 startRecording
    
    `;
  }

};

class RecordVideoResponse {
  constructor() {
    this.filename = '';
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type RecordVideoResponse
    // Serialize message field [filename]
    bufferInfo = _serializer.string(obj.filename, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type RecordVideoResponse
    let tmp;
    let len;
    let data = new RecordVideoResponse();
    // Deserialize message field [filename]
    tmp = _deserializer.string(buffer);
    data.filename = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'summit_xl_web/RecordVideoResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '030824f52a0628ead956fb9d67e66ae9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string filename
    
    
    `;
  }

};

module.exports = {
  Request: RecordVideoRequest,
  Response: RecordVideoResponse
};

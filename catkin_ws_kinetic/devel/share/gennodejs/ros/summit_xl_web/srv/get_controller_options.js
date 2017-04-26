// Auto-generated. Do not edit!

// (in-package summit_xl_web.srv)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class get_controller_optionsRequest {
  constructor() {
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type get_controller_optionsRequest
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type get_controller_optionsRequest
    let tmp;
    let len;
    let data = new get_controller_optionsRequest();
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'summit_xl_web/get_controller_optionsRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    `;
  }

};

class get_controller_optionsResponse {
  constructor() {
    this.takeOver = false;
    this.kinematicMode = '';
    this.gearboxReduction = 0.0;
    this.diameterWheel = 0.0;
    this.motionOdometry = '';
    this.motorsEncoder = '';
    this.motorsEncoderFactor = 0;
    this.xWam = '';
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type get_controller_optionsResponse
    // Serialize message field [takeOver]
    bufferInfo = _serializer.bool(obj.takeOver, bufferInfo);
    // Serialize message field [kinematicMode]
    bufferInfo = _serializer.string(obj.kinematicMode, bufferInfo);
    // Serialize message field [gearboxReduction]
    bufferInfo = _serializer.float32(obj.gearboxReduction, bufferInfo);
    // Serialize message field [diameterWheel]
    bufferInfo = _serializer.float32(obj.diameterWheel, bufferInfo);
    // Serialize message field [motionOdometry]
    bufferInfo = _serializer.string(obj.motionOdometry, bufferInfo);
    // Serialize message field [motorsEncoder]
    bufferInfo = _serializer.string(obj.motorsEncoder, bufferInfo);
    // Serialize message field [motorsEncoderFactor]
    bufferInfo = _serializer.int32(obj.motorsEncoderFactor, bufferInfo);
    // Serialize message field [xWam]
    bufferInfo = _serializer.string(obj.xWam, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type get_controller_optionsResponse
    let tmp;
    let len;
    let data = new get_controller_optionsResponse();
    // Deserialize message field [takeOver]
    tmp = _deserializer.bool(buffer);
    data.takeOver = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [kinematicMode]
    tmp = _deserializer.string(buffer);
    data.kinematicMode = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [gearboxReduction]
    tmp = _deserializer.float32(buffer);
    data.gearboxReduction = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [diameterWheel]
    tmp = _deserializer.float32(buffer);
    data.diameterWheel = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [motionOdometry]
    tmp = _deserializer.string(buffer);
    data.motionOdometry = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [motorsEncoder]
    tmp = _deserializer.string(buffer);
    data.motorsEncoder = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [motorsEncoderFactor]
    tmp = _deserializer.int32(buffer);
    data.motorsEncoderFactor = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [xWam]
    tmp = _deserializer.string(buffer);
    data.xWam = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a service object
    return 'summit_xl_web/get_controller_optionsResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c803d4442092d317a92118964b891b96';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool takeOver
    string kinematicMode
    float32 gearboxReduction
    float32 diameterWheel
    string motionOdometry
    string motorsEncoder
    int32  motorsEncoderFactor
    string xWam
    
    
    `;
  }

};

module.exports = {
  Request: get_controller_optionsRequest,
  Response: get_controller_optionsResponse
};

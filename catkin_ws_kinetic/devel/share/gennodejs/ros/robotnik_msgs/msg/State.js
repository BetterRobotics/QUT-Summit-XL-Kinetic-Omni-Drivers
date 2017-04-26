// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class State {
  constructor() {
    this.state = 0;
    this.desired_freq = 0.0;
    this.real_freq = 0.0;
    this.state_description = '';
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type State
    // Serialize message field [state]
    bufferInfo = _serializer.int32(obj.state, bufferInfo);
    // Serialize message field [desired_freq]
    bufferInfo = _serializer.float32(obj.desired_freq, bufferInfo);
    // Serialize message field [real_freq]
    bufferInfo = _serializer.float32(obj.real_freq, bufferInfo);
    // Serialize message field [state_description]
    bufferInfo = _serializer.string(obj.state_description, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type State
    let tmp;
    let len;
    let data = new State();
    // Deserialize message field [state]
    tmp = _deserializer.int32(buffer);
    data.state = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [desired_freq]
    tmp = _deserializer.float32(buffer);
    data.desired_freq = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [real_freq]
    tmp = _deserializer.float32(buffer);
    data.real_freq = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [state_description]
    tmp = _deserializer.string(buffer);
    data.state_description = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/State';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b3a486e7c5d573e5d1475cd7c02a518b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # constants
    int32 INIT_STATE = 100
    int32 STANDBY_STATE = 200
    int32 READY_STATE = 300
    int32 EMERGENCY_STATE = 400
    int32 FAILURE_STATE = 500
    int32 SHUTDOWN_STATE = 600
    int32 UNKOWN_STATE = 700
    
    # state of the component
    int32 state
    # desired control loop frecuency
    float32 desired_freq
    # real frecuency 
    float32 real_freq
    # Description of the state
    string state_description
    
    `;
  }

};

// Constants for message
State.Constants = {
  INIT_STATE: 100,
  STANDBY_STATE: 200,
  READY_STATE: 300,
  EMERGENCY_STATE: 400,
  FAILURE_STATE: 500,
  SHUTDOWN_STATE: 600,
  UNKOWN_STATE: 700,
}

module.exports = State;

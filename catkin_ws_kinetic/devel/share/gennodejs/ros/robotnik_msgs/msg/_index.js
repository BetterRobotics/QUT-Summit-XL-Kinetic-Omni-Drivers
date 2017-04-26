
"use strict";

let ptz = require('./ptz.js');
let Interfaces = require('./Interfaces.js');
let MotorsStatusDifferential = require('./MotorsStatusDifferential.js');
let MotorsStatus = require('./MotorsStatus.js');
let Alarms = require('./Alarms.js');
let State = require('./State.js');
let AlarmSensor = require('./AlarmSensor.js');
let inputs_outputs = require('./inputs_outputs.js');
let MotorStatus = require('./MotorStatus.js');
let encoders = require('./encoders.js');
let BatteryStatus = require('./BatteryStatus.js');
let Data = require('./Data.js');
let Axis = require('./Axis.js');

module.exports = {
  ptz: ptz,
  Interfaces: Interfaces,
  MotorsStatusDifferential: MotorsStatusDifferential,
  MotorsStatus: MotorsStatus,
  Alarms: Alarms,
  State: State,
  AlarmSensor: AlarmSensor,
  inputs_outputs: inputs_outputs,
  MotorStatus: MotorStatus,
  encoders: encoders,
  BatteryStatus: BatteryStatus,
  Data: Data,
  Axis: Axis,
};

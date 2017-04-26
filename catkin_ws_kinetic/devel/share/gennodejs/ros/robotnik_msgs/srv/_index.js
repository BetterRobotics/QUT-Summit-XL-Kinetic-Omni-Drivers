
"use strict";

let set_float_value = require('./set_float_value.js')
let enable_disable = require('./enable_disable.js')
let set_ptz = require('./set_ptz.js')
let get_digital_input = require('./get_digital_input.js')
let axis_record = require('./axis_record.js')
let set_odometry = require('./set_odometry.js')
let set_analog_output = require('./set_analog_output.js')
let set_digital_output = require('./set_digital_output.js')
let set_height = require('./set_height.js')
let set_mode = require('./set_mode.js')
let home = require('./home.js')
let get_mode = require('./get_mode.js')

module.exports = {
  set_float_value: set_float_value,
  enable_disable: enable_disable,
  set_ptz: set_ptz,
  get_digital_input: get_digital_input,
  axis_record: axis_record,
  set_odometry: set_odometry,
  set_analog_output: set_analog_output,
  set_digital_output: set_digital_output,
  set_height: set_height,
  set_mode: set_mode,
  home: home,
  get_mode: get_mode,
};

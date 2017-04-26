// Auto-generated. Do not edit!

// (in-package summit_cpu.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');
let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------

class Images {
  constructor() {
    this.rgb = new sensor_msgs.msg.Image();
    this.depth = new sensor_msgs.msg.Image();
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type Images
    // Serialize message field [rgb]
    bufferInfo = sensor_msgs.msg.Image.serialize(obj.rgb, bufferInfo);
    // Serialize message field [depth]
    bufferInfo = sensor_msgs.msg.Image.serialize(obj.depth, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type Images
    let tmp;
    let len;
    let data = new Images();
    // Deserialize message field [rgb]
    tmp = sensor_msgs.msg.Image.deserialize(buffer);
    data.rgb = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [depth]
    tmp = sensor_msgs.msg.Image.deserialize(buffer);
    data.depth = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'summit_cpu/Images';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9ec11a40b1735995342c0a7969784331';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    sensor_msgs/Image rgb
    sensor_msgs/Image depth
    
    ================================================================================
    MSG: sensor_msgs/Image
    # This message contains an uncompressed image
    # (0, 0) is at top-left corner of image
    #
    
    Header header        # Header timestamp should be acquisition time of image
                         # Header frame_id should be optical frame of camera
                         # origin of frame should be optical center of cameara
                         # +x should point to the right in the image
                         # +y should point down in the image
                         # +z should point into to plane of the image
                         # If the frame_id here and the frame_id of the CameraInfo
                         # message associated with the image conflict
                         # the behavior is undefined
    
    uint32 height         # image height, that is, number of rows
    uint32 width          # image width, that is, number of columns
    
    # The legal values for encoding are in file src/image_encodings.cpp
    # If you want to standardize a new string format, join
    # ros-users@lists.sourceforge.net and send an email proposing a new encoding.
    
    string encoding       # Encoding of pixels -- channel meaning, ordering, size
                          # taken from the list of strings in include/sensor_msgs/image_encodings.h
    
    uint8 is_bigendian    # is this data bigendian?
    uint32 step           # Full row length in bytes
    uint8[] data          # actual matrix data, size is (step * rows)
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    `;
  }

};

module.exports = Images;

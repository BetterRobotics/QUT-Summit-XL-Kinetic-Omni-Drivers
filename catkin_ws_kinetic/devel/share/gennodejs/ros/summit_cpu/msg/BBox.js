// Auto-generated. Do not edit!

// (in-package summit_cpu.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');
let sensor_msgs = _finder('sensor_msgs');

//-----------------------------------------------------------

class BBox {
  constructor() {
    this.image = new sensor_msgs.msg.Image();
    this.person = false;
    this.lx = 0;
    this.ux = 0;
    this.ly = 0;
    this.uy = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type BBox
    // Serialize message field [image]
    bufferInfo = sensor_msgs.msg.Image.serialize(obj.image, bufferInfo);
    // Serialize message field [person]
    bufferInfo = _serializer.bool(obj.person, bufferInfo);
    // Serialize message field [lx]
    bufferInfo = _serializer.int16(obj.lx, bufferInfo);
    // Serialize message field [ux]
    bufferInfo = _serializer.int16(obj.ux, bufferInfo);
    // Serialize message field [ly]
    bufferInfo = _serializer.int16(obj.ly, bufferInfo);
    // Serialize message field [uy]
    bufferInfo = _serializer.int16(obj.uy, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type BBox
    let tmp;
    let len;
    let data = new BBox();
    // Deserialize message field [image]
    tmp = sensor_msgs.msg.Image.deserialize(buffer);
    data.image = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [person]
    tmp = _deserializer.bool(buffer);
    data.person = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [lx]
    tmp = _deserializer.int16(buffer);
    data.lx = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [ux]
    tmp = _deserializer.int16(buffer);
    data.ux = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [ly]
    tmp = _deserializer.int16(buffer);
    data.ly = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [uy]
    tmp = _deserializer.int16(buffer);
    data.uy = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'summit_cpu/BBox';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9f54c175d8115e3773b15498f0018b75';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    sensor_msgs/Image image
    bool person
    int16 lx
    int16 ux
    int16 ly
    int16 uy
    
    
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

module.exports = BBox;

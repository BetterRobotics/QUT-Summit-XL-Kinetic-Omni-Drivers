; Auto-generated. Do not edit!


(cl:in-package summit_cpu-msg)


;//! \htmlinclude BBox.msg.html

(cl:defclass <BBox> (roslisp-msg-protocol:ros-message)
  ((image
    :reader image
    :initarg :image
    :type sensor_msgs-msg:Image
    :initform (cl:make-instance 'sensor_msgs-msg:Image))
   (person
    :reader person
    :initarg :person
    :type cl:boolean
    :initform cl:nil)
   (lx
    :reader lx
    :initarg :lx
    :type cl:fixnum
    :initform 0)
   (ux
    :reader ux
    :initarg :ux
    :type cl:fixnum
    :initform 0)
   (ly
    :reader ly
    :initarg :ly
    :type cl:fixnum
    :initform 0)
   (uy
    :reader uy
    :initarg :uy
    :type cl:fixnum
    :initform 0))
)

(cl:defclass BBox (<BBox>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BBox>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BBox)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name summit_cpu-msg:<BBox> is deprecated: use summit_cpu-msg:BBox instead.")))

(cl:ensure-generic-function 'image-val :lambda-list '(m))
(cl:defmethod image-val ((m <BBox>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:image-val is deprecated.  Use summit_cpu-msg:image instead.")
  (image m))

(cl:ensure-generic-function 'person-val :lambda-list '(m))
(cl:defmethod person-val ((m <BBox>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:person-val is deprecated.  Use summit_cpu-msg:person instead.")
  (person m))

(cl:ensure-generic-function 'lx-val :lambda-list '(m))
(cl:defmethod lx-val ((m <BBox>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:lx-val is deprecated.  Use summit_cpu-msg:lx instead.")
  (lx m))

(cl:ensure-generic-function 'ux-val :lambda-list '(m))
(cl:defmethod ux-val ((m <BBox>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:ux-val is deprecated.  Use summit_cpu-msg:ux instead.")
  (ux m))

(cl:ensure-generic-function 'ly-val :lambda-list '(m))
(cl:defmethod ly-val ((m <BBox>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:ly-val is deprecated.  Use summit_cpu-msg:ly instead.")
  (ly m))

(cl:ensure-generic-function 'uy-val :lambda-list '(m))
(cl:defmethod uy-val ((m <BBox>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:uy-val is deprecated.  Use summit_cpu-msg:uy instead.")
  (uy m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BBox>) ostream)
  "Serializes a message object of type '<BBox>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'image) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'person) 1 0)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'lx)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'ux)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'ly)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'uy)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BBox>) istream)
  "Deserializes a message object of type '<BBox>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'image) istream)
    (cl:setf (cl:slot-value msg 'person) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'lx) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ux) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ly) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'uy) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BBox>)))
  "Returns string type for a message object of type '<BBox>"
  "summit_cpu/BBox")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BBox)))
  "Returns string type for a message object of type 'BBox"
  "summit_cpu/BBox")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BBox>)))
  "Returns md5sum for a message object of type '<BBox>"
  "9f54c175d8115e3773b15498f0018b75")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BBox)))
  "Returns md5sum for a message object of type 'BBox"
  "9f54c175d8115e3773b15498f0018b75")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BBox>)))
  "Returns full string definition for message of type '<BBox>"
  (cl:format cl:nil "sensor_msgs/Image image~%bool person~%int16 lx~%int16 ux~%int16 ly~%int16 uy~%~%~%================================================================================~%MSG: sensor_msgs/Image~%# This message contains an uncompressed image~%# (0, 0) is at top-left corner of image~%#~%~%Header header        # Header timestamp should be acquisition time of image~%                     # Header frame_id should be optical frame of camera~%                     # origin of frame should be optical center of cameara~%                     # +x should point to the right in the image~%                     # +y should point down in the image~%                     # +z should point into to plane of the image~%                     # If the frame_id here and the frame_id of the CameraInfo~%                     # message associated with the image conflict~%                     # the behavior is undefined~%~%uint32 height         # image height, that is, number of rows~%uint32 width          # image width, that is, number of columns~%~%# The legal values for encoding are in file src/image_encodings.cpp~%# If you want to standardize a new string format, join~%# ros-users@lists.sourceforge.net and send an email proposing a new encoding.~%~%string encoding       # Encoding of pixels -- channel meaning, ordering, size~%                      # taken from the list of strings in include/sensor_msgs/image_encodings.h~%~%uint8 is_bigendian    # is this data bigendian?~%uint32 step           # Full row length in bytes~%uint8[] data          # actual matrix data, size is (step * rows)~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BBox)))
  "Returns full string definition for message of type 'BBox"
  (cl:format cl:nil "sensor_msgs/Image image~%bool person~%int16 lx~%int16 ux~%int16 ly~%int16 uy~%~%~%================================================================================~%MSG: sensor_msgs/Image~%# This message contains an uncompressed image~%# (0, 0) is at top-left corner of image~%#~%~%Header header        # Header timestamp should be acquisition time of image~%                     # Header frame_id should be optical frame of camera~%                     # origin of frame should be optical center of cameara~%                     # +x should point to the right in the image~%                     # +y should point down in the image~%                     # +z should point into to plane of the image~%                     # If the frame_id here and the frame_id of the CameraInfo~%                     # message associated with the image conflict~%                     # the behavior is undefined~%~%uint32 height         # image height, that is, number of rows~%uint32 width          # image width, that is, number of columns~%~%# The legal values for encoding are in file src/image_encodings.cpp~%# If you want to standardize a new string format, join~%# ros-users@lists.sourceforge.net and send an email proposing a new encoding.~%~%string encoding       # Encoding of pixels -- channel meaning, ordering, size~%                      # taken from the list of strings in include/sensor_msgs/image_encodings.h~%~%uint8 is_bigendian    # is this data bigendian?~%uint32 step           # Full row length in bytes~%uint8[] data          # actual matrix data, size is (step * rows)~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BBox>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'image))
     1
     2
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BBox>))
  "Converts a ROS message object to a list"
  (cl:list 'BBox
    (cl:cons ':image (image msg))
    (cl:cons ':person (person msg))
    (cl:cons ':lx (lx msg))
    (cl:cons ':ux (ux msg))
    (cl:cons ':ly (ly msg))
    (cl:cons ':uy (uy msg))
))

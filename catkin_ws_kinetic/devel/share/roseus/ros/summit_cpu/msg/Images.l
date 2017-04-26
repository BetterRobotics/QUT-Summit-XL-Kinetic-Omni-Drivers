;; Auto-generated. Do not edit!


(when (boundp 'summit_cpu::Images)
  (if (not (find-package "SUMMIT_CPU"))
    (make-package "SUMMIT_CPU"))
  (shadow 'Images (find-package "SUMMIT_CPU")))
(unless (find-package "SUMMIT_CPU::IMAGES")
  (make-package "SUMMIT_CPU::IMAGES"))

(in-package "ROS")
;;//! \htmlinclude Images.msg.html
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(defclass summit_cpu::Images
  :super ros::object
  :slots (_rgb _depth ))

(defmethod summit_cpu::Images
  (:init
   (&key
    ((:rgb __rgb) (instance sensor_msgs::Image :init))
    ((:depth __depth) (instance sensor_msgs::Image :init))
    )
   (send-super :init)
   (setq _rgb __rgb)
   (setq _depth __depth)
   self)
  (:rgb
   (&rest __rgb)
   (if (keywordp (car __rgb))
       (send* _rgb __rgb)
     (progn
       (if __rgb (setq _rgb (car __rgb)))
       _rgb)))
  (:depth
   (&rest __depth)
   (if (keywordp (car __depth))
       (send* _depth __depth)
     (progn
       (if __depth (setq _depth (car __depth)))
       _depth)))
  (:serialization-length
   ()
   (+
    ;; sensor_msgs/Image _rgb
    (send _rgb :serialization-length)
    ;; sensor_msgs/Image _depth
    (send _depth :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; sensor_msgs/Image _rgb
       (send _rgb :serialize s)
     ;; sensor_msgs/Image _depth
       (send _depth :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; sensor_msgs/Image _rgb
     (send _rgb :deserialize buf ptr-) (incf ptr- (send _rgb :serialization-length))
   ;; sensor_msgs/Image _depth
     (send _depth :deserialize buf ptr-) (incf ptr- (send _depth :serialization-length))
   ;;
   self)
  )

(setf (get summit_cpu::Images :md5sum-) "9ec11a40b1735995342c0a7969784331")
(setf (get summit_cpu::Images :datatype-) "summit_cpu/Images")
(setf (get summit_cpu::Images :definition-)
      "sensor_msgs/Image rgb
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

")



(provide :summit_cpu/Images "9ec11a40b1735995342c0a7969784331")



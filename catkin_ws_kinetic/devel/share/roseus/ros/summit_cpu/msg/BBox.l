;; Auto-generated. Do not edit!


(when (boundp 'summit_cpu::BBox)
  (if (not (find-package "SUMMIT_CPU"))
    (make-package "SUMMIT_CPU"))
  (shadow 'BBox (find-package "SUMMIT_CPU")))
(unless (find-package "SUMMIT_CPU::BBOX")
  (make-package "SUMMIT_CPU::BBOX"))

(in-package "ROS")
;;//! \htmlinclude BBox.msg.html
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(defclass summit_cpu::BBox
  :super ros::object
  :slots (_image _person _lx _ux _ly _uy ))

(defmethod summit_cpu::BBox
  (:init
   (&key
    ((:image __image) (instance sensor_msgs::Image :init))
    ((:person __person) nil)
    ((:lx __lx) 0)
    ((:ux __ux) 0)
    ((:ly __ly) 0)
    ((:uy __uy) 0)
    )
   (send-super :init)
   (setq _image __image)
   (setq _person __person)
   (setq _lx (round __lx))
   (setq _ux (round __ux))
   (setq _ly (round __ly))
   (setq _uy (round __uy))
   self)
  (:image
   (&rest __image)
   (if (keywordp (car __image))
       (send* _image __image)
     (progn
       (if __image (setq _image (car __image)))
       _image)))
  (:person
   (&optional __person)
   (if __person (setq _person __person)) _person)
  (:lx
   (&optional __lx)
   (if __lx (setq _lx __lx)) _lx)
  (:ux
   (&optional __ux)
   (if __ux (setq _ux __ux)) _ux)
  (:ly
   (&optional __ly)
   (if __ly (setq _ly __ly)) _ly)
  (:uy
   (&optional __uy)
   (if __uy (setq _uy __uy)) _uy)
  (:serialization-length
   ()
   (+
    ;; sensor_msgs/Image _image
    (send _image :serialization-length)
    ;; bool _person
    1
    ;; int16 _lx
    2
    ;; int16 _ux
    2
    ;; int16 _ly
    2
    ;; int16 _uy
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; sensor_msgs/Image _image
       (send _image :serialize s)
     ;; bool _person
       (if _person (write-byte -1 s) (write-byte 0 s))
     ;; int16 _lx
       (write-word _lx s)
     ;; int16 _ux
       (write-word _ux s)
     ;; int16 _ly
       (write-word _ly s)
     ;; int16 _uy
       (write-word _uy s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; sensor_msgs/Image _image
     (send _image :deserialize buf ptr-) (incf ptr- (send _image :serialization-length))
   ;; bool _person
     (setq _person (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; int16 _lx
     (setq _lx (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _ux
     (setq _ux (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _ly
     (setq _ly (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _uy
     (setq _uy (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get summit_cpu::BBox :md5sum-) "9f54c175d8115e3773b15498f0018b75")
(setf (get summit_cpu::BBox :datatype-) "summit_cpu/BBox")
(setf (get summit_cpu::BBox :definition-)
      "sensor_msgs/Image image
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

")



(provide :summit_cpu/BBox "9f54c175d8115e3773b15498f0018b75")



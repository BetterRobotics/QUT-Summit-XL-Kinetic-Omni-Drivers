; Auto-generated. Do not edit!


(cl:in-package summit_xl_controller-msg)


;//! \htmlinclude LimitSwitches.msg.html

(cl:defclass <LimitSwitches> (roslisp-msg-protocol:ros-message)
  ((up
    :reader up
    :initarg :up
    :type cl:boolean
    :initform cl:nil)
   (down
    :reader down
    :initarg :down
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass LimitSwitches (<LimitSwitches>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LimitSwitches>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LimitSwitches)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name summit_xl_controller-msg:<LimitSwitches> is deprecated: use summit_xl_controller-msg:LimitSwitches instead.")))

(cl:ensure-generic-function 'up-val :lambda-list '(m))
(cl:defmethod up-val ((m <LimitSwitches>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_controller-msg:up-val is deprecated.  Use summit_xl_controller-msg:up instead.")
  (up m))

(cl:ensure-generic-function 'down-val :lambda-list '(m))
(cl:defmethod down-val ((m <LimitSwitches>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_controller-msg:down-val is deprecated.  Use summit_xl_controller-msg:down instead.")
  (down m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LimitSwitches>) ostream)
  "Serializes a message object of type '<LimitSwitches>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'up) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'down) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LimitSwitches>) istream)
  "Deserializes a message object of type '<LimitSwitches>"
    (cl:setf (cl:slot-value msg 'up) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'down) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LimitSwitches>)))
  "Returns string type for a message object of type '<LimitSwitches>"
  "summit_xl_controller/LimitSwitches")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LimitSwitches)))
  "Returns string type for a message object of type 'LimitSwitches"
  "summit_xl_controller/LimitSwitches")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LimitSwitches>)))
  "Returns md5sum for a message object of type '<LimitSwitches>"
  "3d014920df9acd91aa1e77d852f832f5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LimitSwitches)))
  "Returns md5sum for a message object of type 'LimitSwitches"
  "3d014920df9acd91aa1e77d852f832f5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LimitSwitches>)))
  "Returns full string definition for message of type '<LimitSwitches>"
  (cl:format cl:nil "bool up~%bool down~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LimitSwitches)))
  "Returns full string definition for message of type 'LimitSwitches"
  (cl:format cl:nil "bool up~%bool down~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LimitSwitches>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LimitSwitches>))
  "Converts a ROS message object to a list"
  (cl:list 'LimitSwitches
    (cl:cons ':up (up msg))
    (cl:cons ':down (down msg))
))

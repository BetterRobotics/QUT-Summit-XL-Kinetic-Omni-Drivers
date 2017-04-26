; Auto-generated. Do not edit!


(cl:in-package summit_xl_web-srv)


;//! \htmlinclude set_controller_options-request.msg.html

(cl:defclass <set_controller_options-request> (roslisp-msg-protocol:ros-message)
  ((takeOver
    :reader takeOver
    :initarg :takeOver
    :type cl:boolean
    :initform cl:nil)
   (kinematicMode
    :reader kinematicMode
    :initarg :kinematicMode
    :type cl:string
    :initform "")
   (gearboxReduction
    :reader gearboxReduction
    :initarg :gearboxReduction
    :type cl:float
    :initform 0.0)
   (diameterWheel
    :reader diameterWheel
    :initarg :diameterWheel
    :type cl:float
    :initform 0.0)
   (motionOdometry
    :reader motionOdometry
    :initarg :motionOdometry
    :type cl:string
    :initform "")
   (motorsEncoder
    :reader motorsEncoder
    :initarg :motorsEncoder
    :type cl:string
    :initform "")
   (motorsEncoderFactor
    :reader motorsEncoderFactor
    :initarg :motorsEncoderFactor
    :type cl:integer
    :initform 0)
   (xWam
    :reader xWam
    :initarg :xWam
    :type cl:string
    :initform ""))
)

(cl:defclass set_controller_options-request (<set_controller_options-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <set_controller_options-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'set_controller_options-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name summit_xl_web-srv:<set_controller_options-request> is deprecated: use summit_xl_web-srv:set_controller_options-request instead.")))

(cl:ensure-generic-function 'takeOver-val :lambda-list '(m))
(cl:defmethod takeOver-val ((m <set_controller_options-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:takeOver-val is deprecated.  Use summit_xl_web-srv:takeOver instead.")
  (takeOver m))

(cl:ensure-generic-function 'kinematicMode-val :lambda-list '(m))
(cl:defmethod kinematicMode-val ((m <set_controller_options-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:kinematicMode-val is deprecated.  Use summit_xl_web-srv:kinematicMode instead.")
  (kinematicMode m))

(cl:ensure-generic-function 'gearboxReduction-val :lambda-list '(m))
(cl:defmethod gearboxReduction-val ((m <set_controller_options-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:gearboxReduction-val is deprecated.  Use summit_xl_web-srv:gearboxReduction instead.")
  (gearboxReduction m))

(cl:ensure-generic-function 'diameterWheel-val :lambda-list '(m))
(cl:defmethod diameterWheel-val ((m <set_controller_options-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:diameterWheel-val is deprecated.  Use summit_xl_web-srv:diameterWheel instead.")
  (diameterWheel m))

(cl:ensure-generic-function 'motionOdometry-val :lambda-list '(m))
(cl:defmethod motionOdometry-val ((m <set_controller_options-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:motionOdometry-val is deprecated.  Use summit_xl_web-srv:motionOdometry instead.")
  (motionOdometry m))

(cl:ensure-generic-function 'motorsEncoder-val :lambda-list '(m))
(cl:defmethod motorsEncoder-val ((m <set_controller_options-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:motorsEncoder-val is deprecated.  Use summit_xl_web-srv:motorsEncoder instead.")
  (motorsEncoder m))

(cl:ensure-generic-function 'motorsEncoderFactor-val :lambda-list '(m))
(cl:defmethod motorsEncoderFactor-val ((m <set_controller_options-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:motorsEncoderFactor-val is deprecated.  Use summit_xl_web-srv:motorsEncoderFactor instead.")
  (motorsEncoderFactor m))

(cl:ensure-generic-function 'xWam-val :lambda-list '(m))
(cl:defmethod xWam-val ((m <set_controller_options-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:xWam-val is deprecated.  Use summit_xl_web-srv:xWam instead.")
  (xWam m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <set_controller_options-request>) ostream)
  "Serializes a message object of type '<set_controller_options-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'takeOver) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'kinematicMode))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'kinematicMode))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'gearboxReduction))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'diameterWheel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'motionOdometry))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'motionOdometry))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'motorsEncoder))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'motorsEncoder))
  (cl:let* ((signed (cl:slot-value msg 'motorsEncoderFactor)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'xWam))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'xWam))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <set_controller_options-request>) istream)
  "Deserializes a message object of type '<set_controller_options-request>"
    (cl:setf (cl:slot-value msg 'takeOver) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'kinematicMode) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'kinematicMode) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'gearboxReduction) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'diameterWheel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'motionOdometry) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'motionOdometry) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'motorsEncoder) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'motorsEncoder) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'motorsEncoderFactor) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'xWam) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'xWam) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<set_controller_options-request>)))
  "Returns string type for a service object of type '<set_controller_options-request>"
  "summit_xl_web/set_controller_optionsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_controller_options-request)))
  "Returns string type for a service object of type 'set_controller_options-request"
  "summit_xl_web/set_controller_optionsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<set_controller_options-request>)))
  "Returns md5sum for a message object of type '<set_controller_options-request>"
  "a51599e3b48803a1fc4a68757b75ae38")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'set_controller_options-request)))
  "Returns md5sum for a message object of type 'set_controller_options-request"
  "a51599e3b48803a1fc4a68757b75ae38")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<set_controller_options-request>)))
  "Returns full string definition for message of type '<set_controller_options-request>"
  (cl:format cl:nil "bool takeOver~%string kinematicMode~%float32 gearboxReduction~%float32 diameterWheel~%string motionOdometry~%string motorsEncoder~%int32  motorsEncoderFactor~%string xWam~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'set_controller_options-request)))
  "Returns full string definition for message of type 'set_controller_options-request"
  (cl:format cl:nil "bool takeOver~%string kinematicMode~%float32 gearboxReduction~%float32 diameterWheel~%string motionOdometry~%string motorsEncoder~%int32  motorsEncoderFactor~%string xWam~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <set_controller_options-request>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'kinematicMode))
     4
     4
     4 (cl:length (cl:slot-value msg 'motionOdometry))
     4 (cl:length (cl:slot-value msg 'motorsEncoder))
     4
     4 (cl:length (cl:slot-value msg 'xWam))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <set_controller_options-request>))
  "Converts a ROS message object to a list"
  (cl:list 'set_controller_options-request
    (cl:cons ':takeOver (takeOver msg))
    (cl:cons ':kinematicMode (kinematicMode msg))
    (cl:cons ':gearboxReduction (gearboxReduction msg))
    (cl:cons ':diameterWheel (diameterWheel msg))
    (cl:cons ':motionOdometry (motionOdometry msg))
    (cl:cons ':motorsEncoder (motorsEncoder msg))
    (cl:cons ':motorsEncoderFactor (motorsEncoderFactor msg))
    (cl:cons ':xWam (xWam msg))
))
;//! \htmlinclude set_controller_options-response.msg.html

(cl:defclass <set_controller_options-response> (roslisp-msg-protocol:ros-message)
  ((ret
    :reader ret
    :initarg :ret
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass set_controller_options-response (<set_controller_options-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <set_controller_options-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'set_controller_options-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name summit_xl_web-srv:<set_controller_options-response> is deprecated: use summit_xl_web-srv:set_controller_options-response instead.")))

(cl:ensure-generic-function 'ret-val :lambda-list '(m))
(cl:defmethod ret-val ((m <set_controller_options-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:ret-val is deprecated.  Use summit_xl_web-srv:ret instead.")
  (ret m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <set_controller_options-response>) ostream)
  "Serializes a message object of type '<set_controller_options-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'ret) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <set_controller_options-response>) istream)
  "Deserializes a message object of type '<set_controller_options-response>"
    (cl:setf (cl:slot-value msg 'ret) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<set_controller_options-response>)))
  "Returns string type for a service object of type '<set_controller_options-response>"
  "summit_xl_web/set_controller_optionsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_controller_options-response)))
  "Returns string type for a service object of type 'set_controller_options-response"
  "summit_xl_web/set_controller_optionsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<set_controller_options-response>)))
  "Returns md5sum for a message object of type '<set_controller_options-response>"
  "a51599e3b48803a1fc4a68757b75ae38")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'set_controller_options-response)))
  "Returns md5sum for a message object of type 'set_controller_options-response"
  "a51599e3b48803a1fc4a68757b75ae38")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<set_controller_options-response>)))
  "Returns full string definition for message of type '<set_controller_options-response>"
  (cl:format cl:nil "bool ret~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'set_controller_options-response)))
  "Returns full string definition for message of type 'set_controller_options-response"
  (cl:format cl:nil "bool ret~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <set_controller_options-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <set_controller_options-response>))
  "Converts a ROS message object to a list"
  (cl:list 'set_controller_options-response
    (cl:cons ':ret (ret msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'set_controller_options)))
  'set_controller_options-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'set_controller_options)))
  'set_controller_options-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_controller_options)))
  "Returns string type for a service object of type '<set_controller_options>"
  "summit_xl_web/set_controller_options")
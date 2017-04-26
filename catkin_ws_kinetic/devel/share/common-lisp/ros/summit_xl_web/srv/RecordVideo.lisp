; Auto-generated. Do not edit!


(cl:in-package summit_xl_web-srv)


;//! \htmlinclude RecordVideo-request.msg.html

(cl:defclass <RecordVideo-request> (roslisp-msg-protocol:ros-message)
  ((startRecording
    :reader startRecording
    :initarg :startRecording
    :type cl:fixnum
    :initform 0))
)

(cl:defclass RecordVideo-request (<RecordVideo-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RecordVideo-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RecordVideo-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name summit_xl_web-srv:<RecordVideo-request> is deprecated: use summit_xl_web-srv:RecordVideo-request instead.")))

(cl:ensure-generic-function 'startRecording-val :lambda-list '(m))
(cl:defmethod startRecording-val ((m <RecordVideo-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:startRecording-val is deprecated.  Use summit_xl_web-srv:startRecording instead.")
  (startRecording m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RecordVideo-request>) ostream)
  "Serializes a message object of type '<RecordVideo-request>"
  (cl:let* ((signed (cl:slot-value msg 'startRecording)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RecordVideo-request>) istream)
  "Deserializes a message object of type '<RecordVideo-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'startRecording) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RecordVideo-request>)))
  "Returns string type for a service object of type '<RecordVideo-request>"
  "summit_xl_web/RecordVideoRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RecordVideo-request)))
  "Returns string type for a service object of type 'RecordVideo-request"
  "summit_xl_web/RecordVideoRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RecordVideo-request>)))
  "Returns md5sum for a message object of type '<RecordVideo-request>"
  "44be2ad84d20bbc65e2c7c40d2653ffb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RecordVideo-request)))
  "Returns md5sum for a message object of type 'RecordVideo-request"
  "44be2ad84d20bbc65e2c7c40d2653ffb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RecordVideo-request>)))
  "Returns full string definition for message of type '<RecordVideo-request>"
  (cl:format cl:nil "int16 startRecording~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RecordVideo-request)))
  "Returns full string definition for message of type 'RecordVideo-request"
  (cl:format cl:nil "int16 startRecording~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RecordVideo-request>))
  (cl:+ 0
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RecordVideo-request>))
  "Converts a ROS message object to a list"
  (cl:list 'RecordVideo-request
    (cl:cons ':startRecording (startRecording msg))
))
;//! \htmlinclude RecordVideo-response.msg.html

(cl:defclass <RecordVideo-response> (roslisp-msg-protocol:ros-message)
  ((filename
    :reader filename
    :initarg :filename
    :type cl:string
    :initform ""))
)

(cl:defclass RecordVideo-response (<RecordVideo-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RecordVideo-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RecordVideo-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name summit_xl_web-srv:<RecordVideo-response> is deprecated: use summit_xl_web-srv:RecordVideo-response instead.")))

(cl:ensure-generic-function 'filename-val :lambda-list '(m))
(cl:defmethod filename-val ((m <RecordVideo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_xl_web-srv:filename-val is deprecated.  Use summit_xl_web-srv:filename instead.")
  (filename m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RecordVideo-response>) ostream)
  "Serializes a message object of type '<RecordVideo-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'filename))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'filename))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RecordVideo-response>) istream)
  "Deserializes a message object of type '<RecordVideo-response>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'filename) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'filename) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RecordVideo-response>)))
  "Returns string type for a service object of type '<RecordVideo-response>"
  "summit_xl_web/RecordVideoResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RecordVideo-response)))
  "Returns string type for a service object of type 'RecordVideo-response"
  "summit_xl_web/RecordVideoResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RecordVideo-response>)))
  "Returns md5sum for a message object of type '<RecordVideo-response>"
  "44be2ad84d20bbc65e2c7c40d2653ffb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RecordVideo-response)))
  "Returns md5sum for a message object of type 'RecordVideo-response"
  "44be2ad84d20bbc65e2c7c40d2653ffb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RecordVideo-response>)))
  "Returns full string definition for message of type '<RecordVideo-response>"
  (cl:format cl:nil "string filename~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RecordVideo-response)))
  "Returns full string definition for message of type 'RecordVideo-response"
  (cl:format cl:nil "string filename~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RecordVideo-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'filename))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RecordVideo-response>))
  "Converts a ROS message object to a list"
  (cl:list 'RecordVideo-response
    (cl:cons ':filename (filename msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'RecordVideo)))
  'RecordVideo-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'RecordVideo)))
  'RecordVideo-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RecordVideo)))
  "Returns string type for a service object of type '<RecordVideo>"
  "summit_xl_web/RecordVideo")
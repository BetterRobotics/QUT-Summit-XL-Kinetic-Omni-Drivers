; Auto-generated. Do not edit!


(cl:in-package summit_cpu-msg)


;//! \htmlinclude Coords.msg.html

(cl:defclass <Coords> (roslisp-msg-protocol:ros-message)
  ((personpresent
    :reader personpresent
    :initarg :personpresent
    :type cl:boolean
    :initform cl:nil)
   (x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (z
    :reader z
    :initarg :z
    :type cl:float
    :initform 0.0))
)

(cl:defclass Coords (<Coords>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Coords>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Coords)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name summit_cpu-msg:<Coords> is deprecated: use summit_cpu-msg:Coords instead.")))

(cl:ensure-generic-function 'personpresent-val :lambda-list '(m))
(cl:defmethod personpresent-val ((m <Coords>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:personpresent-val is deprecated.  Use summit_cpu-msg:personpresent instead.")
  (personpresent m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <Coords>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:x-val is deprecated.  Use summit_cpu-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <Coords>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:y-val is deprecated.  Use summit_cpu-msg:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <Coords>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader summit_cpu-msg:z-val is deprecated.  Use summit_cpu-msg:z instead.")
  (z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Coords>) ostream)
  "Serializes a message object of type '<Coords>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'personpresent) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Coords>) istream)
  "Deserializes a message object of type '<Coords>"
    (cl:setf (cl:slot-value msg 'personpresent) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Coords>)))
  "Returns string type for a message object of type '<Coords>"
  "summit_cpu/Coords")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Coords)))
  "Returns string type for a message object of type 'Coords"
  "summit_cpu/Coords")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Coords>)))
  "Returns md5sum for a message object of type '<Coords>"
  "ea3ef746517c119e7907675c643db99a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Coords)))
  "Returns md5sum for a message object of type 'Coords"
  "ea3ef746517c119e7907675c643db99a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Coords>)))
  "Returns full string definition for message of type '<Coords>"
  (cl:format cl:nil "bool personpresent~%float32 x~%float32 y~%float32 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Coords)))
  "Returns full string definition for message of type 'Coords"
  (cl:format cl:nil "bool personpresent~%float32 x~%float32 y~%float32 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Coords>))
  (cl:+ 0
     1
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Coords>))
  "Converts a ROS message object to a list"
  (cl:list 'Coords
    (cl:cons ':personpresent (personpresent msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
))

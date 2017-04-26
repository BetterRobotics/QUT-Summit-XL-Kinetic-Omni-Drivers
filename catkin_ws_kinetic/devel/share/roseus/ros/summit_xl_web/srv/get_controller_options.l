;; Auto-generated. Do not edit!


(when (boundp 'summit_xl_web::get_controller_options)
  (if (not (find-package "SUMMIT_XL_WEB"))
    (make-package "SUMMIT_XL_WEB"))
  (shadow 'get_controller_options (find-package "SUMMIT_XL_WEB")))
(unless (find-package "SUMMIT_XL_WEB::GET_CONTROLLER_OPTIONS")
  (make-package "SUMMIT_XL_WEB::GET_CONTROLLER_OPTIONS"))
(unless (find-package "SUMMIT_XL_WEB::GET_CONTROLLER_OPTIONSREQUEST")
  (make-package "SUMMIT_XL_WEB::GET_CONTROLLER_OPTIONSREQUEST"))
(unless (find-package "SUMMIT_XL_WEB::GET_CONTROLLER_OPTIONSRESPONSE")
  (make-package "SUMMIT_XL_WEB::GET_CONTROLLER_OPTIONSRESPONSE"))

(in-package "ROS")





(defclass summit_xl_web::get_controller_optionsRequest
  :super ros::object
  :slots ())

(defmethod summit_xl_web::get_controller_optionsRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass summit_xl_web::get_controller_optionsResponse
  :super ros::object
  :slots (_takeOver _kinematicMode _gearboxReduction _diameterWheel _motionOdometry _motorsEncoder _motorsEncoderFactor _xWam ))

(defmethod summit_xl_web::get_controller_optionsResponse
  (:init
   (&key
    ((:takeOver __takeOver) nil)
    ((:kinematicMode __kinematicMode) "")
    ((:gearboxReduction __gearboxReduction) 0.0)
    ((:diameterWheel __diameterWheel) 0.0)
    ((:motionOdometry __motionOdometry) "")
    ((:motorsEncoder __motorsEncoder) "")
    ((:motorsEncoderFactor __motorsEncoderFactor) 0)
    ((:xWam __xWam) "")
    )
   (send-super :init)
   (setq _takeOver __takeOver)
   (setq _kinematicMode (string __kinematicMode))
   (setq _gearboxReduction (float __gearboxReduction))
   (setq _diameterWheel (float __diameterWheel))
   (setq _motionOdometry (string __motionOdometry))
   (setq _motorsEncoder (string __motorsEncoder))
   (setq _motorsEncoderFactor (round __motorsEncoderFactor))
   (setq _xWam (string __xWam))
   self)
  (:takeOver
   (&optional __takeOver)
   (if __takeOver (setq _takeOver __takeOver)) _takeOver)
  (:kinematicMode
   (&optional __kinematicMode)
   (if __kinematicMode (setq _kinematicMode __kinematicMode)) _kinematicMode)
  (:gearboxReduction
   (&optional __gearboxReduction)
   (if __gearboxReduction (setq _gearboxReduction __gearboxReduction)) _gearboxReduction)
  (:diameterWheel
   (&optional __diameterWheel)
   (if __diameterWheel (setq _diameterWheel __diameterWheel)) _diameterWheel)
  (:motionOdometry
   (&optional __motionOdometry)
   (if __motionOdometry (setq _motionOdometry __motionOdometry)) _motionOdometry)
  (:motorsEncoder
   (&optional __motorsEncoder)
   (if __motorsEncoder (setq _motorsEncoder __motorsEncoder)) _motorsEncoder)
  (:motorsEncoderFactor
   (&optional __motorsEncoderFactor)
   (if __motorsEncoderFactor (setq _motorsEncoderFactor __motorsEncoderFactor)) _motorsEncoderFactor)
  (:xWam
   (&optional __xWam)
   (if __xWam (setq _xWam __xWam)) _xWam)
  (:serialization-length
   ()
   (+
    ;; bool _takeOver
    1
    ;; string _kinematicMode
    4 (length _kinematicMode)
    ;; float32 _gearboxReduction
    4
    ;; float32 _diameterWheel
    4
    ;; string _motionOdometry
    4 (length _motionOdometry)
    ;; string _motorsEncoder
    4 (length _motorsEncoder)
    ;; int32 _motorsEncoderFactor
    4
    ;; string _xWam
    4 (length _xWam)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _takeOver
       (if _takeOver (write-byte -1 s) (write-byte 0 s))
     ;; string _kinematicMode
       (write-long (length _kinematicMode) s) (princ _kinematicMode s)
     ;; float32 _gearboxReduction
       (sys::poke _gearboxReduction (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _diameterWheel
       (sys::poke _diameterWheel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; string _motionOdometry
       (write-long (length _motionOdometry) s) (princ _motionOdometry s)
     ;; string _motorsEncoder
       (write-long (length _motorsEncoder) s) (princ _motorsEncoder s)
     ;; int32 _motorsEncoderFactor
       (write-long _motorsEncoderFactor s)
     ;; string _xWam
       (write-long (length _xWam) s) (princ _xWam s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _takeOver
     (setq _takeOver (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _kinematicMode
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _kinematicMode (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32 _gearboxReduction
     (setq _gearboxReduction (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _diameterWheel
     (setq _diameterWheel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; string _motionOdometry
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _motionOdometry (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _motorsEncoder
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _motorsEncoder (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _motorsEncoderFactor
     (setq _motorsEncoderFactor (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _xWam
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _xWam (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass summit_xl_web::get_controller_options
  :super ros::object
  :slots ())

(setf (get summit_xl_web::get_controller_options :md5sum-) "c803d4442092d317a92118964b891b96")
(setf (get summit_xl_web::get_controller_options :datatype-) "summit_xl_web/get_controller_options")
(setf (get summit_xl_web::get_controller_options :request) summit_xl_web::get_controller_optionsRequest)
(setf (get summit_xl_web::get_controller_options :response) summit_xl_web::get_controller_optionsResponse)

(defmethod summit_xl_web::get_controller_optionsRequest
  (:response () (instance summit_xl_web::get_controller_optionsResponse :init)))

(setf (get summit_xl_web::get_controller_optionsRequest :md5sum-) "c803d4442092d317a92118964b891b96")
(setf (get summit_xl_web::get_controller_optionsRequest :datatype-) "summit_xl_web/get_controller_optionsRequest")
(setf (get summit_xl_web::get_controller_optionsRequest :definition-)
      "---
bool takeOver
string kinematicMode
float32 gearboxReduction
float32 diameterWheel
string motionOdometry
string motorsEncoder
int32  motorsEncoderFactor
string xWam

")

(setf (get summit_xl_web::get_controller_optionsResponse :md5sum-) "c803d4442092d317a92118964b891b96")
(setf (get summit_xl_web::get_controller_optionsResponse :datatype-) "summit_xl_web/get_controller_optionsResponse")
(setf (get summit_xl_web::get_controller_optionsResponse :definition-)
      "---
bool takeOver
string kinematicMode
float32 gearboxReduction
float32 diameterWheel
string motionOdometry
string motorsEncoder
int32  motorsEncoderFactor
string xWam

")



(provide :summit_xl_web/get_controller_options "c803d4442092d317a92118964b891b96")



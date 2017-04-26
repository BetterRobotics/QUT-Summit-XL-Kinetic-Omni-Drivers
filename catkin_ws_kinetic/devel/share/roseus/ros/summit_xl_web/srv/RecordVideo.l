;; Auto-generated. Do not edit!


(when (boundp 'summit_xl_web::RecordVideo)
  (if (not (find-package "SUMMIT_XL_WEB"))
    (make-package "SUMMIT_XL_WEB"))
  (shadow 'RecordVideo (find-package "SUMMIT_XL_WEB")))
(unless (find-package "SUMMIT_XL_WEB::RECORDVIDEO")
  (make-package "SUMMIT_XL_WEB::RECORDVIDEO"))
(unless (find-package "SUMMIT_XL_WEB::RECORDVIDEOREQUEST")
  (make-package "SUMMIT_XL_WEB::RECORDVIDEOREQUEST"))
(unless (find-package "SUMMIT_XL_WEB::RECORDVIDEORESPONSE")
  (make-package "SUMMIT_XL_WEB::RECORDVIDEORESPONSE"))

(in-package "ROS")





(defclass summit_xl_web::RecordVideoRequest
  :super ros::object
  :slots (_startRecording ))

(defmethod summit_xl_web::RecordVideoRequest
  (:init
   (&key
    ((:startRecording __startRecording) 0)
    )
   (send-super :init)
   (setq _startRecording (round __startRecording))
   self)
  (:startRecording
   (&optional __startRecording)
   (if __startRecording (setq _startRecording __startRecording)) _startRecording)
  (:serialization-length
   ()
   (+
    ;; int16 _startRecording
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _startRecording
       (write-word _startRecording s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _startRecording
     (setq _startRecording (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(defclass summit_xl_web::RecordVideoResponse
  :super ros::object
  :slots (_filename ))

(defmethod summit_xl_web::RecordVideoResponse
  (:init
   (&key
    ((:filename __filename) "")
    )
   (send-super :init)
   (setq _filename (string __filename))
   self)
  (:filename
   (&optional __filename)
   (if __filename (setq _filename __filename)) _filename)
  (:serialization-length
   ()
   (+
    ;; string _filename
    4 (length _filename)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _filename
       (write-long (length _filename) s) (princ _filename s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _filename
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _filename (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass summit_xl_web::RecordVideo
  :super ros::object
  :slots ())

(setf (get summit_xl_web::RecordVideo :md5sum-) "44be2ad84d20bbc65e2c7c40d2653ffb")
(setf (get summit_xl_web::RecordVideo :datatype-) "summit_xl_web/RecordVideo")
(setf (get summit_xl_web::RecordVideo :request) summit_xl_web::RecordVideoRequest)
(setf (get summit_xl_web::RecordVideo :response) summit_xl_web::RecordVideoResponse)

(defmethod summit_xl_web::RecordVideoRequest
  (:response () (instance summit_xl_web::RecordVideoResponse :init)))

(setf (get summit_xl_web::RecordVideoRequest :md5sum-) "44be2ad84d20bbc65e2c7c40d2653ffb")
(setf (get summit_xl_web::RecordVideoRequest :datatype-) "summit_xl_web/RecordVideoRequest")
(setf (get summit_xl_web::RecordVideoRequest :definition-)
      "int16 startRecording
---
string filename

")

(setf (get summit_xl_web::RecordVideoResponse :md5sum-) "44be2ad84d20bbc65e2c7c40d2653ffb")
(setf (get summit_xl_web::RecordVideoResponse :datatype-) "summit_xl_web/RecordVideoResponse")
(setf (get summit_xl_web::RecordVideoResponse :definition-)
      "int16 startRecording
---
string filename

")



(provide :summit_xl_web/RecordVideo "44be2ad84d20bbc65e2c7c40d2653ffb")



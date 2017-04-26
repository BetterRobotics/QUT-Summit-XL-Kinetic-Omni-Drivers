;; Auto-generated. Do not edit!


(when (boundp 'robotnik_msgs::MotorStatus)
  (if (not (find-package "ROBOTNIK_MSGS"))
    (make-package "ROBOTNIK_MSGS"))
  (shadow 'MotorStatus (find-package "ROBOTNIK_MSGS")))
(unless (find-package "ROBOTNIK_MSGS::MOTORSTATUS")
  (make-package "ROBOTNIK_MSGS::MOTORSTATUS"))

(in-package "ROS")
;;//! \htmlinclude MotorStatus.msg.html


(defclass robotnik_msgs::MotorStatus
  :super ros::object
  :slots (_state _status _statusword _driveflags ))

(defmethod robotnik_msgs::MotorStatus
  (:init
   (&key
    ((:state __state) "")
    ((:status __status) "")
    ((:statusword __statusword) "")
    ((:driveflags __driveflags) "")
    )
   (send-super :init)
   (setq _state (string __state))
   (setq _status (string __status))
   (setq _statusword (string __statusword))
   (setq _driveflags (string __driveflags))
   self)
  (:state
   (&optional __state)
   (if __state (setq _state __state)) _state)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:statusword
   (&optional __statusword)
   (if __statusword (setq _statusword __statusword)) _statusword)
  (:driveflags
   (&optional __driveflags)
   (if __driveflags (setq _driveflags __driveflags)) _driveflags)
  (:serialization-length
   ()
   (+
    ;; string _state
    4 (length _state)
    ;; string _status
    4 (length _status)
    ;; string _statusword
    4 (length _statusword)
    ;; string _driveflags
    4 (length _driveflags)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _state
       (write-long (length _state) s) (princ _state s)
     ;; string _status
       (write-long (length _status) s) (princ _status s)
     ;; string _statusword
       (write-long (length _statusword) s) (princ _statusword s)
     ;; string _driveflags
       (write-long (length _driveflags) s) (princ _driveflags s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _state
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _state (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _status
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _status (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _statusword
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _statusword (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _driveflags
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _driveflags (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get robotnik_msgs::MotorStatus :md5sum-) "bf902392cd07d79e1d1294bfae19e58e")
(setf (get robotnik_msgs::MotorStatus :datatype-) "robotnik_msgs/MotorStatus")
(setf (get robotnik_msgs::MotorStatus :definition-)
      "string state
string status
string statusword
string driveflags

")



(provide :robotnik_msgs/MotorStatus "bf902392cd07d79e1d1294bfae19e58e")



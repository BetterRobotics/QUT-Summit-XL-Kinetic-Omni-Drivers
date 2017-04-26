;; Auto-generated. Do not edit!


(when (boundp 'robotnik_msgs::BatteryStatus)
  (if (not (find-package "ROBOTNIK_MSGS"))
    (make-package "ROBOTNIK_MSGS"))
  (shadow 'BatteryStatus (find-package "ROBOTNIK_MSGS")))
(unless (find-package "ROBOTNIK_MSGS::BATTERYSTATUS")
  (make-package "ROBOTNIK_MSGS::BATTERYSTATUS"))

(in-package "ROS")
;;//! \htmlinclude BatteryStatus.msg.html


(defclass robotnik_msgs::BatteryStatus
  :super ros::object
  :slots (_level _time_remaining ))

(defmethod robotnik_msgs::BatteryStatus
  (:init
   (&key
    ((:level __level) 0.0)
    ((:time_remaining __time_remaining) 0)
    )
   (send-super :init)
   (setq _level (float __level))
   (setq _time_remaining (round __time_remaining))
   self)
  (:level
   (&optional __level)
   (if __level (setq _level __level)) _level)
  (:time_remaining
   (&optional __time_remaining)
   (if __time_remaining (setq _time_remaining __time_remaining)) _time_remaining)
  (:serialization-length
   ()
   (+
    ;; float32 _level
    4
    ;; uint32 _time_remaining
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _level
       (sys::poke _level (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; uint32 _time_remaining
       (write-long _time_remaining s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _level
     (setq _level (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; uint32 _time_remaining
     (setq _time_remaining (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get robotnik_msgs::BatteryStatus :md5sum-) "97f2ff224c7220de9e3b44df5993c0f6")
(setf (get robotnik_msgs::BatteryStatus :datatype-) "robotnik_msgs/BatteryStatus")
(setf (get robotnik_msgs::BatteryStatus :definition-)
      "float32 level			# in %
uint32 time_remaining		# in minutes

")



(provide :robotnik_msgs/BatteryStatus "97f2ff224c7220de9e3b44df5993c0f6")



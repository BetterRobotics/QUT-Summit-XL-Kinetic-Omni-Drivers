;; Auto-generated. Do not edit!


(when (boundp 'summit_xl_controller::LimitSwitches)
  (if (not (find-package "SUMMIT_XL_CONTROLLER"))
    (make-package "SUMMIT_XL_CONTROLLER"))
  (shadow 'LimitSwitches (find-package "SUMMIT_XL_CONTROLLER")))
(unless (find-package "SUMMIT_XL_CONTROLLER::LIMITSWITCHES")
  (make-package "SUMMIT_XL_CONTROLLER::LIMITSWITCHES"))

(in-package "ROS")
;;//! \htmlinclude LimitSwitches.msg.html


(defclass summit_xl_controller::LimitSwitches
  :super ros::object
  :slots (_up _down ))

(defmethod summit_xl_controller::LimitSwitches
  (:init
   (&key
    ((:up __up) nil)
    ((:down __down) nil)
    )
   (send-super :init)
   (setq _up __up)
   (setq _down __down)
   self)
  (:up
   (&optional __up)
   (if __up (setq _up __up)) _up)
  (:down
   (&optional __down)
   (if __down (setq _down __down)) _down)
  (:serialization-length
   ()
   (+
    ;; bool _up
    1
    ;; bool _down
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _up
       (if _up (write-byte -1 s) (write-byte 0 s))
     ;; bool _down
       (if _down (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _up
     (setq _up (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _down
     (setq _down (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get summit_xl_controller::LimitSwitches :md5sum-) "3d014920df9acd91aa1e77d852f832f5")
(setf (get summit_xl_controller::LimitSwitches :datatype-) "summit_xl_controller/LimitSwitches")
(setf (get summit_xl_controller::LimitSwitches :definition-)
      "bool up
bool down

")



(provide :summit_xl_controller/LimitSwitches "3d014920df9acd91aa1e77d852f832f5")



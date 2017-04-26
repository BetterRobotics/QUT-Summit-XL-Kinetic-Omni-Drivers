;; Auto-generated. Do not edit!


(when (boundp 'summit_cpu::Coords)
  (if (not (find-package "SUMMIT_CPU"))
    (make-package "SUMMIT_CPU"))
  (shadow 'Coords (find-package "SUMMIT_CPU")))
(unless (find-package "SUMMIT_CPU::COORDS")
  (make-package "SUMMIT_CPU::COORDS"))

(in-package "ROS")
;;//! \htmlinclude Coords.msg.html


(defclass summit_cpu::Coords
  :super ros::object
  :slots (_personpresent _x _y _z ))

(defmethod summit_cpu::Coords
  (:init
   (&key
    ((:personpresent __personpresent) nil)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:z __z) 0.0)
    )
   (send-super :init)
   (setq _personpresent __personpresent)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _z (float __z))
   self)
  (:personpresent
   (&optional __personpresent)
   (if __personpresent (setq _personpresent __personpresent)) _personpresent)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:serialization-length
   ()
   (+
    ;; bool _personpresent
    1
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; float32 _z
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _personpresent
       (if _personpresent (write-byte -1 s) (write-byte 0 s))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _z
       (sys::poke _z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _personpresent
     (setq _personpresent (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _z
     (setq _z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get summit_cpu::Coords :md5sum-) "ea3ef746517c119e7907675c643db99a")
(setf (get summit_cpu::Coords :datatype-) "summit_cpu/Coords")
(setf (get summit_cpu::Coords :definition-)
      "bool personpresent
float32 x
float32 y
float32 z

")



(provide :summit_cpu/Coords "ea3ef746517c119e7907675c643db99a")



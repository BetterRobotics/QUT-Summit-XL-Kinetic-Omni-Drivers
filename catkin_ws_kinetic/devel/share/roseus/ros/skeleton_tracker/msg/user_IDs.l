;; Auto-generated. Do not edit!


(when (boundp 'skeleton_tracker::user_IDs)
  (if (not (find-package "SKELETON_TRACKER"))
    (make-package "SKELETON_TRACKER"))
  (shadow 'user_IDs (find-package "SKELETON_TRACKER")))
(unless (find-package "SKELETON_TRACKER::USER_IDS")
  (make-package "SKELETON_TRACKER::USER_IDS"))

(in-package "ROS")
;;//! \htmlinclude user_IDs.msg.html


(defclass skeleton_tracker::user_IDs
  :super ros::object
  :slots (_users ))

(defmethod skeleton_tracker::user_IDs
  (:init
   (&key
    ((:users __users) (make-array 0 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _users __users)
   self)
  (:users
   (&optional __users)
   (if __users (setq _users __users)) _users)
  (:serialization-length
   ()
   (+
    ;; uint8[] _users
    (* 1    (length _users)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8[] _users
     (write-long (length _users) s)
     (princ _users s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8[] _users
   (let ((n (sys::peek buf ptr- :integer))) (incf ptr- 4)
     (setq _users (make-array n :element-type :char))
     (replace _users buf :start2 ptr-) (incf ptr- n))
   ;;
   self)
  )

(setf (get skeleton_tracker::user_IDs :md5sum-) "0370fea64fb82134b7a78a66cb25797c")
(setf (get skeleton_tracker::user_IDs :datatype-) "skeleton_tracker/user_IDs")
(setf (get skeleton_tracker::user_IDs :definition-)
      "uint8[] users
")



(provide :skeleton_tracker/user_IDs "0370fea64fb82134b7a78a66cb25797c")



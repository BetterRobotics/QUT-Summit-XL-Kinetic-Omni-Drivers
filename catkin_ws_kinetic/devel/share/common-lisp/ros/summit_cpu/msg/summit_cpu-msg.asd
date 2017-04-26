
(cl:in-package :asdf)

(defsystem "summit_cpu-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :sensor_msgs-msg
)
  :components ((:file "_package")
    (:file "BBox" :depends-on ("_package_BBox"))
    (:file "_package_BBox" :depends-on ("_package"))
    (:file "Coords" :depends-on ("_package_Coords"))
    (:file "_package_Coords" :depends-on ("_package"))
    (:file "Images" :depends-on ("_package_Images"))
    (:file "_package_Images" :depends-on ("_package"))
    (:file "custom_array" :depends-on ("_package_custom_array"))
    (:file "_package_custom_array" :depends-on ("_package"))
  ))
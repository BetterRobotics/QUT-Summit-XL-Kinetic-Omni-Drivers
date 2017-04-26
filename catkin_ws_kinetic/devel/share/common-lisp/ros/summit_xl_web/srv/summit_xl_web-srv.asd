
(cl:in-package :asdf)

(defsystem "summit_xl_web-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "RecordVideo" :depends-on ("_package_RecordVideo"))
    (:file "_package_RecordVideo" :depends-on ("_package"))
    (:file "get_controller_options" :depends-on ("_package_get_controller_options"))
    (:file "_package_get_controller_options" :depends-on ("_package"))
    (:file "set_controller_options" :depends-on ("_package_set_controller_options"))
    (:file "_package_set_controller_options" :depends-on ("_package"))
  ))
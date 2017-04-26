
(cl:in-package :asdf)

(defsystem "summit_xl_controller-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Battery" :depends-on ("_package_Battery"))
    (:file "_package_Battery" :depends-on ("_package"))
    (:file "Battery" :depends-on ("_package_Battery"))
    (:file "_package_Battery" :depends-on ("_package"))
    (:file "LimitSwitches" :depends-on ("_package_LimitSwitches"))
    (:file "_package_LimitSwitches" :depends-on ("_package"))
    (:file "LimitSwitches" :depends-on ("_package_LimitSwitches"))
    (:file "_package_LimitSwitches" :depends-on ("_package"))
  ))
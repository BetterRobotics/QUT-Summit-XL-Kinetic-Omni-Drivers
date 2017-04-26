# summit_xl_robot
ROS package of the Summit XL, XL-HL mobile robot platforms

![Image of Summit XL](http://www.robotnik.es/web/wp-content/uploads/2014/03/summit-xl-robots-moviles-robotnik_s01.jpg)

<h2>gps_map_tf</h2>

This package is intended to publish the transform from map->odom in order to use gps coordinates to localize the robot and in order to use the move_base stack in Cartesian coordinates (it does the equivalent tf publication done in amcl). This package is intended only for testing purposes, a better configuration for the GPS is provided in the summit_xl_localization package of the summit_xl_common metapackage.

It allows to set the coordinates origin and to align the robot heading with the gps coordinate system heading. 

<h2>summit_xl_bringup</h2>

This package contains launch files to start the robot. The most relevant file is launch/summit_xl_complete.launch, that is called from the .bashrc at system startup. The file can be configured to start the available devices, usually: lasers, cameras, rgbd devices, imus, gps, etc. Integrates several test launch files to test the components individually. 

<h2>summit_xl_controller</h2>

Low level robot control of the 4 servos. This package contains the robot control functions to operate the skid-steering / omni-steering structure (velocity control of the axes and position control of the robot) and to get accurate odometry estimations from the robot sensors. This node subscribes to cmd_vel messages.

<h2>summit_xl_web</h2>

rosbridge server based package to access the robot via web browser. It allows to access the status of the robot, the diagnostics of the servos, the camera, battery level, errors, etc. It allows to control the platform motion, but also the PTZ. The package is intended as a template to be further expanded by the user.






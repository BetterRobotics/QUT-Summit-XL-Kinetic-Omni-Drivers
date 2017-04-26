#!/usr/bin/env python  
import roslib
roslib.load_manifest('learning_tf')

import rospy
import tf
import math

if __name__ == '__main__':
    rospy.init_node('my_tf_broadcaster')
    br = tf.TransformBroadcaster()
    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        t = rospy.Time.now().to_sec() * math.pi
        br.sendTransform((-0.4, 0.0, 0.9),
                         (0.0, 0.35, 0.0, 1.0),
                         rospy.Time.now(),
                         "camera1_link",
                         "baseview")
        rate.sleep()

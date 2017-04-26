execute_process(COMMAND "/home/summit/catkin_ws_kinetic/build/summit_xl_robot/summit_xl_web/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/summit/catkin_ws_kinetic/build/summit_xl_robot/summit_xl_web/catkin_generated/python_distutils_install.sh) returned error code ")
endif()

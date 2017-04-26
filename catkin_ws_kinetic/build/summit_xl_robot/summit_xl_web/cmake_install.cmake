# Install script for directory: /home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_web

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/summit/catkin_ws_kinetic/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  include("/home/summit/catkin_ws_kinetic/build/summit_xl_robot/summit_xl_web/catkin_generated/safe_execute_install.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/summit_xl_web/srv" TYPE FILE FILES
    "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_web/srv/RecordVideo.srv"
    "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_web/srv/set_controller_options.srv"
    "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_web/srv/get_controller_options.srv"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/summit_xl_web/cmake" TYPE FILE FILES "/home/summit/catkin_ws_kinetic/build/summit_xl_robot/summit_xl_web/catkin_generated/installspace/summit_xl_web-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/summit/catkin_ws_kinetic/devel/include/summit_xl_web")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/summit/catkin_ws_kinetic/devel/share/roseus/ros/summit_xl_web")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/summit/catkin_ws_kinetic/devel/share/common-lisp/ros/summit_xl_web")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/summit/catkin_ws_kinetic/devel/share/gennodejs/ros/summit_xl_web")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/summit/catkin_ws_kinetic/devel/lib/python2.7/dist-packages/summit_xl_web")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/summit/catkin_ws_kinetic/devel/lib/python2.7/dist-packages/summit_xl_web" REGEX "/\\_\\_init\\_\\_\\.py$" EXCLUDE REGEX "/\\_\\_init\\_\\_\\.pyc$" EXCLUDE)
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/summit/catkin_ws_kinetic/devel/lib/python2.7/dist-packages/summit_xl_web" FILES_MATCHING REGEX "/home/summit/catkin_ws_kinetic/devel/lib/python2.7/dist-packages/summit_xl_web/.+/__init__.pyc?$")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/summit/catkin_ws_kinetic/build/summit_xl_robot/summit_xl_web/catkin_generated/installspace/summit_xl_web.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/summit_xl_web/cmake" TYPE FILE FILES "/home/summit/catkin_ws_kinetic/build/summit_xl_robot/summit_xl_web/catkin_generated/installspace/summit_xl_web-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/summit_xl_web/cmake" TYPE FILE FILES
    "/home/summit/catkin_ws_kinetic/build/summit_xl_robot/summit_xl_web/catkin_generated/installspace/summit_xl_webConfig.cmake"
    "/home/summit/catkin_ws_kinetic/build/summit_xl_robot/summit_xl_web/catkin_generated/installspace/summit_xl_webConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/summit_xl_web" TYPE FILE FILES "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_web/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/summit_xl_web" TYPE PROGRAM FILES "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_web/scripts/summit_xl_web/start_recording_server.py")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/summit_xl_web" TYPE FILE FILES "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_web/launch/summit_xl_web.launch")
endif()


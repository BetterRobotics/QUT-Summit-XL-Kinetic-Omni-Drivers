# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "summit_xl_controller: 2 messages, 0 services")

set(MSG_I_FLAGS "-Isummit_xl_controller:/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg;-Inav_msgs:/opt/ros/kinetic/share/nav_msgs/cmake/../msg;-Irobotnik_msgs:/home/summit/catkin_ws_kinetic/src/dependencies/robotnik_msgs/msg;-Isensor_msgs:/opt/ros/kinetic/share/sensor_msgs/cmake/../msg;-Isummit_xl_controller:/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(summit_xl_controller_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg" NAME_WE)
add_custom_target(_summit_xl_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "summit_xl_controller" "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg" ""
)

get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg" NAME_WE)
add_custom_target(_summit_xl_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "summit_xl_controller" "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_controller
)
_generate_msg_cpp(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_controller
)

### Generating Services

### Generating Module File
_generate_module_cpp(summit_xl_controller
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_controller
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(summit_xl_controller_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(summit_xl_controller_generate_messages summit_xl_controller_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_cpp _summit_xl_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_cpp _summit_xl_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_controller_gencpp)
add_dependencies(summit_xl_controller_gencpp summit_xl_controller_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_controller_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_controller
)
_generate_msg_eus(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_controller
)

### Generating Services

### Generating Module File
_generate_module_eus(summit_xl_controller
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_controller
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(summit_xl_controller_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(summit_xl_controller_generate_messages summit_xl_controller_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_eus _summit_xl_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_eus _summit_xl_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_controller_geneus)
add_dependencies(summit_xl_controller_geneus summit_xl_controller_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_controller_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_controller
)
_generate_msg_lisp(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_controller
)

### Generating Services

### Generating Module File
_generate_module_lisp(summit_xl_controller
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_controller
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(summit_xl_controller_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(summit_xl_controller_generate_messages summit_xl_controller_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_lisp _summit_xl_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_lisp _summit_xl_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_controller_genlisp)
add_dependencies(summit_xl_controller_genlisp summit_xl_controller_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_controller_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_controller
)
_generate_msg_nodejs(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_controller
)

### Generating Services

### Generating Module File
_generate_module_nodejs(summit_xl_controller
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_controller
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(summit_xl_controller_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(summit_xl_controller_generate_messages summit_xl_controller_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_nodejs _summit_xl_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_nodejs _summit_xl_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_controller_gennodejs)
add_dependencies(summit_xl_controller_gennodejs summit_xl_controller_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_controller_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_controller
)
_generate_msg_py(summit_xl_controller
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_controller
)

### Generating Services

### Generating Module File
_generate_module_py(summit_xl_controller
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_controller
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(summit_xl_controller_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(summit_xl_controller_generate_messages summit_xl_controller_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/Battery.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_py _summit_xl_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_controller/msg/LimitSwitches.msg" NAME_WE)
add_dependencies(summit_xl_controller_generate_messages_py _summit_xl_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_controller_genpy)
add_dependencies(summit_xl_controller_genpy summit_xl_controller_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_controller_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_controller
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET nav_msgs_generate_messages_cpp)
  add_dependencies(summit_xl_controller_generate_messages_cpp nav_msgs_generate_messages_cpp)
endif()
if(TARGET robotnik_msgs_generate_messages_cpp)
  add_dependencies(summit_xl_controller_generate_messages_cpp robotnik_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(summit_xl_controller_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET summit_xl_controller_generate_messages_cpp)
  add_dependencies(summit_xl_controller_generate_messages_cpp summit_xl_controller_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_controller
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET nav_msgs_generate_messages_eus)
  add_dependencies(summit_xl_controller_generate_messages_eus nav_msgs_generate_messages_eus)
endif()
if(TARGET robotnik_msgs_generate_messages_eus)
  add_dependencies(summit_xl_controller_generate_messages_eus robotnik_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(summit_xl_controller_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET summit_xl_controller_generate_messages_eus)
  add_dependencies(summit_xl_controller_generate_messages_eus summit_xl_controller_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_controller
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET nav_msgs_generate_messages_lisp)
  add_dependencies(summit_xl_controller_generate_messages_lisp nav_msgs_generate_messages_lisp)
endif()
if(TARGET robotnik_msgs_generate_messages_lisp)
  add_dependencies(summit_xl_controller_generate_messages_lisp robotnik_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(summit_xl_controller_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET summit_xl_controller_generate_messages_lisp)
  add_dependencies(summit_xl_controller_generate_messages_lisp summit_xl_controller_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_controller
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET nav_msgs_generate_messages_nodejs)
  add_dependencies(summit_xl_controller_generate_messages_nodejs nav_msgs_generate_messages_nodejs)
endif()
if(TARGET robotnik_msgs_generate_messages_nodejs)
  add_dependencies(summit_xl_controller_generate_messages_nodejs robotnik_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(summit_xl_controller_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET summit_xl_controller_generate_messages_nodejs)
  add_dependencies(summit_xl_controller_generate_messages_nodejs summit_xl_controller_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_controller)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_controller\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_controller
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET nav_msgs_generate_messages_py)
  add_dependencies(summit_xl_controller_generate_messages_py nav_msgs_generate_messages_py)
endif()
if(TARGET robotnik_msgs_generate_messages_py)
  add_dependencies(summit_xl_controller_generate_messages_py robotnik_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(summit_xl_controller_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET summit_xl_controller_generate_messages_py)
  add_dependencies(summit_xl_controller_generate_messages_py summit_xl_controller_generate_messages_py)
endif()

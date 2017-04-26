# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "skeleton_tracker: 1 messages, 0 services")

set(MSG_I_FLAGS "-Iskeleton_tracker:/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(skeleton_tracker_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg" NAME_WE)
add_custom_target(_skeleton_tracker_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "skeleton_tracker" "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(skeleton_tracker
  "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/skeleton_tracker
)

### Generating Services

### Generating Module File
_generate_module_cpp(skeleton_tracker
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/skeleton_tracker
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(skeleton_tracker_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(skeleton_tracker_generate_messages skeleton_tracker_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg" NAME_WE)
add_dependencies(skeleton_tracker_generate_messages_cpp _skeleton_tracker_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(skeleton_tracker_gencpp)
add_dependencies(skeleton_tracker_gencpp skeleton_tracker_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS skeleton_tracker_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(skeleton_tracker
  "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/skeleton_tracker
)

### Generating Services

### Generating Module File
_generate_module_eus(skeleton_tracker
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/skeleton_tracker
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(skeleton_tracker_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(skeleton_tracker_generate_messages skeleton_tracker_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg" NAME_WE)
add_dependencies(skeleton_tracker_generate_messages_eus _skeleton_tracker_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(skeleton_tracker_geneus)
add_dependencies(skeleton_tracker_geneus skeleton_tracker_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS skeleton_tracker_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(skeleton_tracker
  "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/skeleton_tracker
)

### Generating Services

### Generating Module File
_generate_module_lisp(skeleton_tracker
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/skeleton_tracker
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(skeleton_tracker_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(skeleton_tracker_generate_messages skeleton_tracker_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg" NAME_WE)
add_dependencies(skeleton_tracker_generate_messages_lisp _skeleton_tracker_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(skeleton_tracker_genlisp)
add_dependencies(skeleton_tracker_genlisp skeleton_tracker_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS skeleton_tracker_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(skeleton_tracker
  "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/skeleton_tracker
)

### Generating Services

### Generating Module File
_generate_module_nodejs(skeleton_tracker
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/skeleton_tracker
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(skeleton_tracker_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(skeleton_tracker_generate_messages skeleton_tracker_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg" NAME_WE)
add_dependencies(skeleton_tracker_generate_messages_nodejs _skeleton_tracker_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(skeleton_tracker_gennodejs)
add_dependencies(skeleton_tracker_gennodejs skeleton_tracker_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS skeleton_tracker_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(skeleton_tracker
  "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/skeleton_tracker
)

### Generating Services

### Generating Module File
_generate_module_py(skeleton_tracker
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/skeleton_tracker
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(skeleton_tracker_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(skeleton_tracker_generate_messages skeleton_tracker_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/skeleton_tracker/msg/user_IDs.msg" NAME_WE)
add_dependencies(skeleton_tracker_generate_messages_py _skeleton_tracker_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(skeleton_tracker_genpy)
add_dependencies(skeleton_tracker_genpy skeleton_tracker_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS skeleton_tracker_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/skeleton_tracker)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/skeleton_tracker
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(skeleton_tracker_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/skeleton_tracker)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/skeleton_tracker
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(skeleton_tracker_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/skeleton_tracker)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/skeleton_tracker
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(skeleton_tracker_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/skeleton_tracker)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/skeleton_tracker
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(skeleton_tracker_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/skeleton_tracker)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/skeleton_tracker\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/skeleton_tracker
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(skeleton_tracker_generate_messages_py geometry_msgs_generate_messages_py)
endif()

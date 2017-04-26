# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "summit_xl_web: 0 messages, 3 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(summit_xl_web_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv" NAME_WE)
add_custom_target(_summit_xl_web_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "summit_xl_web" "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv" ""
)

get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv" NAME_WE)
add_custom_target(_summit_xl_web_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "summit_xl_web" "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv" ""
)

get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv" NAME_WE)
add_custom_target(_summit_xl_web_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "summit_xl_web" "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_web
)
_generate_srv_cpp(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_web
)
_generate_srv_cpp(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_web
)

### Generating Module File
_generate_module_cpp(summit_xl_web
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_web
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(summit_xl_web_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(summit_xl_web_generate_messages summit_xl_web_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_cpp _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_cpp _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_cpp _summit_xl_web_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_web_gencpp)
add_dependencies(summit_xl_web_gencpp summit_xl_web_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_web_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_web
)
_generate_srv_eus(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_web
)
_generate_srv_eus(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_web
)

### Generating Module File
_generate_module_eus(summit_xl_web
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_web
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(summit_xl_web_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(summit_xl_web_generate_messages summit_xl_web_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_eus _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_eus _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_eus _summit_xl_web_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_web_geneus)
add_dependencies(summit_xl_web_geneus summit_xl_web_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_web_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_web
)
_generate_srv_lisp(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_web
)
_generate_srv_lisp(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_web
)

### Generating Module File
_generate_module_lisp(summit_xl_web
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_web
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(summit_xl_web_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(summit_xl_web_generate_messages summit_xl_web_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_lisp _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_lisp _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_lisp _summit_xl_web_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_web_genlisp)
add_dependencies(summit_xl_web_genlisp summit_xl_web_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_web_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_web
)
_generate_srv_nodejs(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_web
)
_generate_srv_nodejs(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_web
)

### Generating Module File
_generate_module_nodejs(summit_xl_web
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_web
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(summit_xl_web_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(summit_xl_web_generate_messages summit_xl_web_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_nodejs _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_nodejs _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_nodejs _summit_xl_web_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_web_gennodejs)
add_dependencies(summit_xl_web_gennodejs summit_xl_web_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_web_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_web
)
_generate_srv_py(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_web
)
_generate_srv_py(summit_xl_web
  "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_web
)

### Generating Module File
_generate_module_py(summit_xl_web
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_web
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(summit_xl_web_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(summit_xl_web_generate_messages summit_xl_web_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/RecordVideo.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_py _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/get_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_py _summit_xl_web_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/summit/catkin_ws_kinetic/src/summit_xl_robot/summit_xl_robot-kinetic-devel/summit_xl_web/srv/set_controller_options.srv" NAME_WE)
add_dependencies(summit_xl_web_generate_messages_py _summit_xl_web_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(summit_xl_web_genpy)
add_dependencies(summit_xl_web_genpy summit_xl_web_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS summit_xl_web_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_web)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/summit_xl_web
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(summit_xl_web_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_web)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/summit_xl_web
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(summit_xl_web_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_web)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/summit_xl_web
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(summit_xl_web_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_web)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/summit_xl_web
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(summit_xl_web_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_web)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_web\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_web
    DESTINATION ${genpy_INSTALL_DIR}
    # skip all init files
    PATTERN "__init__.py" EXCLUDE
    PATTERN "__init__.pyc" EXCLUDE
  )
  # install init files which are not in the root folder of the generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_web
    DESTINATION ${genpy_INSTALL_DIR}
    FILES_MATCHING
    REGEX "${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/summit_xl_web/.+/__init__.pyc?$"
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(summit_xl_web_generate_messages_py std_msgs_generate_messages_py)
endif()

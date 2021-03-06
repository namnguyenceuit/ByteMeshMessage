set(GENERIC_ONOFF_CLIENT_SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/generic_onoff_client.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common/src/model_common.c" CACHE INTERNAL "")
set(GENERIC_ONOFF_CLIENT_INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common/include" CACHE INTERNAL "")

set(GENERIC_ONOFF_SERVER_SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/generic_onoff_server.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common/src/model_common.c" CACHE INTERNAL "")
set(GENERIC_ONOFF_SERVER_INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common/include" CACHE INTERNAL "")

set(target_include_dirs
    ${GENERIC_ONOFF_CLIENT_INCLUDE_DIRS}
    ${GENERIC_ONOFF_SERVER_INCLUDE_DIRS}
    ${ACCESS_INCLUDE_DIRS}
    ${MESH_INCLUDE_DIRS}
    ${${SOFTDEVICE}_INCLUDE_DIRS}
    ${${PLATFORM}_INCLUDE_DIRS}
    ${${nRF5_SDK_VERSION}_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/examples/templates
    ${CMAKE_SOURCE_DIR}/mesh/test/include)

add_pc_lint(generic_onoff_${PLATFORM}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/generic_onoff_client.c;${CMAKE_CURRENT_SOURCE_DIR}/src/generic_onoff_server.c;${CMAKE_CURRENT_SOURCE_DIR}/../common/src/model_common.c"
    "${target_include_dirs}"
    "${${PLATFORM}_DEFINES};${${SOFTDEVICE}_DEFINES}")

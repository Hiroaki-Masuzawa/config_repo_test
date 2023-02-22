cmake_minimum_required(VERSION 3.16)

project(config_test)

find_package (Eigen3 REQUIRED)

set(targetlib libRobotAssembler.so)

set(CHOREONOID_INSTALL_PATH /opt/choreonoid)
set(CHOREONOID_INCLUDE_DIRS ${CHOREONOID_INSTALL_PATH}/include/choreonoid-1.8)
set(CHOREONOID_LIBRARY_DIRS ${CHOREONOID_INSTALL_PATH}/lib)

set(GTEST_DIR ${CMAKE_CURRENT_BINARY_DIR}/gtest)
set(GTEST_BUILD_DIR ${GTEST_DIR}/build)
set(GTEST_LIBRARY_DIR ${GTEST_DIR}/lib)
set(GTEST_INCLUDE_DIR ${GTEST_DIR}/include)

if(EXISTS ${GTEST_BUILD_DIR})
  execute_process(COMMAND rm -rf ${GTEST_BUILD_DIR})
endif()
execute_process(COMMAND mkdir -p ${GTEST_BUILD_DIR})

if(EXISTS /usr/src/gtest)
  ## build gtest
  message("EXIST GTEST : ${GTEST_BUILD_DIR}")
  execute_process(COMMAND cmake -DCMAKE_INSTALL_PREFIX=${GTEST_DIR} /usr/src/gtest
                  WORKING_DIRECTORY ${GTEST_BUILD_DIR} )
  execute_process(COMMAND make install
                  WORKING_DIRECTORY ${GTEST_BUILD_DIR} )
else()
  ## TODO: build gtest cloning from github?
  message("FAILED: EXIST GTEST")
endif()

link_directories(${GTEST_LIBRARY_DIR} ${CHOREONOID_LIBRARY_DIRS})
add_executable(config_test config_test.cpp)
target_include_directories(config_test PUBLIC ${GTEST_INCLUDE_DIR} ${CHOREONOID_INCLUDE_DIRS} 
        ${EIGEN3_INCLUDE_DIRS}
	      /choreonoid_src/choreonoid/ext/robot_assembler_plugin/src
        )
target_link_libraries(config_test ${targetlib} gtest gtest_main pthread)
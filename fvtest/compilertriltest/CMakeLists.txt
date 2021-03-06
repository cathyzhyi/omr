###############################################################################
#
# (c) Copyright IBM Corp. 2017, 2017
#
#  This program and the accompanying materials are made available
#  under the terms of the Eclipse Public License v1.0 and
#  Apache License v2.0 which accompanies this distribution.
#
#      The Eclipse Public License is available at
#      http://www.eclipse.org/legal/epl-v10.html
#
#      The Apache License v2.0 is available at
#      http://www.opensource.org/licenses/apache2.0.php
#
# Contributors:
#    Multiple authors (IBM Corp.) - initial implementation and documentation
###############################################################################

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(comptest LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fno-rtti -fno-threadsafe-statics -Wno-deprecated -Wno-enum-compare -Wno-invalid-offsetof -Wno-write-strings -O3 -pthread -fomit-frame-pointer -fasynchronous-unwind-tables -Wreturn-type -fno-dollars-in-identifiers -m64 -fno-strict-aliasing")

add_executable(comptest
   main.cpp
   JitTestUtilitiesTest.cpp
   ILValidatorTest.cpp
   ArithmeticTest.cpp
   ShiftAndRotateTest.cpp
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../tril/tril ${CMAKE_CURRENT_BINARY_DIR}/tril)
target_link_libraries(comptest
   omrGtest
   tril
)

add_test(
    NAME comptest
    COMMAND comptest --gtest_color=yes
)


include_directories (../../UnitTesting)
include_directories (../)

SET(CMAKE_CC_COMPILER /usr/bin/gcc-5)
SET(CMAKE_CXX_COMPILER /usr/bin/g++-5)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DWILD_UNITTESTING_SHOW_FAILURE_DETAILS" )
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-write-strings" )

add_executable (ConsoleTest Console.Test.cpp)

add_custom_command(
	TARGET ConsoleTest POST_BUILD
   	COMMAND ConsoleTest
 )

cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)	

# set the project name and version
project(dbplusplus_test)

file(GLOB SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/dbplusplus_test.cpp
	)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(YAML_CPP REQUIRED yaml-cpp)


if (YAML_CPP_FOUND)
    # Print some message showing some of them
    message(STATUS "yaml-cpp library status:")
    message(STATUS "    version: ${YAML_CPP_VERSION}")
    message(STATUS "    include path: ${YAML_CPP_INCLUDEDIR}" )
    message(STATUS "    cpp flags: -L${YAML_CPP_LIBDIR} ${YAML_CPP_LIBRARIES}")
else ()
    message(FATAL_ERROR "Could not locate yaml-cpp" \n)
endif()


# add_library(yaml_worker SHARED ${CMAKE_CURRENT_SOURCE_DIR}/defines/yaml_worker.cpp)

add_library(element 			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/../src/element/element.cpp)
target_include_directories(element
    PUBLIC
        ${YAML_CPP_INCLUDEDIR} 
        ${YAML_CPP_INCLUDE_DIRS})
        
        
add_library(element_container 	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/../src/element_container/element_container.cpp)
# add_library(database_operator 	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/../src/database_operator/database_operator.cpp)

target_link_libraries(element ${YAML_CPP_LIBRARIES})

# target_include_directories(dbplusplus_test
# PUBLIC
# ${YAML_CPP_INCLUDEDIR} 
# ${YAML_CPP_INCLUDE_DIRS})

target_link_libraries(element_container element)

include_directories(dbplusplus_test ${YAML_CPP_INCLUDE_DIRS})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build)

add_executable(dbplusplus_test ${SOURCE_FILES})
set(CMAKE_CXX_FLAGS "-std=c++17 -g ${CMAKE_CXX_FLAGS}")

# link_directories(${OpenCV_LIB_DIR})
target_compile_features(dbplusplus_test PRIVATE cxx_std_17)
# target_link_libraries(dbplusplus_test ${YAML_CPP_LIBRARIES})
target_link_libraries(dbplusplus_test element ${YAML_CPP_LIBRARIES} -L${YAML_CPP_LIBDIR} ${YAML_CPP_LIBS}
					element_container
					)

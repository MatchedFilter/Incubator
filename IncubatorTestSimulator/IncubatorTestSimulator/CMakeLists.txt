cmake_minimum_required(VERSION 3.16)
project(IncubatorTestSimulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --pedantic-errors")
set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE INCUBATOR_TEST_SIMULATOR_SRC_HDRS src/*.h)
file(GLOB_RECURSE INCUBATOR_TEST_SIMULATOR_SRCS src/*.cpp)

add_executable(${PROJECT_NAME}
    ${INCUBATOR_TEST_SIMULATOR_SRC_HDRS}
    ${INCUBATOR_TEST_SIMULATOR_SRCS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC IncubatorTestSimulatorLib)

target_compile_definitions(${PROJECT_NAME} PUBLIC INCUBATOR_SOFTWARE_VERSION="1.0.0")

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/IncubatorTestSimulator/bin/${CMAKE_BUILD_TYPE})


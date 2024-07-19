
cmake_minimum_required(VERSION 3.5)
project(tvlua LANGUAGES CXX)

find_package(tvision REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LUA REQUIRED lua)

add_executable(tvlua hello.cpp)
target_include_directories(tvlua PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(tvlua PRIVATE tvision::tvision ${LUA_LIBRARIES})

add_custom_target(tvlua_copy_scripts
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/scripts ${PROJECT_BINARY_DIR}/scripts)
add_dependencies(tvlua tvlua_copy_scripts)

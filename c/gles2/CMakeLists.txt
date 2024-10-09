cmake_minimum_required(VERSION 3.5)

project(vte)

add_executable(vte main.c renderer.c r_gl1.c)

include(FindPkgConfig)

pkg_search_module(SDL3 REQUIRED sdl3)
target_include_directories(vte PRIVATE ${SDL3_INCLUDE_DIRS})
target_link_libraries(vte PRIVATE ${SDL3_LIBRARIES})

pkg_search_module(CGLM REQUIRED cglm)
target_include_directories(vte PRIVATE ${CGLM_INCLUDE_DIRS})
target_link_libraries(vte PRIVATE ${CGLM_LIBRARIES})

if(NOT PSP)
	pkg_search_module(GL REQUIRED gl)
	target_include_directories(vte PRIVATE ${GL_INCLUDE_DIRS})
	target_link_libraries(vte PRIVATE ${GL_LIBRARIES})
endif()

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
	target_link_libraries(vte PRIVATE ${MATH_LIBRARY})
endif()

if(PSP)
	create_pbp_file(
		TARGET vte
		ICON_PATH NULL
		BACKGROUND_PATH NULL
		PREVIEW_PATH NULL
		TITLE "VTE"
	)
endif()

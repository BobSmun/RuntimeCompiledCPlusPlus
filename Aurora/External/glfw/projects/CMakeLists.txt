cmake_minimum_required(VERSION 2.8)

project( glfw )

include_directories( ../lib ../lib/win32 )

aux_source_directory( ../lib glfw_source )

if(WIN32)
	aux_source_directory( ../lib/win32 glfw_source_win32 )
	list( APPEND glfw_source ${glfw_source_win32} )
else()
	message( FATAL_ERROR "glfw cmake not implemented for this configuration." )
endif()

add_library(glfw STATIC ${glfw_source})
if(WIN32)
    add_definitions( -D_GLFW_NO_DLOAD_GDI32 )
    add_definitions( -D_GLFW_NO_DLOAD_WINMM )
    add_definitions( -D_MBCS )
endif()

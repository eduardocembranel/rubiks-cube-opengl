cmake_minimum_required( VERSION 3.1 )

project( proj )

find_package( OpenGL REQUIRED )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "" FORCE )
set( GLFW_INSTALL OFF CACHE BOOL  "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories( ${OPENGL_INCLUDE_DIRS} )

include_directories( include )

add_subdirectory( glfw )

file(GLOB SRC_DIR
    "src/*.cpp"
    "src/*.c"
)
 
if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()
    
add_executable( proj WIN32 ${SRC_DIR} )
target_link_libraries( proj ${OPENGL_LIBRARIES} glfw )
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0") 
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'proj' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT proj )
    endif()
endif()

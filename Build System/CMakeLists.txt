cmake_minimum_required( VERSION 2.8 )

# inserir o nome do projeto
project(  )

file( GLOB SRCS *.cpp )
file( GLOB HEADERS *.h )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} `pkg-config --cflags --libs opencv`" )

find_package( OpenCV REQUIRED )
add_executable( ${CMAKE_PROJECT_NAME} ${SRCS} ${HEADERS} )
target_link_libraries( ${CMAKE_PROJECT_NAME} ${OpenCV_LIBS} )

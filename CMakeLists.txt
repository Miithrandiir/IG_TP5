cmake_minimum_required (VERSION 2.6)
project (tp1)
set(SRCS
    ./Src/tp3d.c
    ./Src/graphique.c
    ./Src/touches.c
    )
    
set(HEADERS
  ./Src/graphique.h
  ./Src/touches.h
   )



add_executable(tp3d ${SRCS} ${HEADERS})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(tp3d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

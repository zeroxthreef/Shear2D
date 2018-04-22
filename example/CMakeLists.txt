#use this as an example or something if you want to use cmake to make your games with shear
cmake_minimum_required(VERSION 2.8)
project(ShearXMPL)


option(STATIC_LINK_EVERYTHING "tells the example that the lib was compiled with all of the other libraries statically" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../find/")

#include the stuff. You'll wanna take this out when using the library after it has installed
include_directories(${PROJECT_SOURCE_DIR}/../include)

#just put your sources here
set(ShearXMPL_SRC ${PROJECT_SOURCE_DIR}/main.c ${PROJECT_SOURCE_DIR}/level0.c ${PROJECT_SOURCE_DIR}/level1.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")

add_executable(ShearXMPL ${ShearXMPL_SRC})
# add_dependencies(ShearXMPL shear)


if(STATIC_LINK_EVERYTHING)
  target_link_libraries(ShearXMPL ${PROJECT_SOURCE_DIR}/../build/libshear.a) #you'll just wanna change that to "shear" in the end if it's installed
else(STATIC_LINK_EVERYTHING)
  find_package(SDL2 REQUIRED)
  find_package(SDL2_IMAGE REQUIRED)
  find_package(SDL2_MIXER REQUIRED)
  find_package(Chipmunk REQUIRED)
  find_package(Jansson REQUIRED)
  target_link_libraries(ShearXMPL ${SDL2_LIBRARY})
  target_link_libraries(ShearXMPL ${SDL2_IMAGE_LIBRARY})
  target_link_libraries(ShearXMPL ${SDL2_MIXER_LIBRARY})
  target_link_libraries(ShearXMPL ${CHIPMUNK_LIBRARY})
  target_link_libraries(ShearXMPL ${JANSSON_LIBRARY})
  target_link_libraries(ShearXMPL ${PROJECT_SOURCE_DIR}/../build/libshear.a) #you'll just wanna change that to "shear" in the end if it's installed
endif(STATIC_LINK_EVERYTHING)

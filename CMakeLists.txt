cmake_minimum_required(VERSION 2.8)
project(shear)

include(GNUInstallDirs)
include(ExternalProject)

set(SHEAR_MAJ 0)
set(SHEAR_MIN 0)
set(SHEAR_REV 1)
set(SHEAR_VER ${HWCL_MAJ}.${HWCL_MIN}.${HWCL_REV})

set(SHEAR_SRC src/shear.c src/scene.c src/state.c src/renderer.c src/util.c src/world.c src/command.c src/gui.c)

set(SDL2_SRC_PATH ${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.8)
set(SDL2IMG_SRC_PATH ${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.3)
set(SDL2MIX_SRC_PATH ${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.2)
set(CHIPMUNK_SRC_PATH ${PROJECT_SOURCE_DIR}/lib/chipmunk2D)

option(STATIC_SDL2 "SDL2 Compile statically with source in lib/" OFF)
option(STATIC_SDL2_IMAGE "SDL2_image Compile statically with source in lib/" OFF)
option(STATIC_SDL2_MIXER "SDL2_mixer Compile statically with source in lib/" OFF)
option(STATIC_OPENMPT "Compile libopenmpt statically" OFF) #--without-portaudiocpp
option(STATIC_CHIPMUNK "Compile chipmink2D statically" OFF)
option(BUILD_EXAMPLE "Build the example" OFF)
option(BUILD_EXAMPLE_STATIC "Build the example when shear has been build statically" OFF)
option(BUILD_DEBUG "Build the library with debugging symbols" ON)


include_directories(include)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/find/")

add_library(shear STATIC ${SHEAR_SRC})


find_package(Jansson REQUIRED)
target_link_libraries(shear ${JANSSON_LIBRARY})

if(BUILD_DEBUG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")
endif(BUILD_DEBUG)

if(STATIC_SDL2)
  ExternalProject_Add(SDL2_SHEAR_STATIC SOURCE_DIR ${SDL2_SRC_PATH} CMAKE_ARGS -DSDL_STATIC=1 INSTALL_COMMAND true)
  add_dependencies(shear SDL2_SHEAR_STATIC)
  target_link_libraries(shear ${SDL2_SHEAR_STATIC})
else(STATIC_SDL2)
  find_package(SDL2 REQUIRED)
  target_link_libraries(shear ${SDL2_LIBRARY})
endif(STATIC_SDL2)

if(STATIC_SDL2_IMAGE)
  # ExternalProject_Add(SDL2IMG_SHEAR_STATIC SOURCE_DIR ${SDL2IMG_SRC_PATH} CMAKE_ARGS -DSDL_STATIC=1 INSTALL_COMMAND false) #never finished the next line. TODO finish
  add_custom_target(SDL2IMG_SHEAR_STATIC WORKING_DIRECTORY ${SDL2IMG_SRC_PATH} COMMAND ./configure --enable-png --disable-sdltest LIBPNG_LIBS=-l:${SDL2_SRC_PATH}/libSDL2.a COMMAND make COMMAND mv libSDL2_image.a ${SDL2IMG_SRC_PATH}/build COMMAND make clean)
  add_dependencies(shear SDL2IMG_SHEAR_STATIC)
  target_link_libraries(shear ${PROJECT_SOURCE_DIR}/build/libSDL2_image.a)
else(STATIC_SDL2_IMAGE)
  find_package(SDL2_IMAGE REQUIRED)
  target_link_libraries(shear ${SDL2_IMAGE_LIBRARY})
endif(STATIC_SDL2_IMAGE)

if(STATIC_SDL2_MIXER)
  #add_subdirectory(lib)
  ExternalProject_Add(SDL2MIX_SRC_PATH)
else(STATIC_SDL2_MIXER)
  find_package(SDL2_MIXER REQUIRED)
  target_link_libraries(shear ${SDL2_MIXER_LIBRARY})
endif(STATIC_SDL2_MIXER)

if(STATIC_CHIPMUNK)
  ExternalProject_Add(CHIPMUNK_SRC_PATH)
  #target_link_libraries(SHEAR lib/SDL2/libSDL2.a)
else(STATIC_CHIPMUNK)
  find_package(Chipmunk REQUIRED)
  target_link_libraries(shear ${CHIPMUNK_LIBRARY})
endif(STATIC_CHIPMUNK)



install(TARGETS shear DESTINATION lib)
install(DIRECTORY include DESTINATION include)



if(BUILD_EXAMPLE)
  if(BUILD_EXAMPLE_STATIC)
    ExternalProject_Add(EXAMPLE_TARGET SOURCE_DIR ${PROJECT_SOURCE_DIR}/example BINARY_DIR ${PROJECT_SOURCE_DIR}/example CMAKE_ARGS -DSTATIC_LINK_EVERYTHING=1 INSTALL_COMMAND true)
    add_dependencies(EXAMPLE_TARGET shear)
  else(BUILD_EXAMPLE_STATIC)
    ExternalProject_Add(EXAMPLE_TARGET SOURCE_DIR ${PROJECT_SOURCE_DIR}/example BINARY_DIR ${PROJECT_SOURCE_DIR}/example INSTALL_COMMAND true)
  endif(BUILD_EXAMPLE_STATIC)
endif(BUILD_EXAMPLE)

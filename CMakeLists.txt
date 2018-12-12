cmake_minimum_required(VERSION 2.6)

project(Assignment_1)

if(MSVC)
  include_directories(
    ${CMAKE_SOURCE_DIR}/contrib
	${CMAKE_SOURCE_DIR}/contrib/glm
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
  )
else()
  include_directories(
    /usr/X11R6/include
    /usr/local/include
  )

  link_directories(
    /usr/X11R6/lib
    /usr/local/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_executable(RayTracer
  src/Camera.cpp
  src/Camera.h
  src/main.cpp
  src/Object.cpp
  src/Object.h
  src/Ray.cpp
  src/Ray.h
  src/RayHitList.cpp
  src/RayHitList.h
  src/RayHitTable.cpp
  src/RayHitTable.h
  src/Raytracer.cpp
  src/Raytracer.h
  src/Renderer.cpp
  src/Renderer.h
  src/Window.cpp
  src/Window.h
)

if(MSVC)
  target_link_libraries(RayTracer
    SDL2
  )
else()
  target_link_libraries(RayTracer
    SDL2
  )
endif()

if(MSVC)
  add_custom_command(TARGET RayTracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:RayTracer>"
  )
endif()
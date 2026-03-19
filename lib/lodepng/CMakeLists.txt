add_library(lodepng STATIC lodepng.cpp lodepng.h)

target_include_directories(lodepng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
  target_compile_options(lodepng PRIVATE /W0)
else()
  target_compile_options(lodepng PRIVATE -w)
endif()

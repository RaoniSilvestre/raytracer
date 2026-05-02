file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")


list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")



add_library(core_lib ${SOURCES})

target_include_directories(core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(core_lib
    PUBLIC
        tinyxml2
        lodepng
)

add_executable(app main.cpp)

target_link_libraries(app PRIVATE core_lib)


find_package(OpenMP REQUIRED)

target_link_libraries(app PRIVATE OpenMP::OpenMP_CXX)

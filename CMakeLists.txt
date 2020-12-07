cmake_minimum_required(VERSION 3.0.0)

project(TetrisD3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(UNIX)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
)
endif()

if(WIN32)
include_directories(../include)
link_directories((../lib/x64))
endif()


file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.hpp")

add_executable(
    ${PROJECT_NAME}
    ${SRC_FILES}
    ${HEADER_FILES}
)

if(UNIX)
target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARY} 
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)
endif()

if(WIN32)
target_link_libraries(
    ${PROJECT_NAME}
    SDL2.lib
    SDL2main.lib
    SDL2_image.lib
    SDL2_mixer.lib
    SDL2_ttf.lib
)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


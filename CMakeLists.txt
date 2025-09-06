cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML paths
set(SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/External/SFML/include)
set(SFML_LIB_DIR ${CMAKE_SOURCE_DIR}/External/SFML/lib)
set(SFML_BIN_DIR ${CMAKE_SOURCE_DIR}/External/SFML/bin)

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

# Sources
set(SRC_DIR ${CMAKE_SOURCE_DIR}/GameIDKNAME)
file(GLOB SOURCES "${SRC_DIR}/*.cpp")

add_executable(TD ${SOURCES})

# Link SFML + dependencies
target_link_libraries(TD PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-main-s
    flac
    freetype
    ogg
	oggd
    vorbis
    vorbisenc
    vorbisfile
)

# Copy DLLs (Windows only)
if(WIN32)
    add_custom_command(TARGET TD POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SRC_DIR}/sfml-graphics-3.dll
            ${SRC_DIR}/sfml-window-3.dll
            ${SRC_DIR}/sfml-audio-3.dll
            ${SRC_DIR}/sfml-system-3.dll
            $<TARGET_FILE_DIR:TD>
    )
endif()

# Copy assets Textures
add_custom_command(TARGET TD POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SRC_DIR}/Textures
        $<TARGET_FILE_DIR:TD>/Textures
)

# Copy assets Fonts
add_custom_command(TARGET TD POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SRC_DIR}/Fonts
        $<TARGET_FILE_DIR:TD>/Fonts
)

# Copy assets Shaders
add_custom_command(TARGET TD POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SRC_DIR}/Shaders
        $<TARGET_FILE_DIR:TD>/Shaders
)

# Copy assets Saves
add_custom_command(TARGET TD POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SRC_DIR}/Saves
        $<TARGET_FILE_DIR:TD>/Saves
)
cmake_minimum_required(VERSION 3.16)
project(BombermanProject VERSION 0.0.1 LANGUAGES CXX)

set(PROJECT_HEADERS
    include/assetManager.h
    include/IBasicOperations.h
    include/enemy.h
    include/enemyManager.h
    include/game.h
    include/player.h
    include/playerManager.h
    include/scene.h
    include/sceneManager.h
    include/world.h
    include/bomb
)

set(PROJECT_SOURCES
    src/enemy.cpp
    src/enemyManager.cpp
    src/game.cpp
    src/player.cpp
    src/playerManager.cpp
    src/scene.cpp
    src/sceneManager.cpp
    src/world.cpp
    src/main.cpp
    src/assetManager.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
include_directories(${PROJECT_NAME} PRIVATE include)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

install(TARGETS ${PROJECT_NAME})

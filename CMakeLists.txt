cmake_minimum_required(VERSION 3.3)
project(RogueLike)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lsfml-graphics -lsfml-window -lsfml-system")

set(SOURCE_FILES
    RogueLike/CollisionSystem.cpp
    RogueLike/CollisionSystem.h
    RogueLike/Common.h
    RogueLike/Component.cpp
    RogueLike/Component.h
    RogueLike/Cursor.cpp
    RogueLike/Cursor.h
    RogueLike/Entity.cpp
    RogueLike/Entity.h
    RogueLike/Event.cpp
    RogueLike/Event.h
    RogueLike/Main.cpp
    RogueLike/MovementSystem.cpp
    RogueLike/MovementSystem.h
    RogueLike/Player.cpp
    RogueLike/Player.h
    RogueLike/RenderCommon.h
    RogueLike/RenderManager.cpp
    RogueLike/RenderManager.h
    RogueLike/SpriteBlock.cpp
    RogueLike/SpriteBlock.h
    RogueLike/SpriteFactory.cpp
    RogueLike/SpriteFactory.h
    RogueLike/Tree.h
    RogueLike/Wall.cpp
    RogueLike/Wall.h
    RogueLike/World.cpp
    RogueLike/World.h)

add_executable(RogueLike ${SOURCE_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()



cmake_minimum_required(VERSION 3.3)
project(src)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        src/CollisionSystem.cpp
        src/CollisionSystem.h
        src/Common.h
        src/Component.cpp
        src/Component.h
        src/Cursor.cpp
        src/Cursor.h
        src/DamageSystem.cpp
        src/DamageSystem.h
        src/Enemy.cpp
        src/Enemy.h
        src/EnemyManager.cpp
        src/EnemyManager.h
        src/Entity.cpp
        src/Entity.h
        src/EntityCommon.h
        src/Event.cpp
        src/Event.h
        src/Item.cpp
        src/Item.h
        src/Main.cpp
        src/MovementSystem.cpp
        src/MovementSystem.h
        src/Player.cpp
        src/Player.h
        src/RenderCommon.h
        src/RenderManager.cpp
        src/RenderManager.h
        src/SpriteCanvas.cpp
        src/SpriteCanvas.h
        src/SpriteFactory.cpp
        src/SpriteFactory.h
        src/SpriteList.cpp
        src/SpriteList.h
        src/TileSet.png
        src/TileSet2.png
        src/TileSet3.png
        src/Tree.h
        src/Wall.cpp
        src/Wall.h
        src/World.cpp
        src/World.h)

add_executable(src ${SOURCE_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

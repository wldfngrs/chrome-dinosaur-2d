cmake_minimum_required(VERSION 3.5)

project(DinoSaur)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE
         "Enable -ftime-trace to generate time tracing .json files on clang"
         OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# allow for Sanitizers
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

set(SDL2_DIR SDL2/cmake)
set(SDL2_IMAGE_DIR SDL2_image/cmake)
set(SDL2_MIXER_DIR SDL2_mixer/cmake)
set(SDL2_TTF_DIR SDL2_ttf/cmake)

find_package(SDL2 REQUIRED CONFIG PATHS ${SDL2_DIR})
find_package(SDL2_image REQUIRED CONFIG PATHS ${SDL2_IMAGE_DIR})
find_package(SDL2_mixer REQUIRED CONFIG PATHS ${SDL2_MIXER_DIR})
find_package(SDL2_ttf REQUIRED CONFIG PATHS ${SDL2_TTF_DIR})

include_directories(SDL2/include)
include_directories(SDL2_image/include)
include_directories(SDL2_mixer/include)
include_directories(SDL2_ttf/include)

include_directories(
      ${PROJECT_SOURCE_DIR}
      Background
      Core
      Dino
      Graphics
      Obstacle
      Physics
      Physics
      Sound
      Text
)

add_executable(${PROJECT_NAME} Main.cpp
      Game.h
			Game.cpp
			Background/BackgroundSprite.cpp
      Background/DirtManager.h
			Background/DirtManager.cpp
      Core/EntityComponentSystem.h
      Core/keyboardController.h
      Core/Score.h
			Core/Score.cpp
      Core/SpriteComponent.h
      Core/SpriteComponent.cpp
      Core/TransformComponent.h
      Dino/DinoSprite.cpp
      Dino/DinoStates.h
      Dino/States.h
      Graphics/Sprites.h
      Graphics/TextureManager.cpp
      Graphics/TextureManager.h
      Obstacle/ObstacleManager.cpp
      Obstacle/ObstacleManager.h
      Obstacle/ObstacleSprite.cpp
      Physics/Collision.cpp
      Physics/Collision.h
      Physics/Vector2D.cpp
      Physics/Vector2D.h
      Sound/SoundManager.cpp
      Sound/SoundManager.h
      Text/Text.cpp
      Text/Text.h
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_mixer::SDL2_mixer)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)
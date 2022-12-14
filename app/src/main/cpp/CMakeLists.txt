#
# Copyright (C) The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.4.1)

# build native_app_glue as a static lib
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# now build app's shared lib
# Add  -Werror  to consider unused variables as errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
# add_definitions("-DGLM_FORCE_SIZE_T_LENGTH -DGLM_FORCE_RADIANS")
add_definitions("-DGLM_FORCE_RADIANS")

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

# Import the CMakeLists.txt for the glm library
add_subdirectory(glm)


add_subdirectory(services)
add_subdirectory(screens)
add_subdirectory(uiobjects)
add_subdirectory(sprite)
add_subdirectory(render)
add_subdirectory(particles)
add_subdirectory(workspace)
add_subdirectory(input)

add_library(native-activity SHARED
	${game_SRCS}
    main.cpp
    AudioPlayer
    LevelFactory
    stb_image.h
    ResourceManager
    MainGame
    LevelStructs.cpp
    HighscoreFactory
    ScoreStructs.cpp
    INIReader
    InstanceTracker
    LevelScore.cpp)


target_include_directories(native-activity PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)

# add lib dependencies
target_link_libraries(native-activity
    android
    native_app_glue
    EGL
#    GLESv1_CM
    GLESv3
    glm
    log
    OpenSLES)

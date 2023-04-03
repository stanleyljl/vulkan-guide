#[[
Copyright 2022 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
]]
cmake_minimum_required(VERSION 3.4.1)

project(vktuts)

# Integrate GameActivity, refer to
#     https://d.android.com/games/agdk/integrate-game-activity
# for the detailed instructions.
find_package(game-activity REQUIRED CONFIG)

# build vulkan app
get_filename_component(REPO_ROOT_DIR
    ${CMAKE_SOURCE_DIR}/../../../../../..  ABSOLUTE)
set(COMMON_DIR ${REPO_ROOT_DIR}/android/common)

add_library(${CMAKE_PROJECT_NAME} SHARED
    ${COMMON_DIR}/vulkan_wrapper/vulkan_wrapper.cpp
    AndroidMain.cpp
    ${COMMON_DIR}/src/GameActivitySources.cpp
    ${REPO_ROOT_DIR}/extra-engine/cvars.cpp
    ${REPO_ROOT_DIR}/extra-engine/material_system.cpp
    ${REPO_ROOT_DIR}/extra-engine/player_camera.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_descriptors.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_engine.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_engine_scenerender.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_initializers.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_mesh.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_profiler.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_pushbuffer.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_scene.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_shaders.cpp
    ${REPO_ROOT_DIR}/extra-engine/vk_textures.cpp
    ${REPO_ROOT_DIR}/assetlib/asset_loader.cpp
    ${REPO_ROOT_DIR}/assetlib/material_asset.cpp
    ${REPO_ROOT_DIR}/assetlib/mesh_asset.cpp
    ${REPO_ROOT_DIR}/assetlib/prefab_asset.cpp
    ${REPO_ROOT_DIR}/assetlib/texture_asset.cpp

    ${REPO_ROOT_DIR}/third_party/fmt_lib/fmt/format.cc
    ${REPO_ROOT_DIR}/third_party/fmt_lib/fmt/os.cc
    ${REPO_ROOT_DIR}/third_party/lz4/lz4.c
    ${REPO_ROOT_DIR}/third_party/spv_reflect/spirv_reflect.c
    ${REPO_ROOT_DIR}/third_party/tinyobjloader/tiny_obj_loader.cc
    ${REPO_ROOT_DIR}/third_party/vkbootstrap/VkBootstrap.cpp
    )

include_directories(${COMMON_DIR}/vulkan_wrapper)
include_directories(${REPO_ROOT_DIR}/extra-engine)
include_directories(${REPO_ROOT_DIR}/assetlib)
include_directories(${REPO_ROOT_DIR}/third_party/fmt_lib)
include_directories(${REPO_ROOT_DIR}/third_party/lz4)
include_directories(${REPO_ROOT_DIR}/third_party/spv_reflect)
include_directories(${REPO_ROOT_DIR}/third_party/tinyobjloader)
include_directories(${REPO_ROOT_DIR}/third_party/vkbootstrap)
include_directories(${REPO_ROOT_DIR}/third_party/vma)
include_directories(${REPO_ROOT_DIR}/third_party/glm)
include_directories(${REPO_ROOT_DIR}/third_party/tracy)
include_directories(${REPO_ROOT_DIR}/third_party/stb_image)
include_directories(${REPO_ROOT_DIR}/third_party/nlohmann_json)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall \
                     -DVK_USE_PLATFORM_ANDROID_KHR -DGLM_FORCE_DEPTH_ZERO_TO_ONE -DGLM_FORCE_LEFT_HANDED")

target_link_libraries(${CMAKE_PROJECT_NAME}
    game-activity::game-activity
    log
    android)

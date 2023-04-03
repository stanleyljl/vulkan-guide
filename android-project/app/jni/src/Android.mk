LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../extra-engine
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../assetlib
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/fmt_lib
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/imgui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/lz4
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/spv_reflect
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/tinyobjloader
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/vkbootstrap
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/vma
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/glm
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/tracy
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/stb_image
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/nlohmann_json
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../third_party/vulkan_wrapper

# Add your application source files here...
LOCAL_SRC_FILES := main.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/cvars.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/material_system.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/player_camera.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_descriptors.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_engine.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_engine_scenerender.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_initializers.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_mesh.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_profiler.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_pushbuffer.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_scene.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_shaders.cpp
LOCAL_SRC_FILES += ../../../../extra-engine/vk_textures.cpp
LOCAL_SRC_FILES += ../../../../assetlib/asset_loader.cpp
LOCAL_SRC_FILES += ../../../../assetlib/material_asset.cpp
LOCAL_SRC_FILES += ../../../../assetlib/mesh_asset.cpp
LOCAL_SRC_FILES += ../../../../assetlib/prefab_asset.cpp
LOCAL_SRC_FILES += ../../../../assetlib/texture_asset.cpp

LOCAL_SRC_FILES += ../../../../third_party/vulkan_wrapper/vulkan_wrapper.cpp
LOCAL_SRC_FILES += ../../../../third_party/fmt_lib/fmt/format.cc
LOCAL_SRC_FILES += ../../../../third_party/fmt_lib/fmt/os.cc
LOCAL_SRC_FILES += ../../../../third_party/imgui/imgui.cpp
LOCAL_SRC_FILES += ../../../../third_party/imgui/imgui_demo.cpp
LOCAL_SRC_FILES += ../../../../third_party/imgui/imgui_draw.cpp
LOCAL_SRC_FILES += ../../../../third_party/imgui/imgui_impl_sdl.cpp
LOCAL_SRC_FILES += ../../../../third_party/imgui/imgui_impl_vulkan.cpp
LOCAL_SRC_FILES += ../../../../third_party/imgui/imgui_stdlib.cpp
LOCAL_SRC_FILES += ../../../../third_party/imgui/imgui_widgets.cpp
LOCAL_SRC_FILES += ../../../../third_party/lz4/lz4.c
LOCAL_SRC_FILES += ../../../../third_party/spv_reflect/spirv_reflect.c
LOCAL_SRC_FILES += ../../../../third_party/tinyobjloader/tiny_obj_loader.cc
LOCAL_SRC_FILES += ../../../../third_party/vkbootstrap/VkBootstrap.cpp

LOCAL_CFLAGS := -DGLM_FORCE_DEPTH_ZERO_TO_ONE
LOCAL_CFLAGS += -DGLM_FORCE_LEFT_HANDED

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -llog -landroid

include $(BUILD_SHARED_LIBRARY)

// Copyright 2016 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <android/log.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <vk_engine.h>

android_app* g_AppCtx = nullptr;
VulkanEngine* g_engine = nullptr;

// Process the next main command.
void handle_cmd(android_app* app, int32_t cmd) {
  switch (cmd) {
    case APP_CMD_INIT_WINDOW:
      // The window is being shown, get it ready.
      if (g_engine) {
        uint32_t width = ANativeWindow_getWidth(app->window);
        uint32_t height = ANativeWindow_getHeight(app->window);
        g_engine->_windowExtent = {width, height};
        g_engine->init();
      }
      break;
    case APP_CMD_TERM_WINDOW:
      // The window is being hidden or closed, clean it up.
      if (g_engine) {
        g_engine->cleanup();
      }
      break;
    default:
      __android_log_print(ANDROID_LOG_INFO, "Vulkan Tutorials",
                          "event not handled: %d", cmd);
  }
}

void android_main(struct android_app* app) {

  g_AppCtx = app;
  VulkanEngine engine;
  g_engine = &engine;

  // Set the callback to process system events
  app->onAppCmd = handle_cmd;

  // Used to poll the events in the main loop
  int events;
  android_poll_source* source;

  // Main loop
  do {
    if (ALooper_pollAll(g_engine->is_ready() ? 1 : 0, nullptr,
                        &events, (void**)&source) >= 0) {
      if (source != NULL) source->process(app, source);
    }

    // render if vulkan is ready
    if (g_engine->is_ready()) {
      g_engine->run();
    }
  } while (app->destroyRequested == 0);
}

extern "C" {
JNIEXPORT void JNICALL
Java_com_android_example_MainActivity_nativeKeyDown(JNIEnv *env, jobject thiz, jint code) {
  if (!g_engine) {
    return;
  }

  auto &camera = g_engine->_camera;
  switch (code) {
    case 0:
      camera.inputAxis.z -= 1.f;
          break;
    case 1:
      camera.inputAxis.x += 1.f;
          break;
    case 2:
      camera.inputAxis.z += 1.f;
          break;
    case 3:
      camera.inputAxis.y -= 1.f;
          break;
    case 4:
      camera.inputAxis.x -= 1.f;
          break;
    case 5:
      camera.inputAxis.y += 1.f;
          break;
    default:
      break;
  }

  camera.inputAxis = glm::clamp(camera.inputAxis, {-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0});
}

JNIEXPORT void JNICALL
Java_com_android_example_MainActivity_nativeKeyUp(JNIEnv *env, jobject thiz, jint code) {
  if (!g_engine) {
    return;
  }

  auto &camera = g_engine->_camera;
  switch (code) {
    case 0:
      camera.inputAxis.z += 1.f;
          break;
    case 1:
      camera.inputAxis.x -= 1.f;
          break;
    case 2:
      camera.inputAxis.z -= 1.f;
          break;
    case 3:
      camera.inputAxis.y += 1.f;
          break;
    case 4:
      camera.inputAxis.x += 1.f;
          break;
    case 5:
      camera.inputAxis.y -= 1.f;
          break;
    default:
      break;
  }

  camera.inputAxis = glm::clamp(camera.inputAxis, {-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0});
}
}
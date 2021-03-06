// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/shell/platform/windows/client_wrapper/testing/stub_flutter_windows_api.h"

static flutter::testing::StubFlutterWindowsApi* s_stub_implementation;

namespace flutter {
namespace testing {

// static
void StubFlutterWindowsApi::SetTestStub(StubFlutterWindowsApi* stub) {
  s_stub_implementation = stub;
}

// static
StubFlutterWindowsApi* StubFlutterWindowsApi::GetTestStub() {
  return s_stub_implementation;
}

ScopedStubFlutterWindowsApi::ScopedStubFlutterWindowsApi(
    std::unique_ptr<StubFlutterWindowsApi> stub)
    : stub_(std::move(stub)) {
  previous_stub_ = StubFlutterWindowsApi::GetTestStub();
  StubFlutterWindowsApi::SetTestStub(stub_.get());
}

ScopedStubFlutterWindowsApi::~ScopedStubFlutterWindowsApi() {
  StubFlutterWindowsApi::SetTestStub(previous_stub_);
}

}  // namespace testing
}  // namespace flutter

// Forwarding dummy implementations of the C API.

FlutterDesktopViewControllerRef FlutterDesktopCreateViewController(
    int width,
    int height,
    const FlutterDesktopEngineProperties& engine_properties) {
  if (s_stub_implementation) {
    return s_stub_implementation->CreateViewController(width, height,
                                                       engine_properties);
  }
  return nullptr;
}

void FlutterDesktopDestroyViewController(
    FlutterDesktopViewControllerRef controller) {
  if (s_stub_implementation) {
    s_stub_implementation->DestroyViewController();
  }
}

FlutterDesktopViewRef FlutterDesktopGetView(
    FlutterDesktopViewControllerRef controller) {
  // The stub ignores this, so just return an arbitrary non-zero value.
  return reinterpret_cast<FlutterDesktopViewRef>(1);
}

FlutterDesktopEngineRef FlutterDesktopGetEngine(
    FlutterDesktopViewControllerRef controller) {
  // The stub ignores this, so just return an arbitrary non-zero value.
  return reinterpret_cast<FlutterDesktopEngineRef>(1);
}

uint64_t FlutterDesktopProcessMessages(FlutterDesktopEngineRef engine) {
  if (s_stub_implementation) {
    return s_stub_implementation->ProcessMessages();
  }
  return 0;
}

HWND FlutterDesktopViewGetHWND(FlutterDesktopViewRef controller) {
  if (s_stub_implementation) {
    return s_stub_implementation->ViewGetHWND();
  }
  return reinterpret_cast<HWND>(-1);
}

FlutterDesktopEngineRef FlutterDesktopRunEngine(
    const FlutterDesktopEngineProperties& engine_properties) {
  if (s_stub_implementation) {
    return s_stub_implementation->RunEngine(engine_properties);
  }
  return nullptr;
}

bool FlutterDesktopShutDownEngine(FlutterDesktopEngineRef engine_ref) {
  if (s_stub_implementation) {
    return s_stub_implementation->ShutDownEngine();
  }
  return true;
}

FlutterDesktopPluginRegistrarRef FlutterDesktopGetPluginRegistrar(
    FlutterDesktopEngineRef engine,
    const char* plugin_name) {
  // The stub ignores this, so just return an arbitrary non-zero value.
  return reinterpret_cast<FlutterDesktopPluginRegistrarRef>(1);
}

FlutterDesktopViewRef FlutterDesktopRegistrarGetView(
    FlutterDesktopPluginRegistrarRef controller) {
  // The stub ignores this, so just return an arbitrary non-zero value.
  return reinterpret_cast<FlutterDesktopViewRef>(1);
}

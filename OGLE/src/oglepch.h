#pragma once

const float OGLE_DEF_WIDTH = 640;
const float OGLE_DEF_HEIGHT = 640;

#include "OGLE/Core/PlatformDetection.h"

#ifdef OGLE_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "OGLE/Core/Base.h"

#include "OGLE/Core/Log.h"

#include "OGLE/Debug/Instrumentor.h"

#ifdef OGLE_PLATFORM_WINDOWS
#include <Windows.h>
#endif
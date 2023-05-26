#pragma once
//===============================================
// プリコンパイル済みヘッダー
//  ここに書いたものは初回のみ解析されるため、コンパイル時間が高速になる。
//  全てのcppからインクルードされる必要がある。
//===============================================

//===============================================
// 基本
//===============================================
#pragma comment(lib,"winmm.lib")

#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <cassert>

#include <wrl/client.h>

//===============================================
// STL
//===============================================
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <list>
#include <iterator>
#include <queue>
#include <algorithm>
#include <memory>
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <fileSystem>
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

//===============================================
// Direct3D12
//===============================================
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

#include <d3d12.h>
#include <dxgi1_6.h>

#include "System/System.h"
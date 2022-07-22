#pragma once

#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include <deque>
#include <memory>
#include <vector>
#include <cstdint>
#include <unordered_map>


#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE

#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"
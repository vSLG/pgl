#pragma once

#include <SDL2/SDL_log.h>
#include <sstream>
#include <string>
#include <vector>

#define xcat(a, b) a##b
#define cat(a, b)  xcat(a, b)

#define _log(category, prio, ...) SDL_LogMessage(category, prio, __VA_ARGS__)
#define _log_app(prio, ...) \
    _log(SDL_LOG_CATEGORY_APPLICATION, prio, __VA_ARGS__)
#define _log_video(prio, ...)  _log(SDL_LOG_CATEGORY_VIDEO, prio, __VA_ARGS__)
#define _log_assert(prio, ...) _log(SDL_LOG_CATEGORY_ASSERT, prio, __VA_ARGS__)

#define log(...)   _log_app(SDL_LOG_PRIORITY_INFO, __VA_ARGS__)
#define debug(...) _log_app(SDL_LOG_PRIORITY_DEBUG, __VA_ARGS__)
#define error(...) _log_app(SDL_LOG_PRIORITY_ERROR, __VA_ARGS__)

#define log_video(...)   _log_video(SDL_LOG_PRIORITY_INFO, __VA_ARGS__)
#define debug_video(...) _log_video(SDL_LOG_PRIORITY_DEBUG, __VA_ARGS__)
#define error_video(...) _log_video(SDL_LOG_PRIORITY_ERROR, __VA_ARGS__)

#define log_assert(...)   _log_video(SDL_LOG_PRIORITY_INFO, __VA_ARGS__)
#define debug_assert(...) _log_video(SDL_LOG_PRIORITY_DEBUG, __VA_ARGS__)
#define error_assert(...) _log_video(SDL_LOG_PRIORITY_ERROR, __VA_ARGS__)

namespace pgl::Utils {
std::vector<std::string> split(const std::string &str, char delimeter);
std::string join(const std::vector<std::string> &vec, char splitter);
} // namespace pgl::Utils
#pragma once

#ifndef VRM_DEBUG
#ifdef __ANDROID__
#include <android/log.h>
#endif
#endif

#include <iostream>
#include <string>

namespace vrm {
    void print(const std::string &message);
    void printErr(const std::string &message, const std::exception &errorMessage);
}
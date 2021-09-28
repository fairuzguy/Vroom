#include "debug.hpp"

namespace vrm {
    void print(const std::string &message) {
#ifndef NDEBUG
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_DEBUG, "Template", "%s", message.c_str());
#else
        std::cout << message << std::endl;
#endif
#endif
    }
    
    void printErr(const std::string &message, const std::exception &errorMessage) {
#ifndef NDEBUG
        std::string output = message + " Exception message was: " + std::string{errorMessage.what()};
        print(output);
#endif
    }
}
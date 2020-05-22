#ifndef STARP_SRC_ERR_H_
#define STARP_SRC_ERR_H_

#include <cstdio>

namespace starp {

// errors
namespace err {

inline void Exit(const char* fmt) {
    perror(fmt);
    exit(EXIT_FAILURE);
}

}   // namespace err

}   // namespace starp

#endif  // STARP_SRC_ERR_H_

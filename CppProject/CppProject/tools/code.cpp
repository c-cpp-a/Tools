#ifndef CODE_CPP_CPP
#define CODE_CPP_CPP
#include "code.h"
#include <iostream>
#include <string>
#include <vector>
namespace Code {
const std::string decode_base64(const std::string& a) {
    //用base64解码，返回
    if (a.length() & 3) {
        throw base64_error("const std::string &&decode_base64(const "
                           "std::string &a):Integrity missing!\n");
    }
    std::string res;
    std::string::size_type tmp[4];
    for (std::string::size_type i = 0, len = a.length(); i < len; i += 4) {
        for (std::string::size_type k = 0; k < 4; k++) {
            tmp[k] = base64_nums_hash[a[i + k]];
            if (tmp[k] >> 6) {
                throw base64_error(
                    "const std::string decode_base64(const std::string& "
                    "a):Unknown character appears!");
            }
        }
        res += static_cast<char>((tmp[0] << 2) | (tmp[1] >> 4));
        res += static_cast<char>((tmp[1] << 4) | (tmp[2] >> 2));
        res += static_cast<char>((tmp[2] << 6) | tmp[3]);
    }
    return res;
}
void decode_base64_this(std::string& a) {
    //用base64解码，原地操作
    a = decode_base64(a);
}
const std::string encode_base64(const std::string& a) {
    //用base64加密，返回
    std::string res;
    std::string::size_type i = 0, len = a.length();
    for (; i + 3 <= len; i += 3) {
        unsigned long long x =
            (static_cast<unsigned long long>(a[i]) << 16) |
            (static_cast<unsigned long long>(a[i + 1]) << 8) |
            (static_cast<unsigned long long>(a[i + 2]));
        res += base64_nums[((x >> 18) & (0x3f))];
        res += base64_nums[((x >> 12) & (0x3f))];
        res += base64_nums[((x >> 6) & (0x3f))];
        res += base64_nums[((x) & (0x3f))];
    }
    if (len - i == 2) {
        unsigned long long x = (static_cast<unsigned long long>(a[i]) << 16) |
                               (static_cast<unsigned long long>(a[i + 1]) << 8);
        res += base64_nums[((x >> 18) & (0x3f))];
        res += base64_nums[((x >> 12) & (0x3f))];
        res += base64_nums[((x >> 6) & (0x3f))];
        res += '=';
    } else if (len - i == 1) {
        unsigned long long x = (static_cast<unsigned long long>(a[i]) << 16);
        res += base64_nums[((x >> 18) & (0x3f))];
        res += base64_nums[((x >> 12) & (0x3f))];
        res += '=';
        res += '=';
    }
    return res;
}
void encode_base64_this(std::string& a) {
    //用base64加密，原地操作
    a = encode_base64(a);
}
} // namespace Code
#endif
#ifndef CODE_H_H
#define CODE_H_H
#include <exception>
#include <string>
#include <utility>
namespace Code {
//常量定义域
const std::string base64_nums =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const std::string::size_type base64_nums_hash[255] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62,  255,
    255, 255, 63,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  255, 255,
    255, 0,   255, 255, 255, 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
    10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,
    25,  255, 255, 255, 255, 255, 255, 26,  27,  28,  29,  30,  31,  32,  33,
    34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
    49,  50,  51,  255, 255, 255, 255};
//错误类定义域
class base64_error : public std::exception {
  private:
    const std::string content;

  public:
    base64_error(const std::string& s) : content(s) {}
    base64_error() : content("function base64() throw a exception!\n") {}
    virtual ~base64_error() {}

  public:
    virtual const char* what() const noexcept { return content.c_str(); }
};
//函数定义域
const std::string decode_base64(const std::string&); //用base64解码，返回
void decode_base64_this(std::string&); //用base64解码，原地操作
const std::string encode_base64(const std::string&); //用base64加密，返回
void encode_base64_this(std::string&); //用base64加密，原地操作
} // namespace Code
#endif